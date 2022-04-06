#include "Classes.h"

void aeroport::afficheLesAvionSurPlace()
{
    for(int m =0; m<AvionAuParking.size(); m++)
    {
        std::cout<<std::endl;
        AvionAuParking[m].afficheAttribut();
    }
}

void aeroport::atterir(Avion Avion_en_Aterissage)
{
    File_Atteente_Atterissage.push_back(Avion_en_Aterissage);
}

void ActualisationCompteur() /// appeler fonction toute les 1 UT
{

}
/// faire test avec plein de COUT partout pour verifier que l'avion passe bien par chaque etape et quil manque juste a metre le etemps en jeu
void aeroport::actualisationAtterissageToutLesAeroport()/// fonction appelé toute les 1 UT pour tout les aeroport
{
    if((nb_piste_utiliseATM < nb_piste)&&(nb_places_sol_DisponibleATM > 0))
    {
        atterissageEnCours.push_back(File_Atteente_Atterissage[0]);
        File_Atteente_Atterissage.erase(File_Atteente_Atterissage.begin());/// verifier si erase decale tout de 1
        ///on attend le temps de atterissage de l'aeroport en UT PUIS:
        AvionAuParking.push_back(atterissageEnCours[0]);
        atterissageEnCours.erase(atterissageEnCours.begin());/// verifier si erase decale tout de 1
    }
}

void aeroport::decoler(Avion Avion_en_Decolage)
{
    File_Atteente_Decolage.push_back(Avion_en_Decolage);
}
/// verifier cette fonction
void aeroport::actualisationDecolageToutLesAeroport()/// fonction appelé toute les 1 UT pour tout les aeroport
{
    int FIN = 0;
    int compteur = 0;
    if(nb_piste_utiliseATM < nb_piste)
    {
        decolageEnCours.push_back(File_Atteente_Decolage[0]);
        // supprimer l'avion qui decolle des place de parking
        do
        {
            for(int z=0; z<decolageEnCours.size(); z++)
            {
                if(AvionAuParking[compteur].getType() == decolageEnCours[z].getType()) ///probleme de boucle on verifie pas tout les avions dans la liste d'attente de decolage
                {
                    AvionAuParking.erase(AvionAuParking.begin()+compteur);
                    FIN = 1;
                }

            }
            compteur++;
        }
        while(FIN != 1);
        File_Atteente_Decolage.erase(File_Atteente_Decolage.begin());
        ///on attend le temps de decollage de l'aeroport en UT PUIS:
        decolageEnCours.erase(decolageEnCours.begin());

    }
}




int aeroport::getternb_piste()
{
    return nb_piste;
}


int aeroport::getternb_places_sol()
{
    return nb_places_sol;
}

void aeroport::remplirAvionParking(Avion Avion_Atterissant)
{
    AvionAuParking.push_back(Avion_Atterissant);
}



aeroport::~aeroport() {}

aeroport::aeroport(int _num_sommet, string _nom, int _loca_x, int _loca_y, int _nb_piste, int _nb_places_sol, int _attente_sol, int _temps_acces_piste, int _temps_atter, int _anti_collision, int _boucle_attente, int _nb_arrete, map<string, int> _arrete)
        :num_sommet(_num_sommet), nom(_nom), loca_x(_loca_x), loca_y(_loca_y), nb_piste(_nb_piste), nb_places_sol(_nb_places_sol), attente_sol(_attente_sol), temps_acces_piste(_temps_acces_piste), temps_atter(_temps_atter), anti_collision(_anti_collision), boucle_attente(_boucle_attente), nb_arrete(_nb_arrete), arrete(_arrete)
{}





void aeroport::InitialiseAeroport()
{
    srand((unsigned int)time(0));
    int nbAvionDansAreo = rand()%nb_places_sol +1;
    for(int x=0; x<nbAvionDansAreo; x++)
    {
        int TypeAvion = rand()%3 +1;

        if(TypeAvion == 1)
        {
            stringstream conversion;
            std::string str;
            int z;
            z = x;
            conversion << z;
            conversion >> str;
            Avion AvionInitialisation("Cours_Courrier");
            AvionInitialisation.setNom(nom+"Cours_Courrier"+str);
            AvionAuParking.push_back(AvionInitialisation);
        }
        else if(TypeAvion == 2)
        {
            stringstream conversion;
            std::string str;
            int z;
            z = x;
            conversion << z;
            conversion >> str;
            Avion AvionInitialisation("Moyen_Courrier");
            AvionInitialisation.setNom(nom+"Moyen_Courrier"+str);
            AvionAuParking.push_back(AvionInitialisation);
        }
        else if(TypeAvion == 3)
        {
            stringstream conversion;
            std::string str;
            int z;
            z = x;
            conversion << z;
            conversion >> str;
            Avion AvionInitialisation("Long_Courrier");
            AvionInitialisation.setNom(nom+"Long_Courrier"+str);
            AvionAuParking.push_back(AvionInitialisation);
        }
    }
}
