#include "Classes.h"

string conversionSommetVille(int nombre){
    switch (nombre) {
        case 0:
            return "Paris";
            break;

        case 1:
            return "Tallinn";
            break;

        case 2:
            return "Tokyo";
            break;

        case 3:
            return "Sydney";
            break;

        case 4:
            return "Tananarive";
            break;

        case 5:
            return "Chicago";
            break;

        case 6:
            return "Dubai";
            break;

        case 7:
            return "Santiago";
            break;

        default: "ERREUR";
            break;
    }
    return "ERREUR";
}

std::string choixavion()
{
    int choixA;
    std::string TypeAvionChoix;
    std::cout<<"Veuillez choisir le type d'avion avec lequel vous voulez voler"<<std::endl;
    std::cout<<"pour choisir un avion de type cours courrier entrer 1"<<std::endl;
    std::cout<<"pour choisir un avion de type moyen courrier entrer 2"<<std::endl;
    std::cout<<"pour choisir un avion de type long courrier entrer 3"<<std::endl;
    std::cin>>choixA;
    if(choixA == 1)
    {
        TypeAvionChoix = "Cours_Courrier";
    }
    if(choixA == 2)
    {
        TypeAvionChoix = "Moyen_Courrier";
    }
    if(choixA == 3)
    {
        TypeAvionChoix = "Long_Courrier";
    }
    return TypeAvionChoix;
}


std::vector<aeroport> remplirAeroAleatoirement(std::vector<aeroport> ListeAeroport)
{
    for(int i= 0;i<ListeAeroport.size();i++)
    {
        int nbAvionInitial;
        nbAvionInitial = ListeAeroport[i].getternb_places_sol();
        srand((unsigned int)time(0));
        int nbAvionDansAreo = rand()%nbAvionInitial +1;
        for(int x=0;x<nbAvionDansAreo;x++)
        {
            int TypeAvion = rand()%3 +1;

            if(TypeAvion == 1)
            {
                Avion AvionInitialisation("Cours_Courrier");
                ListeAeroport[i].remplirAvionParking(AvionInitialisation);
            }
            else if(TypeAvion == 2)
            {
                Avion AvionInitialisation("Moyen_Courrier");
                ListeAeroport[i].remplirAvionParking(AvionInitialisation);
            }
            else if(TypeAvion == 3)
            {
                Avion AvionInitialisation("Long_Courrier");
                ListeAeroport[i].remplirAvionParking(AvionInitialisation);
            }
        }
    }
    return ListeAeroport;

}







