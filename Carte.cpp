#include "Classes.h"
//cc
void Carte::IciToutCePasse()
{
    for(int y = 0;y<AvionEnVol.size();y++)/// ici on incremente le temps passer au sol par les avion
    {
        map<string,int> EtatActuel;
        EtatActuel = AvionEnVol[y].getEtatAvion();
/*
        if(EtatActuel["Vol"]  == nombreUTdeAeroportdepartAarvvie)// ici on verifie que l'avion à atteint le nombre de UT qu'il devait faire
        {
            // ici on doit enlever l'avion du vecteur AvionEnVol pour le mettre dans le vecteur File_Atteente_Atterissage
        }
      else if(EtatActuel["Vol"]  != nombreUTdeAeroportdepartAarvvie)
        {
            EtatActuel["Vol"] = EtatActuel["Vol"] + 1;
            EtatActuel["Sol"] = 0;
            EtatActuel["Atterit"] = 0;
            EtatActuel["Decole"] = 0;
            EtatActuel["Attend"] = 0;
            EtatActuel["AccedePiste"] = 0;
            AvionEnVol[y].setEtatAvion(EtatActuel);
        }
*/
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



void Carte::derouledujeu()
{
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
    std::vector<Avion> stackAvion;
    std::vector<Avion> stackAvion111;
    std::vector<Avion> stackAvionDispo;
    Avion AvionTest("Long_Courrier");
    std::string TypeAvion;
    int choixmenu;
    std::string choixavion1;
    /// faire un do while mais fleme je vais dodo
/*
    window.clear();

    while (window.isOpen()) {
        sf::Event event;
  */

    do{
        //while (window.pollEvent(event)) {

        std::cout<<std::endl;
        std::cout<<"=========================================Menu========================================="<<std::endl;
        std::cout<<"Si vous voulez vous deplacer appuyer sur 1"<<std::endl;
        //std::cout<<"Si vous voulez choisir votre avion appuyer sur 2"<<std::endl;
        std::cout<<"Si vous voulez afficher les caracteristique de votre avion appuyer sur 3"<<std::endl;
        std::cout<<"quitter appuyer sur 4"<<std::endl;
        std::cout<<"======================================================================================"<<std::endl;
        std::cin>>choixmenu;
        int FIN = 0;

/// ici je modifie
        switch(choixmenu)
        {
            case 1:
            {

                int depart;
                int arrive;

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
                std::cin >> arrive;
                /*stackAvionDispo = ToutLesAeroport[depart].partir(depart, arrive);
                std::cout
                        << "entrer le nom de l'avion que voulez faire decoler (ce nom doit apparaitre dans la liste des avion disponible)"
                        << std::endl;
                std::cin >> choixavion1;
            for (int z = 0; z < stackAvionDispo.size(); z++) {
                if (stackAvionDispo[z].getNom() == choixavion1) {
                    ToutLesAeroport[depart].decoler(stackAvionDispo[z]);
                }
            }
            while(FIN != 1) {

                for (int w = 0; w < ToutLesAeroport.size(); w++) {
                    ToutLesAeroport[w].icitoutcepasse();
                }
                std::cout << "ENTRER 1 POUR ARRETER LA SIMULATION" << std::endl;
                std::cout << "ENTRER 0 POUR CONTINUER LA SIMULATION" << std::endl;
                std::cin >> FIN;
                }*/

                stackAvion111.push_back(AvionTest);
                stackAvion111[0].ParametrageGPSdijkstra();
                stackAvion111[0].setTrajet(stackAvion111[0].trajet_de_lavion(depart,arrive));
                stackAvion111[0].envol();
                vector<int> pp;

                for (int i = stackAvion111[0].getTrajet().size() - 1;
                     i >= 0; --i) { //inversion trajet pour plus de clareté
                    pp.push_back(stackAvion111[0].getTrajet()[i]);
                }
                stackAvion111[0].setTrajet(pp);



                for (int i = 0; i < stackAvion111[0].getTrajet().size() - 1; ++i) {
                    //cout << stackAvion[0].getTrajet()[i] << " ";
                    stackAvion111[0].setnbUT(ToutLesAeroport[stackAvion111[0].getTrajet()[i]].getDistance(
                            conversionSommetVille(stackAvion111[0].getTrajet()[i]) + "->" +
                            conversionSommetVille(stackAvion111[0].getTrajet()[i + 1])) / 200);
                    cout << stackAvion111[0].getnbUT()[i] << endl;
                    float distance = ToutLesAeroport[stackAvion111[0].getTrajet()[i]].getDistance(
                            conversionSommetVille(stackAvion111[0].getTrajet()[i]) + "->" +
                            conversionSommetVille(stackAvion111[0].getTrajet()[i + 1]));

                    stackAvion111[0].setAvencement(
                            (ToutLesAeroport[stackAvion111[0].getTrajet()[i + 1]].getLoca_x() -
                             ToutLesAeroport[stackAvion111[0].getTrajet()[i]].getLoca_x()) /
                            (distance / 200),
                            (ToutLesAeroport[stackAvion111[0].getTrajet()[i + 1]].getLoca_y() -
                             ToutLesAeroport[stackAvion111[0].getTrajet()[i]].getLoca_y()) /
                            (distance / 200));
                    //std::cout<<"Distance = "<<distance<<std::endl;
                    cout << stackAvion111[0].getAvnecement_x()[i] << " " << stackAvion111[0].getAvnecement_y()[i]
                         << endl;


                }


                //stackAvion.clear();
                //stackAvion[0].ParametrageGPSdijkstra();
                //stackAvion[0].trajet_de_lavion();
            }
                break;
            case 2:
            {

                TypeAvion = choixavion();
                Avion AvionTest1(TypeAvion);
                stackAvion.push_back(AvionTest1);
                std::cout<<"Tres bon choix"<<std::endl;

            }

                break;
            case 3:
            {
                if(stackAvion.size() == 0)
                {
                    std::cout<<"vous n'avez pas choisi d'avion on ne peut donc pas afficher ces caracteristique"<<std::endl;
                }
                else
                {
                    stackAvion[0].afficheAttribut();
                }
            }

                break;


        }

        /* window.clear();
         window.draw(imageFond);

     }

     window.display();

     ///Timer en secondes:
     std::chrono::seconds dura( 1);
     std::this_thread::sleep_for( dura );*/

    }while(choixmenu != 4);
    //}
}
