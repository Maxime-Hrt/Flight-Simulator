#include "Classes.h"

void Carte::IciToutCePasse()
{
    for(int y = 0;y<AvionEnVol.size();y++)/// ici on incremente le temps passer au sol par les avion
    {
        vector<float> UT;
        vector<int> Trajet;
        int TEMPO;
        map<string,int> EtatActuel;
        EtatActuel = AvionEnVol[y].getEtatAvion();

        Trajet = AvionEnVol[y].getTrajet();
        UT = AvionEnVol[y].getnbUT();
        if(UT.size() != 0){
            if(EtatActuel["Vol"]  == UT[0])// ici on verifie que l'avion à atteint le nombre de UT qu'il devait faire
            {
                AvionEnVol[y].popFrontAvion();
                //std::cout<<"JE RENTRE ICI AVANT DE CRASH"<<std::endl;
                //std::cout<<" AAAA "<< Trajet[1]<<std::endl;
                TEMPO = Trajet[1];
                Trajet.erase(Trajet.begin());
                UT.erase(UT.begin());
                AvionEnVol[y].setTrajet(Trajet);
                AvionEnVol[y].resetnbUT();
                for(int x=0;x<UT.size();x++)
                {
                    AvionEnVol[y].setnbUT(UT[x]);
                }

                AvionEnVol[y].setLocaX(ToutLesAeroport[AvionEnVol[y].getTrajet()[0]].getLoca_x());
                AvionEnVol[y].setLocaY(ToutLesAeroport[AvionEnVol[y].getTrajet()[0]].getLoca_y());

                ToutLesAeroport[TEMPO].atterir(AvionEnVol[y]);// il atterit a paris automatiquement pour le moment
                AvionEnVol.erase(AvionEnVol.begin()+y);
                // ici on doit enlever l'avion du vecteur AvionEnVol pour le mettre dans le vecteur File_Atteente_Atterissage
            }

            else if(EtatActuel["Vol"]  != UT[0])
            {
                EtatActuel["Vol"] = EtatActuel["Vol"] + 1;
                EtatActuel["Sol"] = 0;
                EtatActuel["Atterit"] = 0;
                EtatActuel["Decole"] = 0;
                EtatActuel["Attend"] = 0;
                EtatActuel["AccedePiste"] = 0;
                //std::cout<<AvionEnVol[y].getNom()<<" est en Vol depuis "<<EtatActuel["Vol"]<<" UT"<<std::endl;
                AvionEnVol[y].setEtatAvion(EtatActuel);
                AvionEnVol[y].augmenteDistance(0);
                AvionEnVol[y].setPositionDesign();
            }
        }
    }
}

void Carte::initialiseAeroport()
{
    ifstream fichier("Aeroport.txt");
    if(fichier)
    {
        int a, b, c, d, e, f, g, h, j, k, l, n;
        string nom, desti;
        for (int i = 0; i < 8; ++i) {
            fichier >> a;
            fichier >> nom;
            fichier >> b;
            fichier >> c;
            fichier >> d;
            fichier >> e;
            fichier >> f;
            fichier >> g;
            fichier >> h;
            fichier >> j;
            fichier >> k;
            map<string, int> art;
            fichier >> l;
            for (int m = 0; m < l; ++m) {
                fichier >> desti;
                fichier >> n;
                art[desti]=n;
            }
            aeroport tem(a, nom, b, c, d, e, f, g, h, j, k, l, art);
            ToutLesAeroport.push_back(tem);
        }
    }
    else {
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
    }

    //aero = remplirAeroAleatoirement(aero);
    for(int z=0;z<ToutLesAeroport.size();z++)
    {
        ToutLesAeroport[z].InitialiseAeroport();
        std::cout<<"==========================================="<<std::endl;
        std::cout<<"Aeroport "<<z<<std::endl;
        std::cout<<"===========================================";
        ToutLesAeroport[z].afficheLesAvionSurPlace();
    }
}


std::map<int,int> Carte::initialisePowel()
{
    std::map<int,int> sommet_Altitude;
    int InutileMaintenant;
    int nombreDeSommet;
    int Sommet;
    int Adj;
    std::ifstream fichierPremiereOuverture("Powel.txt");
    if(fichierPremiereOuverture) {
        fichierPremiereOuverture>>nombreDeSommet;
    }
    Graph powelEviteColision(nombreDeSommet);
    std::ifstream fichier("Powel.txt");
    if(fichier) {
        fichier>>InutileMaintenant;
        while(fichier>>Sommet) {
            fichier>>Sommet;
            fichier>>Adj;
            powelEviteColision.addEdge(Sommet, Adj);
        }
    }
    sommet_Altitude = powelEviteColision.greedyColoring();
    return sommet_Altitude;


}



