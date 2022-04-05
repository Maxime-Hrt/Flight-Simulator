#include "Classes.h"

void aeroport::afficheLesAvionSurPlace()
{
    for(int m =0;m<AvionAuParking.size();m++)
    {
        std::cout<<std::endl;
        AvionAuParking[m].afficheAttribut();
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

