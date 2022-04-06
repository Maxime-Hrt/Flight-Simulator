#include "Classes.h"

using namespace std;



/*
int main()
{
    string cour_courrier = "/Users/mael/Desktop/ece/piscine/Piscine-Project/Images/court_courier.png";
    string moyen_courrier ="/Users/mael/Desktop/ece/piscine/Piscine-Project/Images/moyen_courier.png";
    string long_courrier = "/Users/mael/Desktop/ece/piscine/Piscine-Project/Images/long_courier.png";


    string cour_courrier = "/Users/maxime_hrt/Documents/Ing2/Informatique/Ing2Info/TheorieDesGraphes/Swimming_pool/Images/court_courier.png";
    string moyen_courrier ="/Users/maxime_hrt/Documents/Ing2/Informatique/Ing2Info/TheorieDesGraphes/Swimming_pool/Images/moyen_courier.png";
    string long_courrier = "/Users/maxime_hrt/Documents/Ing2/Informatique/Ing2Info/TheorieDesGraphes/Swimming_pool/Images/long_courier.png";

    image(long_courrier);
    return 0;
}

*/




int main() {


    vector<aeroport> aero;
    std::vector<Avion> stackAvion;
    std::string TypeAvion;
    int choixmenu;

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
            aero.push_back(tem);
        }
    }
    else {
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
    }

    //aero = remplirAeroAleatoirement(aero);
    for(int z=0;z<aero.size();z++)
    {
        aero[z].InitialiseAeroport();
        std::cout<<"==========================================="<<std::endl;
        std::cout<<"Aeroport "<<z<<std::endl;
        std::cout<<"===========================================";
        aero[z].afficheLesAvionSurPlace();
    }



    do{
        std::cout<<std::endl;
        std::cout<<"=========================================Menu========================================="<<std::endl;
        std::cout<<"Si vous voulez vous deplacer appuyer sur 1"<<std::endl;
        std::cout<<"Si vous voulez choisir votre avion appuyer sur 2"<<std::endl;
        std::cout<<"Si vous voulez afficher les caracteristique de votre avion appuyer sur 3"<<std::endl;
        std::cout<<"quitter appuyer sur 4"<<std::endl;
        std::cout<<"======================================================================================"<<std::endl;
        std::cin>>choixmenu;

        switch(choixmenu)
        {
            case 1:
            {
                if(stackAvion.size() == 0)
                {
                    std::cout<<"vous n'avez pas choisi d'avion avant de vous deplacer on vous a donc attribuer un avion cours courrier par default"<<std::endl;
                    Avion AvionTest("Cours_Courrier");
                    stackAvion.push_back(AvionTest);
                }
                stackAvion[0].ParametrageGPSdijkstra();
                stackAvion[0].setTrajet(stackAvion[0].trajet_de_lavion());
                stackAvion[0].envol();
                vector<int> pp;

                for (int i = stackAvion[0].getTrajet().size()-1; i >= 0; --i) { //inversion trajet pour plus de clareté
                    pp.push_back(stackAvion[0].getTrajet()[i]);
                }
                stackAvion[0].setTrajet(pp);

                for (int i = 0; i < stackAvion[0].getTrajet().size()-1; ++i) {
                    //cout << stackAvion[0].getTrajet()[i] << " ";

                    int distance = aero[stackAvion[0].getTrajet()[i]].getDistance(conversionSommetVille(stackAvion[0].getTrajet()[i])+"->"+conversionSommetVille(stackAvion[0].getTrajet()[i+1]));
                    stackAvion[0].setnbUT(distance/200);
                }



            }
                break;
            case 2:
            {
                stackAvion.clear();
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
    }while(choixmenu != 4);

    return 0;
}
