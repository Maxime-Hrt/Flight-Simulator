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
/*
         vector<float> getnbUT(){
        return nbUT;
    }
    vector<int> getTrajet(){
        return trajet;
    }*/
        Trajet = AvionEnVol[y].getTrajet();
        UT = AvionEnVol[y].getnbUT();

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
    sprite.setTexture(texture); //image dans le sprite

    std::vector <Avion> stackAvion;
    std::vector <Avion> stackAvion111;
    std::vector <Avion> stackAvionDispo;
    Avion AvionTest("Long_Courrier");
    std::string TypeAvion;
    int choixmenu;
    std::string choixatterissage;
    std::string choixavion1;
    /// faire un do while mais fleme je vais dodo
/*
    window.clear();
    while (window.isOpen()) {
        sf::Event event;
  */
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

                //std::cin >> choixmenu;
                int FIN = 0;

                /// Tu verras plus tard
                choixmenu = 1;

/// ici je modifie
                switch (choixmenu) {
                    case 1: {
                        while (FIN != 1) {
                            int nouveaudecolage = 0;
                            int depart;
                            int arrive;
                            std::cout << "voulez vous faire decolez un nouvelle avion" << std::endl;
                            std::cout << "1 oui" << std::endl;
                            std::cout << "2 non" << std::endl;
                            std::cin >> nouveaudecolage;
                            if (nouveaudecolage == 1) {
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
                                std::cout
                                        << "entrer le nom de l'avion que voulez faire decoler (ce nom doit apparaitre dans la liste des avion disponible)"
                                        << std::endl;
                                std::cin >> choixavion1;
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

                            std::cout << "ENTRER 1 POUR ARRETER LA SIMULATION" << std::endl;
                            std::cout << "ENTRER 0 POUR CONTINUER LA SIMULATION" << std::endl;
                            std::cin >> FIN;

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

                            */

                            window.clear();
                            window.draw(sprite);
                            for (int i = 0; i < AvionEnVol.size(); ++i) {
                                window.draw(AvionEnVol[i].getDesignAvion());
                            }

                            window.display();





                            //IciToutCePasse();
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

                        TypeAvion = choixavion();
                        Avion AvionTest1(TypeAvion);
                        stackAvion.push_back(AvionTest1);
                        std::cout << "Tres bon choix" << std::endl;

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