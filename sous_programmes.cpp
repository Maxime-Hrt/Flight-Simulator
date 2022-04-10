#include "Classes.h"
//cc

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
