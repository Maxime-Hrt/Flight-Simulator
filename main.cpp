#include "Classes.h"
using namespace sf;

//erxgx'"tgerzgxerz
//zgefx

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML Application");
    sf::Texture imageFond_texture;

    if(imageFond_texture.loadFromFile("/Users/mael/Desktop/ece/piscine/Piscine-Project/Images/Long_Courrier.png", IntRect(0, 0, WIDTH, HEIGHT))){
        //Message d'erreur t'as vu
    }
    Sprite imageFond;
    imageFond.setTexture(imageFond_texture);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(imageFond);
        window.display();
    }
}

/*
int main(){
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "Simulateur tour de contrôle");

    Texture imageFond_texture;
    if(imageFond_texture.loadFromFile("/Users/maxime_hrt/Documents/Ing2/Informatique/Ing2Info/TheorieDesGraphes/Swimming_pool/Images/Long_Courrier.png", IntRect(0, 0, WIDTH, HEIGHT))){
        //Message d'erreur t'as vu
    }
    Sprite imageFond;
    imageFond.setTexture(imageFond_texture);

    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(imageFond);
        window.display();
    }

    return 0;
}
*/


/**
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

    aero = remplirAeroAleatoirement(aero);
    for(int z=0;z<aero.size();z++)
    {
        std::cout<<"==========================================="<<std::endl;
        std::cout<<"Aeroport "<<z<<std::endl;
        std::cout<<"===========================================";
        aero[z].afficheLesAvionSurPlace();
    }



/// faire un do while mais fleme je vais dodo
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
                stackAvion[0].trajet_de_lavion();
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
*/