#include "Classes.h"



void aeroport::afficheLesAvionSurPlace()
{
    for(int m =0; m<AvionAuParking.size(); m++)
    {
        std::cout<<std::endl;
        AvionAuParking[m].afficheAttribut();
    }
}
/// nouvelle methode
std::vector<Avion> aeroport::partir(int depart,int arrive)
{
    bool Dispo;
    std::vector<Avion> AvionDispoPourTrajet;

    for(int x = 0;x<AvionAuParking.size();x++)
    {
        AvionAuParking[x].ParametrageGPSdijkstra();   // paramettre djikstra en fonction du type de l'avion
        Dispo = AvionAuParking[x].Verifietrajet_de_lavion(depart,arrive);
        if(Dispo == 1)
        {
            AvionDispoPourTrajet.push_back(AvionAuParking[x]);
        }

    }
    std::cout<<"=================================="<<std::endl;
    std::cout<<"AVION DISPONIBLE POUR CE TRAJET"<<std::endl;
    std::cout<<"=================================="<<std::endl;
    for(int x = 0;x<AvionDispoPourTrajet.size();x++)
    {
        AvionDispoPourTrajet[x].afficheAttribut();
        std::cout<<std::endl;
    }
    return AvionDispoPourTrajet;
}


void aeroport::icitoutcepasse()
{
    std::cout<<"VOICI L'AVION QUI VA DECOLLER EST "<<std::endl;
    std::cout<<std::endl;
    //<<File_Atteente_Decolage[0].getNom()<<
    for(int y = 0;y<File_Atteente_Atterissage.size();y++)// on regarde si l'avioon peut atterir
    {
        nb_piste_utiliseATM = (atterissageEnCours.size()+decolageEnCours.size());
        nb_places_sol_DisponibleATM = (nb_places_sol-AvionAuParking.size());
        map<string,int> EtatActuel;
        EtatActuel = File_Atteente_Atterissage[y].getEtatAvion();
        if((EtatActuel["Attend"] >= boucle_attente)&&(nb_piste_utiliseATM<nb_piste)&&(nb_places_sol_DisponibleATM>0))// si l'avion à attendu les UT necessaire pour atterire et qu'il y à une piste de libre et une place libre alors atterir
        {
            atterissageEnCours.push_back(File_Atteente_Atterissage[y]);
            File_Atteente_Atterissage.erase(File_Atteente_Atterissage.begin()+y);
        }
    }

    for(int y = 0;y<atterissageEnCours.size();y++)// on regarde si l'avion à  atterit
    {
        map<string,int> EtatActuel;
        EtatActuel = atterissageEnCours[y].getEtatAvion();
        if(EtatActuel["Atterit"] = temps_atter)// si l'avion à finit d'atterir alors
        {
            AvionAuParking.push_back(atterissageEnCours[y]);
            atterissageEnCours.erase(atterissageEnCours.begin()+y);
        }
    }


    for(int y = 0;y<File_Atteente_Decolage.size();y++)// on regarde si l'avion peut decoler
    {
        nb_piste_utiliseATM = (atterissageEnCours.size()+decolageEnCours.size());
        map<string,int> EtatActuel;
        EtatActuel = File_Atteente_Decolage[y].getEtatAvion();
        std::cout<<"ON RENTRE ICI ?"<<std::endl;
        std::cout<<"ici c nb piste utiliser maintenant "<<nb_piste_utiliseATM<<std::endl;
        std::cout<<"ici c nb piste dans aeroport "<<nb_piste<<std::endl;
        std::cout<<"ici nous avons valeur etat sol "<<EtatActuel["Sol"]<<std::endl;
        std::cout<<"ici nous avons valeur etat sol a atteindre avant decolage "<<attente_sol<<std::endl;
        if((nb_piste_utiliseATM<nb_piste)&&(EtatActuel["Sol"]>=attente_sol))// si la piste est libre alors avion decole
        {
            Accede_au_piste.push_back(File_Atteente_Decolage[y]);
            std::cout<<"cette avion va ver la piste  "<<Accede_au_piste[0].getNom()<<std::endl;
            AvionAuParking.erase(AvionAuParking.begin()+y);
            File_Atteente_Decolage.erase(File_Atteente_Decolage.begin()+y);
        }
    }

    for(int y = 0;y<Accede_au_piste.size();y++)// on regarde si l'avion a fini de decoler
    {
        map<string,int> EtatActuel;
        EtatActuel = Accede_au_piste[y].getEtatAvion();
        nb_piste_utiliseATM = (atterissageEnCours.size()+decolageEnCours.size());
        if((EtatActuel["AccedePiste"] >= temps_acces_piste)&&(nb_piste_utiliseATM<nb_piste))// si il y a une piste libre alors on s'engage
        {
            decolageEnCours.push_back(Accede_au_piste[y]);
            Accede_au_piste.erase(Accede_au_piste.begin()+y);
        }
    }


    for(int y = 0;y<decolageEnCours.size();y++)// on regarde si l'avion a fini de decoler
    {
        map<string,int> EtatActuel;
        EtatActuel = decolageEnCours[y].getEtatAvion();
        if(EtatActuel["Decole"] = temps_atter)// temp atterissage = temp decolage
        {
            ///AvionenVol.push_back(decolageEnCours[y]); on à pas de vecteur en vol donc on va juste le supprimer du vecteur decolage en cours et
            decolageEnCours.erase(decolageEnCours.begin()+y);
        }
    }



    for(int y = 0;y<File_Atteente_Decolage.size();y++)/// ici on incremente le temps passer au sol par les avion
    {
        map<string,int> EtatActuel;
        EtatActuel = File_Atteente_Decolage[y].getEtatAvion();
        EtatActuel["Sol"] = EtatActuel["Sol"] + 1;
        EtatActuel["Vol"] = 0;
        EtatActuel["Atterit"] = 0;
        EtatActuel["Decole"] = 0;
        EtatActuel["Attend"] = 0;
        EtatActuel["AccedePiste"] = 0;
        std::cout<<File_Atteente_Decolage[y].getNom()<<" est au sol"<<std::endl;
        File_Atteente_Decolage[y].setEtatAvion(EtatActuel);
    }
    for(int y = 0;y<AvionAuParking.size();y++)/// ici on incremente le temps passer au sol par les avion
    {
        map<string,int> EtatActuel;
        EtatActuel = AvionAuParking[y].getEtatAvion();
        EtatActuel["Sol"] = EtatActuel["Sol"] + 1;
        EtatActuel["Vol"] = 0;
        EtatActuel["Atterit"] = 0;
        EtatActuel["Decole"] = 0;
        EtatActuel["Attend"] = 0;
        EtatActuel["AccedePiste"] = 0;
        std::cout<<AvionAuParking[y].getNom()<<" est au sol"<<std::endl;
        AvionAuParking[y].setEtatAvion(EtatActuel);
    }
    for(int y = 0;y<Accede_au_piste.size();y++)/// ici on incremente le temps passer au AccedePiste par les avion
    {
        map<string,int> EtatActuel;
        EtatActuel = Accede_au_piste[y].getEtatAvion();
        EtatActuel["AccedePiste"] = EtatActuel["AccedePiste"] + 1;
        EtatActuel["Vol"] = 0;
        EtatActuel["Atterit"] = 0;
        EtatActuel["Decole"] = 0;
        EtatActuel["Attend"] = 0;
        EtatActuel["Sol"] = 0;
        std::cout<<Accede_au_piste[y].getNom()<<" accede au piste"<<std::endl;
    }
    for(int y = 0;y<decolageEnCours.size();y++)/// ici on incremente le temps passer au Decole par les avion
    {
        map<string,int> EtatActuel;
        EtatActuel = decolageEnCours[y].getEtatAvion();
        EtatActuel["Decole"] = EtatActuel["Decole"] + 1;
        EtatActuel["Vol"] = 0;
        EtatActuel["Atterit"] = 0;
        EtatActuel["AccedePiste"] = 0;
        EtatActuel["Attend"] = 0;
        EtatActuel["Sol"] = 0;
        std::cout<<decolageEnCours[y].getNom()<<" Decole"<<std::endl;
    }
    for(int y = 0;y<atterissageEnCours.size();y++)/// ici on incremente le temps passer au Atterit par les avion
    {
        map<string,int> EtatActuel;
        EtatActuel = atterissageEnCours[y].getEtatAvion();
        EtatActuel["Atterit"] = EtatActuel["Atterit"] + 1;
        EtatActuel["Vol"] = 0;
        EtatActuel["Decole"] = 0;
        EtatActuel["AccedePiste"] = 0;
        EtatActuel["Attend"] = 0;
        EtatActuel["Sol"] = 0;
        std::cout<<atterissageEnCours[y].getNom()<<" Atterit"<<std::endl;
    }
    for(int y = 0;y<File_Atteente_Atterissage.size();y++)/// ici on incremente le temps passer au Attend par les avion
    {
        map<string,int> EtatActuel;
        EtatActuel = File_Atteente_Atterissage[y].getEtatAvion();
        EtatActuel["Attend"] = EtatActuel["Attend"] + 1;
        EtatActuel["Vol"] = 0;
        EtatActuel["Decole"] = 0;
        EtatActuel["AccedePiste"] = 0;
        EtatActuel["Atterit"] = 0;
        EtatActuel["Sol"] = 0;
        std::cout<<File_Atteente_Atterissage[y].getNom()<<" Attend"<<std::endl;
    }

}


