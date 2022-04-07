#ifndef SWIMMING_POOL_CLASSES_H
#define SWIMMING_POOL_CLASSES_H




#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <sstream>
#include <thread>
#include <chrono>
#include <SFML/Graphics.hpp>
#define WIDTH 1707
#define HEIGHT 1067
using namespace std;

///nouveau



class Avion
{
private:
    /// nouveau
    map<string,int> EtatAvion; // Vol,Sol,Atterit,Decole,Attend,AccedePiste
    vector<Avion> AvionEnVOl;
    vector<Avion> AvionEnAttente;
    ///===============
    std::string type;
    std::string nomAvion;
    int consomation;
    int reservoir;
    //int positionActuelle; ///la position de l'avion dit dans quel aeroport se trouve l'avion
    float loca_x, loca_y;
    int cost[100][100], nbs, Sommet_, Adjacence, ponderation_;
    int DistanceAutonomie;
    vector<int> trajet;
    int etat_avion;  ///0 au sol ; 1 en l'air ;
    vector<float> nbUT;
    vector<float> avencement_x, avencement_y;
    bool PeutFaireVoyage;
public:
    Avion();
    Avion(std::string type);
    ~Avion();
    void ParametrageGPSdijkstra();
    int getMin(int dist[], bool visited[]);
    vector<int> display(int dist[], int par[], int end);
    vector<int> dijkstra(int src , int end);
    vector<int> trajet_de_lavion(int depart,int arrive);
    void afficheAttribut();
    std::string getType();
    void setNom(std::string nouveauNom);
    ///nouveau aussi
    std::string getNom();
    void setEtatAvion(map<string,int> MAJEtatAvion);
    map<string,int> getEtatAvion();
    void ActualisationCompteurUTVOL();
    void ActualisationCompteurUTATTENTE();

    bool getPeutFaireVoyage()
    {
        return PeutFaireVoyage;
    }

    vector<int> getTrajet(){
        return trajet;
    }
    void setTrajet(vector<int> _trajet){
        trajet=_trajet;
    }
    void envol(){
        etat_avion=1;
    }
    void ausol(){
        etat_avion=0;
    }
    void setnbUT(float _nbUT){
        nbUT.push_back(_nbUT);
    }
    vector<float> getnbUT(){
        return nbUT;
    }
    void augmenteDistance(int i){
        loca_x += avencement_x[i];
        loca_y += avencement_y[i];
    }
    void setAvencement(float x, float y){

        avencement_y.push_back(y);
        avencement_x.push_back(x);
    }
    vector <float> getAvnecement_x(){
        return avencement_x;
    }
    vector <float> getAvnecement_y(){
        return avencement_y;
    }

};
///nouveau




class aeroport{
private:
    int num_sommet;
    string nom;
    int loca_x;
    int loca_y;
    int nb_piste;
    int nb_places_sol;
    int attente_sol;
    int temps_acces_piste;
    int temps_atter;
    int anti_collision;
    int boucle_attente;
    int nb_arrete;
    map<string, int> arrete;
    std::vector<Avion> AvionAuParking;
    int nb_piste_utiliseATM; /// est egal à atterissageEnCours.size()+decolageEnCours.size()
    int nb_places_sol_DisponibleATM; /// est egal nb_places_sol-AvionAuParking.size()
    std::vector<Avion> atterissageEnCours; /// les avions reste dans ce vecteur un certains temps avant de ce garer
    std::vector<Avion> decolageEnCours; /// les avions reste dans ce vecteur un certains temps avant de decoller completement de l'aeroport
    std::vector<Avion> File_Atteente_Atterissage;/// ici stocker les avion en attente pour atterir par ordre d'urgence(manque d'essence etc)
    std::vector<Avion> File_Atteente_Decolage;
    std::vector<Avion> Accede_au_piste;

public:
    aeroport();
    aeroport(int _num_sommet, string _nom, int _loca_x, int _loca_y, int _nb_piste, int _nb_places_sol, int _attente_sol, int _temps_acces_piste, int _temps_atter, int _anti_collision, int _boucle_attente, int _nb_arrete, map<string, int> _arrete);
    ~aeroport();
    void remplirAvionParking(Avion Avion_Atterissant);
    int getternb_piste();
    int getternb_places_sol();
    string getterNom();
    int getNum_sommet();
    void atterir(Avion Avion_en_Aterissage);
    void afficheLesAvionSurPlace();
    void actualisationAtterissageToutLesAeroport();
    void decoler(Avion Avion_en_Decolage);
    void actualisationDecolageToutLesAeroport();
    void InitialiseAeroport();
    std::vector<Avion> partir(int depart,int arrive);
    ///nouveau
    void ActualisationCompteurUTATTERISSAGE();
    void ActualisationCompteurUTSOL();
    void ActualisationCompteurUTDECOLAGE();
    void icitoutcepasse();
    float getLoca_x(){
        return loca_x;
    }
    float getLoca_y(){
        return loca_y;
    }
    int getDistance(string cle){
        return arrete[cle];
    }
};


class Carte{
private:
    std::vector<aeroport> ToutLesAeroport;
    std::vector<Avion> AvionEnVol;
public:
    void IciToutCePasse();
    void initialiseAeroport();
    void derouledujeu();
};



string conversionSommetVille(int nombre);
std::string choixavion();
std::vector<aeroport> remplirAeroAleatoirement(std::vector<aeroport> ListeAeroport);
void image(string image_path);
void drawSprite(sf::Sprite image);
sf::CircleShape afficherAvion(float x, float y);


#endif //SWIMMING_POOL_CLASSES_H