void Carte::derouledujeu() {

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Plateau de jeu"); //crÃ©ation de la window
    sf::Texture texture;

    if (!texture.loadFromFile(
            "/Users/maxime_hrt/Documents/Ing2/Informatique/Ing2Info/TheorieDesGraphes/Swimming_pool/Images/CarteGraph.png")) {
        std::cout << "probleme douverture de l'image\n";
    }
    sf::Texture imageDebut;

    if (!imageDebut.loadFromFile(
            "/Users/maxime_hrt/Documents/Ing2/Informatique/Ing2Info/TheorieDesGraphes/Swimming_pool/Images/long_courier.png")) {
        std::cout << "probleme douverture de l'image\n";
    }
    sf::Sprite imgDebut;
    imgDebut.setTexture(imageDebut);

    sf::Font font;
    if (!font.loadFromFile("/Users/maxime_hrt/Documents/Ing2/Informatique/Ing2Info/TheorieDesGraphes/Swimming_pool/Donnees_ext/arial.ttf"))
    {
        std::cerr << ".Error while loading font" << std::endl;
    }

    sf::Sprite sprite;
    sprite.setTexture(texture); //image dans le sprite*
    std::map<int,int> recevoirAeorportAltitude;
    recevoirAeorportAltitude = initialisePowel();
    for(int y = 0;y<ToutLesAeroport.size();y++)
    {
        ToutLesAeroport[y].setCouleur(recevoirAeorportAltitude[y]);
    }
    std::cout<<std::endl;
    for(int x = 0;x<recevoirAeorportAltitude.size();x++)
    {
        recevoirAeorportAltitude[x] = (recevoirAeorportAltitude[x]+5)*1500;
        std::cout<<"Aeroport "<<x<<" Altitude des avion qui parte de cette aeroport "<<recevoirAeorportAltitude[x]<<std::endl;
    }
    for(int y = 0;y<ToutLesAeroport.size();y++)
    {
        ToutLesAeroport[y].setaltitude(recevoirAeorportAltitude[y]);
    }
    std::vector <Avion> stackAvion;
    std::vector <Avion> stackAvion111;
    std::vector <Avion> stackAvionDispo;
    Avion AvionTest("Long_Courrier");
    std::string TypeAvion;
    int choixmenu;
    std::string choixatterissage;
    std::string choixavion1;
    bool finJeu(true);
    vector<Avion> AvionCrash;


    srand(time(NULL));
    window.clear();

    while (window.isOpen()) {
        sf::Event event;
        window.draw(imgDebut);
        window.display();
        while (window.pollEvent(event)) {
            do{


                std::cout << std::endl;
                std::cout << "=========================================Menu========================================="
                          << std::endl;
                std::cout << "Si vous voulez déplacer des avions manuelement appuyer sur 1" << std::endl;
                std::cout << "Si vous voulez lancer une simulation appuyer sur 2"<<std::endl;
                std::cout << "Si vous voulez afficher tous les aéroports avec leur caractéristiques appuyer sur 3" << std::endl;
                std::cout << "quitter appuyer sur 4" << std::endl;
                std::cout << "======================================================================================"
                          << std::endl;

                std::cin >> choixmenu;
                int FIN = 0;
                int compteur  = 0;


/// ici je modifie
                switch (choixmenu) {
                    case 1: {

                        for (int i = 0; i < ToutLesAeroport.size(); ++i) {
                            ToutLesAeroport[i].initialiseDebutVol();
                        }

                        for(int y = 0;y<ToutLesAeroport.size();y++)
                        {
                            ToutLesAeroport[y].setPermDecoler(true);
                        }
                        for(int y = 0;y<ToutLesAeroport.size();y++)
                        {
                            ToutLesAeroport[y].setCompteurPermDecoler(0);
                        }
                        while (compteur < 1000) {
                            /*
                            if (compteur%20 == 0 && (AvionEnVol.size() != 0)){
                                AvionEnVol[0].Fuitereservoir();
                            }*/

                            bool continuee = false;
                            int depart;
                            int arrive;
                            int nouveaudecolage;
                            std::cout << "voulez vous faire decolez un nouvelle avion" << std::endl;
                            std::cout << "1 oui" << std::endl;
                            std::cout << "2 non" << std::endl;
                            std::cin >> nouveaudecolage;
                            if (nouveaudecolage == 1) {
                                while(continuee == false)
                                {
                                    std::cout << "d'ou voulez vous partir : " << std::endl;
                                    std::cout << " entrer 0 pour Paris" << std::endl;
                                    std::cout << " entrer 1 pour Tallinn" << std::endl;
                                    std::cout << " entrer 2 pour Tokyo" << std::endl;
                                    std::cout << " entrer 3 pour Sydney" << std::endl;
                                    std::cout << " entrer 4 pour Tananarive" << std::endl;
                                    std::cout << " entrer 5 pour Chicago" << std::endl;
                                    std::cout << " entrer 6 pour Dubai" << std::endl;
                                    std::cout << " entrer 7 pour Santiago" << std::endl;

                                    std::cin >> depart;
                                    std::cout << "ou voulez vous arrivez : " << std::endl;
                                    std::cout << " entrer 0 pour Paris" << std::endl;
                                    std::cout << " entrer 1 pour Tallinn" << std::endl;
                                    std::cout << " entrer 2 pour Tokyo" << std::endl;
                                    std::cout << " entrer 3 pour Sydney" << std::endl;
                                    std::cout << " entrer 4 pour Tananarive" << std::endl;
                                    std::cout << " entrer 5 pour Chicago" << std::endl;
                                    std::cout << " entrer 6 pour Dubai" << std::endl;
                                    std::cout << " entrer 7 pour Santiago" << std::endl;

                                    /// A randomiser plus tard
                                    std::cin >> arrive;
                                    stackAvionDispo = ToutLesAeroport[depart].partir(depart, arrive);
                                    if(stackAvionDispo.size() == 0)
                                    {
                                        continuee = false;
                                    }
                                    else if(stackAvionDispo.size() != 0)
                                    {
                                        std::cout<< "entrer le nom de l'avion que voulez faire decoler (ce nom doit apparaitre dans la liste des avion disponible)"<< std::endl;
                                        std::cin >> choixavion1;
                                        continuee = true;
                                    }

                                }

                                for (int z = 0; z < stackAvionDispo.size(); z++) {
                                    if (stackAvionDispo[z].getNom() == choixavion1) {
                                        stackAvionDispo[z].setdepart(depart);
                                        stackAvionDispo[z].setarrive(arrive);
                                        //std::cout << "fdsfqfqsfsdqfdqfd" << std::endl;
                                        std::cout << stackAvionDispo[z].getdepart() << std::endl;
                                        std::cout << stackAvionDispo[z].getarrive() << std::endl;
                                        ToutLesAeroport[depart].decoler(stackAvionDispo[z]);
                                    }
                                }
                            }

                            /// ici il y a le compteur pour savoir si un avion peut decoler car il faut un decalage de 1ut par decolage par aeroport
                            for(int y = 0;y<ToutLesAeroport.size();y++)
                            {
                                if(ToutLesAeroport[y].getPermDecoler() == false)
                                {
                                    int comptedecole;
                                    comptedecole = ToutLesAeroport[y].getCompteurPermDecoler();
                                    comptedecole = comptedecole+1;
                                    ToutLesAeroport[y].setCompteurPermDecoler(comptedecole);
                                }
                            }

                            for(int y = 0;y<ToutLesAeroport.size();y++)
                            {

                                if(ToutLesAeroport[y].getCompteurPermDecoler() == 2)
                                {
                                    ToutLesAeroport[y].setPermDecoler(true);
                                    ToutLesAeroport[y].setCompteurPermDecoler(0);
                                }
                            }

                            for (int w = 0; w < ToutLesAeroport.size(); w++) {
                                cout << endl;
                                cout << "AEROPORT : " << w << endl;
                                ToutLesAeroport[w].icitoutcepasse();
                                std::vector<Avion> AvionQuiVontEtreEnVol;
                                AvionQuiVontEtreEnVol = ToutLesAeroport[w].ActualisationAvionDecoler();
                                for (int u = 0; u < AvionQuiVontEtreEnVol.size(); u++) {
                                    AvionEnVol.push_back(AvionQuiVontEtreEnVol[u]);
                                }
                                AvionQuiVontEtreEnVol.clear();
                                ToutLesAeroport[w].nettoyervecteurAvionADecoler();
                            }



                            // apres le parametrage nous mettron le bool TrajetDeCetteAvionEnregistre en true et quand le vecteur trajet de l'avion sera vide on remmetra ce bool en false
                            for (int r = 0; r < AvionEnVol.size(); r++) {
                                if (!AvionEnVol[r].getTrajetDeCetteAvionEnregistre()) {
                                    AvionEnVol[r].ParametrageGPSdijkstra();
                                    AvionEnVol[r].setTrajet(AvionEnVol[r].trajet_de_lavion(AvionEnVol[r].getdepart(),
                                                                                           AvionEnVol[r].getarrive()));
                                    AvionEnVol[r].envol();
                                    vector<int> pp;

                                    for (int i = AvionEnVol[r].getTrajet().size() - 1;
                                         i >= 0; --i) { //inversion trajet pour plus de clareté
                                        pp.push_back(AvionEnVol[r].getTrajet()[i]);
                                    }
                                    AvionEnVol[r].setTrajet(pp);


                                    for (int i = 0; i < AvionEnVol[r].getTrajet().size() - 1; ++i) {
                                        //cout << stackAvion[0].getTrajet()[i] << " ";
                                        AvionEnVol[r].setnbUT(ToutLesAeroport[AvionEnVol[r].getTrajet()[i]].getDistance(
                                                conversionSommetVille(AvionEnVol[r].getTrajet()[i]) + "->" +
                                                conversionSommetVille(AvionEnVol[r].getTrajet()[i + 1])) / 200);
                                        cout << AvionEnVol[r].getnbUT()[i] << endl;
                                        float distance = ToutLesAeroport[AvionEnVol[r].getTrajet()[i]].getDistance(
                                                conversionSommetVille(AvionEnVol[r].getTrajet()[i]) + "->" +
                                                conversionSommetVille(AvionEnVol[r].getTrajet()[i + 1]));

                                        AvionEnVol[r].setAvencement(
                                                (ToutLesAeroport[AvionEnVol[r].getTrajet()[i + 1]].getLoca_x() -
                                                 ToutLesAeroport[AvionEnVol[r].getTrajet()[i]].getLoca_x()) /
                                                (distance / 200),
                                                (ToutLesAeroport[AvionEnVol[r].getTrajet()[i + 1]].getLoca_y() -
                                                 ToutLesAeroport[AvionEnVol[r].getTrajet()[i]].getLoca_y()) /
                                                (distance / 200));
                                        //std::cout<<"Distance = "<<distance<<std::endl;
                                        cout << AvionEnVol[r].getAvnecement_x()[i] << " "
                                             << AvionEnVol[r].getAvnecement_y()[i]
                                             << endl;


                                    }
                                    if (AvionEnVol[r].getX() == 0) {
                                        AvionEnVol[r].setLocaX(
                                                ToutLesAeroport[AvionEnVol[r].getTrajet()[0]].getLoca_x());
                                        AvionEnVol[r].setLocaY(
                                                ToutLesAeroport[AvionEnVol[r].getTrajet()[0]].getLoca_y());

                                    }
                                    AvionEnVol[r].setTrajetDeCetteAvionEnregistre(true);
                                }
                            }


                            IciToutCePasse();

                            /*
                            for (int i = 0; i < AvionEnVol.size();++i) {
                                AvionEnVol[i].crashDesign();
                                if(AvionEnVol[i].getreserveActuelCarburant() <= 0){
                                    AvionCrash.push_back(AvionEnVol[i]);
                                    AvionEnVol.erase(AvionEnVol.begin() + i);
                                }
                            }
                            */

                            std::cout<<"============================================="<<std::endl;
                            std::cout<<"AVION ACTUELLEMENT EN VOL"<<std::endl;
                            std::cout<<"============================================="<<std::endl;
                            for(int i = 0;i<AvionEnVol.size();i++)
                            {
                                AvionEnVol[i].affichereserveActuelCarburant();
                                AvionEnVol[i].actualisationCarburantVol();
                                std::map<string,int> tempo;
                                tempo = AvionEnVol[i].getEtatAvion();
                                std::cout<<AvionEnVol[i].getNom()<<" est en Vol depuis "<<tempo["Vol"]<<" UT est atterit a "<<" il vole a "<<AvionEnVol[i].getaltitudeAvion()<<" metre"<<" sa couleur est "<< AvionEnVol[i].getCouleurAvion()<<std::endl;//mettre le nombre d'ut à atteindre
                            }
                            std::cout<<"============================================="<<std::endl;
                            // std::chrono::seconds dura(1);
                            //std::this_thread::sleep_for(dura);
                            compteur = compteur+1;


                            window.clear();
                            window.draw(sprite);
                            for (int i = 0; i < AvionEnVol.size(); ++i) {
                                window.draw(AvionEnVol[i].getDesignAvion());
                            }

                            window.display();





                            //IciToutCePasse();
                        }

                    }
                        break;
                    case 2: {

                        for (int i = 0; i < ToutLesAeroport.size(); ++i) {
                            ToutLesAeroport[i].initialiseDebutVol();
                        }
                        for(int y = 0;y<ToutLesAeroport.size();y++)
                        {
                            ToutLesAeroport[y].setPermDecoler(true);
                        }
                        for(int y = 0;y<ToutLesAeroport.size();y++)
                        {
                            ToutLesAeroport[y].setCompteurPermDecoler(0);
                        }
                        while (compteur < 1000 && finJeu) {

                            if (compteur%20 == 0 && (AvionEnVol.size() != 0)){
                                AvionEnVol[0].Fuitereservoir();
                            }
                            int nbAvionDispo;
                            int depart;
                            int arrive;
                            int choixavion2;
                            std::string choixavion2string;
                            int toutlesaeroportsontvidecompteur;
                            bool toutlesaeroportsontvide = false;
                            bool FinBoucleAlea = false;
                            bool departDiffDarrive = false;
                            while ((FinBoucleAlea == false)&&(toutlesaeroportsontvide == false)) {
                                while(departDiffDarrive == false)
                                {
                                    depart = rand() % 8;
                                    arrive = rand() % 8;
                                    //std::cout<<"DEPART : "<<depart<<std::endl;
                                    //std::cout<<"ARRIVE : "<<arrive<<std::endl;
                                    if(depart != arrive)
                                    {
                                        departDiffDarrive = true;
                                    }
                                }

                                stackAvionDispo = ToutLesAeroport[depart].partir(depart, arrive);
                                nbAvionDispo = stackAvionDispo.size();
                                //std::cout << " ICI " << nbAvionDispo;
                                if (nbAvionDispo == 0) {
                                    std::cout << "cette aeroport ne possede pas d'avion pour ce voyage" << std::endl;
                                    FinBoucleAlea = false;
                                    toutlesaeroportsontvidecompteur = toutlesaeroportsontvidecompteur +1;
                                    if(toutlesaeroportsontvidecompteur >= 7)
                                    {
                                        //std::cout<<"il n'y a plus davion au sol dans aucun aerroport"<<std::endl;
                                        toutlesaeroportsontvide = true;
                                    }
                                } else if (nbAvionDispo >= 1) {
                                    choixavion2 = 0;
                                    FinBoucleAlea = true;
                                    //std::cout << " ICI 2 " << choixavion2 << std::endl;
                                    //stackAvionDispo[choixavion2].setTrajetDeCetteAvionEnregistre(false);
                                    stackAvionDispo[choixavion2].setdepart(depart);
                                    stackAvionDispo[choixavion2].setarrive(arrive);
                                    //std::cout << stackAvionDispo[choixavion2].getdepart() << std::endl;
                                    //std::cout << stackAvionDispo[choixavion2].getarrive() << std::endl;
                                    ToutLesAeroport[depart].decoler(stackAvionDispo[choixavion2]);
                                }


                            }


                            /// ici il y a le compteur pour savoir si un avion peut decoler car il faut un decalage de 1ut par decolage par aeroport
                            for(int y = 0;y<ToutLesAeroport.size();y++)
                            {
                                if(ToutLesAeroport[y].getPermDecoler() == false)
                                {
                                    int comptedecole;
                                    comptedecole = ToutLesAeroport[y].getCompteurPermDecoler();
                                    comptedecole = comptedecole+1;
                                    ToutLesAeroport[y].setCompteurPermDecoler(comptedecole);
                                }
                            }
                            for(int y = 0;y<ToutLesAeroport.size();y++)
                            {
                                if(ToutLesAeroport[y].getCompteurPermDecoler() == 2)
                                {
                                    ToutLesAeroport[y].setPermDecoler(true);
                                    ToutLesAeroport[y].setCompteurPermDecoler(0);
                                }
                            }


                            ///ici jai modifier des truc
                            for (int w = 0; w < ToutLesAeroport.size(); w++) {
                                cout << endl;
                                cout << "AEROPORT : " << w << endl;
                                ToutLesAeroport[w].icitoutcepasse();
                                std::vector<Avion> AvionQuiVontEtreEnVol;
                                AvionQuiVontEtreEnVol = ToutLesAeroport[w].ActualisationAvionDecoler();
                                for (int u = 0; u < AvionQuiVontEtreEnVol.size(); u++) {
                                    AvionEnVol.push_back(AvionQuiVontEtreEnVol[u]);
                                }
                                AvionQuiVontEtreEnVol.clear();
                                ToutLesAeroport[w].nettoyervecteurAvionADecoler();
                            }


                            // apres le parametrage nous mettron le bool TrajetDeCetteAvionEnregistre en true et quand le vecteur trajet de l'avion sera vide on remmetra ce bool en false
                            for (int r = 0; r < AvionEnVol.size(); r++) {
                                if (!AvionEnVol[r].getTrajetDeCetteAvionEnregistre()) {
                                    //std::cout<<" JE PASSE ICI EST C TREES IMPORTANT"<<std::endl;
                                    AvionEnVol[r].ParametrageGPSdijkstra();
                                    AvionEnVol[r].setTrajet(AvionEnVol[r].trajet_de_lavion(AvionEnVol[r].getdepart(),
                                                                                           AvionEnVol[r].getarrive()));
                                    AvionEnVol[r].envol();
                                    vector<int> pp;

                                    for (int i = AvionEnVol[r].getTrajet().size() - 1;
                                         i >= 0; --i) { //inversion trajet pour plus de clareté
                                        pp.push_back(AvionEnVol[r].getTrajet()[i]);
                                    }
                                    AvionEnVol[r].setTrajet(pp);


                                    for (int i = 0; i < AvionEnVol[r].getTrajet().size() - 1; ++i) {
                                        //cout << stackAvion[0].getTrajet()[i] << " ";
                                        AvionEnVol[r].setnbUT(ToutLesAeroport[AvionEnVol[r].getTrajet()[i]].getDistance(
                                                conversionSommetVille(AvionEnVol[r].getTrajet()[i]) + "->" +
                                                conversionSommetVille(AvionEnVol[r].getTrajet()[i + 1])) / 200);
                                        cout << AvionEnVol[r].getnbUT()[i] << endl;
                                        float distance = ToutLesAeroport[AvionEnVol[r].getTrajet()[i]].getDistance(
                                                conversionSommetVille(AvionEnVol[r].getTrajet()[i]) + "->" +
                                                conversionSommetVille(AvionEnVol[r].getTrajet()[i + 1]));

                                        AvionEnVol[r].setAvencement(
                                                (ToutLesAeroport[AvionEnVol[r].getTrajet()[i + 1]].getLoca_x() -
                                                 ToutLesAeroport[AvionEnVol[r].getTrajet()[i]].getLoca_x()) /
                                                (distance / 200),
                                                (ToutLesAeroport[AvionEnVol[r].getTrajet()[i + 1]].getLoca_y() -
                                                 ToutLesAeroport[AvionEnVol[r].getTrajet()[i]].getLoca_y()) /
                                                (distance / 200));
                                        //std::cout<<"Distance = "<<distance<<std::endl;
                                        cout << AvionEnVol[r].getAvnecement_x()[i] << " "
                                             << AvionEnVol[r].getAvnecement_y()[i]
                                             << endl;


                                    }
                                    if (AvionEnVol[r].getX() == 0) {
                                        AvionEnVol[r].setLocaX(
                                                ToutLesAeroport[AvionEnVol[r].getTrajet()[0]].getLoca_x());
                                        AvionEnVol[r].setLocaY(
                                                ToutLesAeroport[AvionEnVol[r].getTrajet()[0]].getLoca_y());

                                    }
                                    AvionEnVol[r].setTrajetDeCetteAvionEnregistre(true);
                                }
                            }




                            std::chrono::seconds dura(1);
                            std::this_thread::sleep_for(dura);


                            window.clear();

                            IciToutCePasse();




                            //Les avions qui ne volle plus ne s'affiche plus (ILS SONT EN PANNE)
                            for (int i = 0; i < AvionEnVol.size(); ++i) {
                                std::map<string,int> recupEtat;
                                recupEtat = AvionEnVol[i].getEtatAvion();
                                if (recupEtat["Vol"] == 0){
                                    AvionEnVol.erase(AvionEnVol.begin() + i);
                                }
                            }


                            window.draw(sprite);
                            for (int i = 0; i < AvionEnVol.size(); ++i) {
                                AvionEnVol[i].crashDesign();
                                window.draw(AvionEnVol[i].getDesignAvion());


                                if((AvionEnVol[i].getreserveActuelCarburant() <= 0 )&& AvionEnVol[i].getEtatFuite()){
                                    //cout << "DANS BOUCLE DE CARBURANT " << AvionEnVol[i].getreserveActuelCarburant() << endl;
                                    AvionCrash.push_back(AvionEnVol[i]);
                                    AvionEnVol.erase(AvionEnVol.begin() + i);
                                }
                            }
                            for (int i = 0; i < AvionCrash.size(); ++i) {
                                window.draw(AvionCrash[i].getDesignAvion());
                            }


                            window.display();





                            std::cout<<"============================================="<<std::endl;
                            std::cout<<"AVION ACTUELLEMENT EN VOL"<<std::endl;
                            std::cout<<"============================================="<<std::endl;
                            for(int i = 0;i<AvionEnVol.size();i++)
                            {
                                vector<float> ut;
                                ut=AvionEnVol[i].getnbUT();
                                //AvionEnVol[i].affichereserveActuelCarburant();
                                AvionEnVol[i].actualisationCarburantVol();
                                std::map<string,int> tempo;
                                tempo = AvionEnVol[i].getEtatAvion();
                                std::cout<<AvionEnVol[i].getNom()<<" est en Vol depuis "<<tempo["Vol"]<<" UT est atterit a "<<ut[0]<<" il vole a "<<AvionEnVol[i].getaltitudeAvion()<<" metre"<<" sa couleur est "<< AvionEnVol[i].getCouleurAvion()<<std::endl;//mettre le nombre d'ut à atteindre

                            }
                            std::cout<<"============================================="<<std::endl;
                            compteur = compteur+1;

                            //IciToutCePasse();


                        }

                    }
                        break;
                    case 3: {
                        sf::Text text;

                        text.setFont(font); // font is a sf::Font

                        string phrace;
                        for (int i = 0; i < ToutLesAeroport.size(); ++i) {

                            phrace += "nom de l aeroport : " +(ToutLesAeroport[i].getterNom()) + "\n";
                            phrace += "nombre de pistes : " +to_string(ToutLesAeroport[i].getternb_piste()) + "\n";
                            phrace += "nombre de places au sol : " +to_string(ToutLesAeroport[i].getternb_places_sol()) + "\n";
                            phrace += "delais attente au sol : " +to_string(ToutLesAeroport[i].gettempssol()) + "\n";
                            phrace += "temps d acces au piste : " +to_string(ToutLesAeroport[i].getattenteaccesaupiste()) + "\n";
                            phrace += "duree atterisage / decolage : " +to_string(ToutLesAeroport[i].getTempsAtterisage()) + "\n";
                            phrace += "delais anti collision : " +to_string(ToutLesAeroport[i].getDelaisAntiColision()) + "\n";
                            phrace += "duree boucle attente avant atterisage : " +to_string(ToutLesAeroport[i].getdelaisboucleattenteavantatterisage()) + "\n\n";

                        }
                        text.setString(phrace);
                        text.setCharacterSize(12); // in pixels, not points!
                        text.setFillColor(sf::Color::White);

                        while (window.isOpen()) {
                            sf::Event event;
                            while (window.pollEvent(event)) {


                                window.draw(text);
                                window.display();
                                if(event.type==sf::Event::Closed)
                                {
                                    window.close();
                                    choixmenu = 4;
                                }
                            }
                        }

                    }

                        break;

                }


            }while (choixmenu != 4 && finJeu);

        }
        if (!finJeu)
            window.close();
    }
}