void aeroport::atterir(Avion Avion_en_Aterissage)
{
    // il faudrai le supprimer du vecteur en vol quand on auras accès à celui-ci
    File_Atteente_Atterissage.push_back(Avion_en_Aterissage);
}

/*
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

*/




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

///nouveau
void aeroport::ActualisationCompteurUTATTERISSAGE()
{

}
void aeroport::ActualisationCompteurUTSOL()/// cette methode va etre appellé a chaque boucle du jeu
{
    map<string,int> changement;
    for(int x =0;x<AvionAuParking.size();x++)
    {
        changement = AvionAuParking[x].getEtatAvion();
        changement["Sol"] = changement["Sol"]+1;
        AvionAuParking[x].setEtatAvion(changement);
    }
}
void aeroport::ActualisationCompteurUTDECOLAGE()
{

}

void aeroport::decoler(Avion Avion_en_Decolage)
{
    File_Atteente_Decolage.push_back(Avion_en_Decolage);
    std::cout<<"VOICI L'AVION QUI VA DECOLLER EST "<<File_Atteente_Decolage[0].getNom()<<std::endl;
    std::cout<<std::endl;
}

/// verifier cette fonction
void aeroport::actualisationDecolageToutLesAeroport()/// fonction appelé toute les 1 UT pour tout les aeroport
{
    map<string,int> changement;
    changement["Sol"] = 0;
    if(nb_piste_utiliseATM < nb_piste)
    {
        decolageEnCours.push_back(File_Atteente_Decolage[0]);
        for(int ma =0;ma<AvionAuParking.size();ma++)
        {
            if((AvionAuParking[ma].getNom()) == (File_Atteente_Decolage[0].getNom()))
            {
                AvionAuParking.erase(AvionAuParking.begin()+ma);
                AvionAuParking[ma].setEtatAvion(changement);
            }
        }
        File_Atteente_Decolage.erase(File_Atteente_Decolage.begin());
    }
}
///=========


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


