#include "Classes.h"
//cc
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
                std::cout<<"JE RENTRE ICI AVANT DE CRASH"<<std::endl;
                std::cout<<" AAAA "<< Trajet[1]<<std::endl;
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
                std::cout<<AvionEnVol[y].getNom()<<" est en Vol depuis "<<EtatActuel["Vol"]<<" UT"<<std::endl;
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
    /*
    INITIALISATION DES GRAPHIQUES
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML Application");
    sf::Texture imageFond_texture;
    if(imageFond_texture.loadFromFile("/Users/maxime_hrt/Documents/Ing2/Informatique/Ing2Info/TheorieDesGraphes/Swimming_pool/Images/Carte.png", sf::IntRect(0, 0, WIDTH, HEIGHT))){
        //Message d'erreur t'as vu
    }
    sf::Sprite imageFond;
    imageFond.setTexture(imageFond_texture);
    */

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Plateau de jeu"); //crÃ©ation de la window
    sf::Texture texture;
    if (!texture.loadFromFile(
            "/Users/maxime_hrt/Documents/Ing2/Informatique/Ing2Info/TheorieDesGraphes/Swimming_pool/Images/Carte.png")) {
        std::cout << "probleme douverture de l'image\n";
    }
    sf::Sprite sprite;
    sprite.setTexture(texture); //image dans le sprite*
    std::map<int,int> recevoirAeorportAltitude;
    recevoirAeorportAltitude = initialisePowel();
    for(int y = 0;y<ToutLesAeroport.size();y++)
    {
        ToutLesAeroport[y].setCouleur(recevoirAeorportAltitude[y]);
        //std::cout<<ToutLesAeroport[y].getCouleur()<<std::endl;
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
        //std::cout<<ToutLesAeroport[y].getaltitude()<<std::endl;
    }
    std::vector <Avion> stackAvion;
    std::vector <Avion> stackAvion111;
    std::vector <Avion> stackAvionDispo;
    Avion AvionTest("Long_Courrier");
    std::string TypeAvion;
    int choixmenu;
    std::string choixatterissage;
    std::string choixavion1;
    /// faire un do while mais fleme je vais dodo



    srand(time(NULL));
    window.clear();

    while (window.isOpen()) {
    sf::Event event;
    do {
        while (window.pollEvent(event)) {

        std::cout << std::endl;
        std::cout << "=========================================Menu========================================="
                  << std::endl;
        std::cout << "Si vous voulez vous deplacer appuyer sur 1" << std::endl;
        //std::cout<<"Si vous voulez choisir votre avion appuyer sur 2"<<std::endl;
        std::cout << "Si vous voulez afficher les caracteristique de votre avion appuyer sur 3" << std::endl;
        std::cout << "quitter appuyer sur 4" << std::endl;
        std::cout << "======================================================================================"
                  << std::endl;

        std::cin >> choixmenu;
        int FIN = 0;
        int compteur  = 0;

        /// Tu verras plus tard
        //choixmenu = 1;

/// ici je modifie
        switch (choixmenu) {
            case 1: {
                for(int y = 0;y<ToutLesAeroport.size();y++)
                {
                    ToutLesAeroport[y].setPermDecoler(true);
                }
                for(int y = 0;y<ToutLesAeroport.size();y++)
                {
                    ToutLesAeroport[y].setCompteurPermDecoler(0);
                }
                while (compteur < 1000) {
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

                            /// A randomiser plus tard
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
                                std::cout << "fdsfqfqsfsdqfdqfd" << std::endl;
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
                    //////////////////////////////////////////////////
                    ///ici jai modifier des truc

                    for (int w = 0; w < ToutLesAeroport.size(); w++) {
                        ToutLesAeroport[w].icitoutcepasse();
                        std::vector<Avion> AvionQuiVontEtreEnVol;
                        AvionQuiVontEtreEnVol = ToutLesAeroport[w].ActualisationAvionDecoler();
                        for (int u = 0; u < AvionQuiVontEtreEnVol.size(); u++) {
                            AvionEnVol.push_back(AvionQuiVontEtreEnVol[u]);
                        }
                        AvionQuiVontEtreEnVol.clear();
                        ToutLesAeroport[w].nettoyervecteurAvionADecoler();
                    }

                    /*
                    if (AvionEnVol.size() != 0) {
                        std::cout << "==========================================" << std::endl;
                        std::cout << "Avion Disponible Pour Atterissage" << std::endl;
                        std::cout << "==========================================" << std::endl;
                        for (int d = 0; d < AvionEnVol.size(); d++) {
                            AvionEnVol[d].afficheAttribut();
                            std::cout << std::endl;
                        }
                        std::cout
                                << "entrer le nom de l'avion que voulez faire atterire (ce nom doit apparaitre dans la liste des avion disponible)"
                                << std::endl;
                        std::cin >> choixatterissage;
                        for (int z = 0; z < AvionEnVol.size(); z++) {
                            if (AvionEnVol[z].getNom() == choixatterissage) {
                                ToutLesAeroport[0].atterir(
                                        AvionEnVol[z]);// il atterit a paris automatiquement pour le moment
                                AvionEnVol.erase(AvionEnVol.begin() + z);
                            }
                        }

                    }
                    */

                    /*std::cout << "ENTRER 1 POUR ARRETER LA SIMULATION" << std::endl;
                    std::cout << "ENTRER 0 POUR CONTINUER LA SIMULATION" << std::endl;
                    std::cin >> FIN;*/

                    ///
                    //std::cout<<"LA BIZARERIE NEST JAMAIS FINI"<<std::endl;


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
                    std::cout<<"============================================="<<std::endl;
                    std::cout<<"AVION ACTUELLEMENT EN VOL"<<std::endl;
                    std::cout<<"============================================="<<std::endl;
                    for(int i = 0;i<AvionEnVol.size();i++)
                    {
                        std::map<string,int> tempo;
                        tempo = AvionEnVol[i].getEtatAvion();
                        std::cout<<AvionEnVol[i].getNom()<<" est en Vol depuis "<<tempo["Vol"]<<" UT est atterit a "<<" il vole a "<<AvionEnVol[i].getaltitudeAvion()<<" metre"<<" sa couleur est "<< AvionEnVol[i].getCouleurAvion()<<std::endl;//mettre le nombre d'ut à atteindre
                    }
                    std::cout<<"============================================="<<std::endl;
                    // std::chrono::seconds dura(1);
                    //std::this_thread::sleep_for(dura);
                    compteur = compteur+1;

                    ///A changer avec les UT
                    /*
                    for (int i = 0; i < AvionEnVol.size(); ++i) {
                        if (((AvionEnVol[i].getX()-ToutLesAeroport[AvionEnVol[i].getTrajet()[1]].getLoca_x()) > -4
                             && (AvionEnVol[i].getX()-ToutLesAeroport[AvionEnVol[i].getTrajet()[1]].getLoca_x()) < 4)
                            &&((AvionEnVol[i].getY()-ToutLesAeroport[AvionEnVol[i].getTrajet()[1]].getLoca_y()) > -4
                               && (AvionEnVol[i].getY()-ToutLesAeroport[AvionEnVol[i].getTrajet()[1]].getLoca_y()) < 4)){

                            AvionEnVol[i].popFrontAvion();

                            cout << "Loca X: " << AvionEnVol[i].getX() << endl;
                            cout << "Loca Y: " << AvionEnVol[i].getY() << endl;
                            for (int j = 0; j < AvionEnVol[i].getTrajet().size(); ++j) {
                                cout << "Trajet " << j << " : " << AvionEnVol[i].getTrajet()[j] << endl;
                            }
                            cout << "Size : " << AvionEnVol[i].getTrajet().size();

                            AvionEnVol[i].setLocaX(ToutLesAeroport[AvionEnVol[i].getTrajet()[0]].getLoca_x());
                            AvionEnVol[i].setLocaY(ToutLesAeroport[AvionEnVol[i].getTrajet()[0]].getLoca_y());

                            /// Si avion à l'aeroport alors il ne vole plus
                            if (AvionEnVol[i].getTrajet().size() == 1){
                                /// Aterrissage en de l'avion i
                                AvionEnVol.erase(AvionEnVol.begin() + i);
                            }
                        }
                        else {
                            AvionEnVol[i].augmenteDistance(0);
                            AvionEnVol[i].setPositionDesign();
                        }

                    }*/

                    /// PAUSE
                    /*
                    std::chrono::seconds dura( 1);
                    std::this_thread::sleep_for( dura );



                    window.clear();
                    window.draw(sprite);
                    for (int i = 0; i < AvionEnVol.size(); ++i) {
                        window.draw(AvionEnVol[i].getDesignAvion());
                    }

                    window.display();





                    IciToutCePasse();*/
                }
                /// ici je peut recuperer nombre UT et le Trajet de l'avion
                // si depart paris et arrivé sydney trajet = paris,dubai,sydney
                // vecteur[0] = paris
                // vecteur[1] = dubai
                // vecteur[2] = sydney
                // vecteur[0] = 10   /// ici distance paris dubai
                // vecteur[1] = 15   /// ici distance dubai sydney
                //ne pas oublier de faire 1 seconde d'ecart entre chaque decollage


                //stackAvion.clear();
                //stackAvion[0].ParametrageGPSdijkstra();
                //stackAvion[0].trajet_de_lavion();
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
                while (compteur < 1000) {
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
                            std::cout<<"DEPART : "<<depart<<std::endl;
                            std::cout<<"ARRIVE : "<<arrive<<std::endl;
                            if(depart != arrive)
                            {
                                departDiffDarrive = true;
                            }
                        }

                        stackAvionDispo = ToutLesAeroport[depart].partir(depart, arrive);
                        nbAvionDispo = stackAvionDispo.size();
                        std::cout << " ICI " << nbAvionDispo;
                        if (nbAvionDispo == 0) {
                            std::cout << "cette aeroport ne possede pas d'avion pour ce voyage" << std::endl;
                            FinBoucleAlea = false;
                            toutlesaeroportsontvidecompteur = toutlesaeroportsontvidecompteur +1;
                            if(toutlesaeroportsontvidecompteur >= 7)
                            {
                                std::cout<<"il n'y a plus davion au sol dans aucun aerroport"<<std::endl;
                                toutlesaeroportsontvide = true;
                            }
                        } else if (nbAvionDispo >= 1) {
                            choixavion2 = 0;
                            FinBoucleAlea = true;
                            std::cout << " ICI 2 " << choixavion2 << std::endl;
                            //stackAvionDispo[choixavion2].setTrajetDeCetteAvionEnregistre(false);
                            stackAvionDispo[choixavion2].setdepart(depart);
                            stackAvionDispo[choixavion2].setarrive(arrive);
                            std::cout << stackAvionDispo[choixavion2].getdepart() << std::endl;
                            std::cout << stackAvionDispo[choixavion2].getarrive() << std::endl;
                            ToutLesAeroport[depart].decoler(stackAvionDispo[choixavion2]);
                        } /*else if (nbAvionDispo > 1) {
                                    choixavion2 = rand() % (nbAvionDispo - 1) + 0;
                                    FinBoucleAlea = true;
                                    std::cout << " ICI 2 " << choixavion2 << std::endl;
                                    stackAvionDispo[choixavion2].setdepart(depart);
                                    stackAvionDispo[choixavion2].setarrive(arrive);
                                    std::cout << stackAvionDispo[choixavion2].getdepart() << std::endl;
                                    std::cout << stackAvionDispo[choixavion2].getarrive() << std::endl;
                                    ToutLesAeroport[depart].decoler(stackAvionDispo[choixavion2]);
                                }*/


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

                    //////////////////////////////////////////////////


                    ///ici jai modifier des truc
                    for (int w = 0; w < ToutLesAeroport.size(); w++) {
                        ToutLesAeroport[w].icitoutcepasse();
                        std::vector<Avion> AvionQuiVontEtreEnVol;
                        AvionQuiVontEtreEnVol = ToutLesAeroport[w].ActualisationAvionDecoler();
                        for (int u = 0; u < AvionQuiVontEtreEnVol.size(); u++) {
                            AvionEnVol.push_back(AvionQuiVontEtreEnVol[u]);
                        }
                        AvionQuiVontEtreEnVol.clear();
                        ToutLesAeroport[w].nettoyervecteurAvionADecoler();
                    }

                    /*
                    if (AvionEnVol.size() != 0) {
                        std::cout << "==========================================" << std::endl;
                        std::cout << "Avion Disponible Pour Atterissage" << std::endl;
                        std::cout << "==========================================" << std::endl;
                        for (int d = 0; d < AvionEnVol.size(); d++) {
                            AvionEnVol[d].afficheAttribut();
                            std::cout << std::endl;
                        }
                        std::cout
                                << "entrer le nom de l'avion que voulez faire atterire (ce nom doit apparaitre dans la liste des avion disponible)"
                                << std::endl;
                        std::cin >> choixatterissage;
                        for (int z = 0; z < AvionEnVol.size(); z++) {
                            if (AvionEnVol[z].getNom() == choixatterissage) {
                                ToutLesAeroport[0].atterir(
                                        AvionEnVol[z]);// il atterit a paris automatiquement pour le moment
                                AvionEnVol.erase(AvionEnVol.begin() + z);
                            }
                        }

                    }
                    */

                    //std::cout << "ENTRER 1 POUR ARRETER LA SIMULATION" << std::endl;
                    //std::cout << "ENTRER 0 POUR CONTINUER LA SIMULATION" << std::endl;
                    //std::cin >> FIN;

                    ///
                    //std::cout<<"LA BIZARERIE NEST JAMAIS FINI"<<std::endl;


                    // apres le parametrage nous mettron le bool TrajetDeCetteAvionEnregistre en true et quand le vecteur trajet de l'avion sera vide on remmetra ce bool en false
                    for (int r = 0; r < AvionEnVol.size(); r++) {
                        if (!AvionEnVol[r].getTrajetDeCetteAvionEnregistre()) {
                            std::cout<<" JE PASSE ICI EST C TREES IMPORTANT"<<std::endl;
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
                        window.draw(AvionEnVol[i].getDesignAvion());
                    }



                    window.display();



                    std::cout<<"============================================="<<std::endl;
                    std::cout<<"AVION ACTUELLEMENT EN VOL"<<std::endl;
                    std::cout<<"============================================="<<std::endl;
                    for(int i = 0;i<AvionEnVol.size();i++)
                    {
                        std::map<string,int> tempo;
                        tempo = AvionEnVol[i].getEtatAvion();
                        std::cout<<AvionEnVol[i].getNom()<<" est en Vol depuis "<<tempo["Vol"]<<" UT est atterit a "<<" il vole a "<<AvionEnVol[i].getaltitudeAvion()<<" metre"<<" sa couleur est "<< AvionEnVol[i].getCouleurAvion()<<std::endl;//mettre le nombre d'ut à atteindre
                    }
                    std::cout<<"============================================="<<std::endl;
                    compteur = compteur+1;

                    //IciToutCePasse();

                }

            }

                break;
            case 3: {
                if (stackAvion.size() == 0) {
                    std::cout
                            << "vous n'avez pas choisi d'avion on ne peut donc pas afficher ces caracteristique"
                            << std::endl;
                } else {
                    stackAvion[0].afficheAttribut();
                }
            }

                break;


        }

        }

    } while (choixmenu != 4);
    }
}
