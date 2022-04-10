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
#include <list>
#include <SFML/Graphics.hpp>
#define WIDTH 1707
#define HEIGHT 1067
using namespace std;


class Avion
{
private:
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
    bool TrajetDeCetteAvionEnregistre;
    int depart;
    int arrive;
    int altitudeAvion;
    int CouleurAvion;
    sf::CircleShape design;
    int reserveActuelCarburant;
    bool fuiteReservoir;
    int augmentationConsomation;

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
    bool Verifietrajet_de_lavion(int depart,int arrive);
    void setdepart(int depart1)
    {
        depart = depart1;
    }
    int getdepart()
    {
        return depart;
    }
    void setarrive(int arrive1)
    {
        arrive = arrive1;
    }
    int getarrive()
    {
        return arrive;
    }
    bool getEtatFuite(){
        return fuiteReservoir;
    }


    bool getTrajetDeCetteAvionEnregistre()
    {
        return TrajetDeCetteAvionEnregistre;
    }

    void setTrajetDeCetteAvionEnregistre(bool actualisation)
    {
        TrajetDeCetteAvionEnregistre = actualisation;
    }

    vector<int> getTrajet(){
        return trajet;
    }
    void setTrajet(vector<int> _trajet){
        trajet=_trajet;
    }
    void resetTrajet(){
        trajet.clear();
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
    void resetnbUT()
    {
        nbUT.clear();
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

    void setPositionDesign(){
        design.setPosition(loca_x, loca_y);
    }
    sf::CircleShape getDesignAvion(){
        return design;
    }

    float getX(){
        return loca_x;
    }
    float getY(){
        return loca_y;
    }

    void setLocaX(float _loca_x){
        loca_x = _loca_x;
    }
    void setLocaY(float _loca_y){
        loca_y = _loca_y;
    }

    void popFrontAvion(){
        //trajet.erase(trajet.begin());
        avencement_x.erase(avencement_x.begin());
        avencement_y.erase(avencement_y.begin());
        //nbUT.erase(nbUT.begin());
    }
    void setaltitudeAvion(int altitude1)
    {
        altitudeAvion = altitude1;
    }
    int getaltitudeAvion()
    {
        return altitudeAvion;
    }
    void setCouleurAvion(int Couleur1)
    {
        CouleurAvion = Couleur1;
    }
    int getCouleurAvion()
    {
        return CouleurAvion;
    }

    void setDesign(){
        switch (CouleurAvion) {
            //Bas
            case 0:
                if (type == "Cours_Courrier")
                    design.setFillColor(sf::Color(200, 255, 200));
                if (type == "Moyen_Courrier")
                    design.setFillColor(sf::Color(200, 200, 255));
                if (type == "Long_Courrier")
                    design.setFillColor(sf::Color(255, 200, 200));
                break;

                //Haut
            case 2:
                if (type == "Cours_Courrier")
                    design.setFillColor(sf::Color(70, 255, 70));
                if (type == "Moyen_Courrier")
                    design.setFillColor(sf::Color(70, 70, 255));
                if (type == "Long_Courrier")
                    design.setFillColor(sf::Color(255, 70, 70));
                break;

                //tres Haut
            case 3:
                if (type == "Cours_Courrier")
                    design.setFillColor(sf::Color(0, 255, 0));
                if (type == "Moyen_Courrier")
                    design.setFillColor(sf::Color(0, 0, 255));
                if (type == "Long_Courrier")
                    design.setFillColor(sf::Color(255, 0, 0));
                break;

                // moyen
            case 1:
                if (type == "Cours_Courrier")
                    design.setFillColor(sf::Color(120, 255, 120));
                if (type == "Moyen_Courrier")
                    design.setFillColor(sf::Color(120, 120, 255));
                if (type == "Long_Courrier")
                    design.setFillColor(sf::Color(255, 120, 120));
        }

    }
    void crashDesign(){
        if (fuiteReservoir) {
            design.setFillColor(sf::Color::Black);
        }
    }
    void actualisationCarburantVol()
    {
        reserveActuelCarburant = reserveActuelCarburant-consomation;
    }
    void actualisationCarburantAttente()
    {
        reserveActuelCarburant = (reserveActuelCarburant)-((consomation/2)*(80/100));
    }
    void actualisationCarburantDecolage()
    {
        reserveActuelCarburant = reserveActuelCarburant;//-((consomation)*(30/100));
    }
    void actualisationCarburantAtterissage()
    {
        reserveActuelCarburant = (reserveActuelCarburant)-((consomation)*(120/100));
    }
    int getreserveActuelCarburant()
    {
        return reserveActuelCarburant;
    }
    void affichereserveActuelCarburant()
    {
        std::cout<<"Le carburant actuel dans "<<nomAvion<<" est de "<<reserveActuelCarburant<<std::endl;
    }
    void Fuitereservoir()
    {
        std::cout<<nomAvion<<" a une fuite reservoir votre cosomation augmente de 40%"<<std::endl;
        augmentationConsomation = consomation*(140/100)-(consomation);
        consomation = consomation*(400/100);
        fuiteReservoir = true;
    }
    void avionReparer()
    {
        fuiteReservoir = false;
        consomation = consomation-augmentationConsomation;
    }
    void rechargeCarburantSol(){
        reserveActuelCarburant = reservoir;
    }
};

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
    int CompteurPermissionDecolage;
    bool PermDecoler;

    int nb_arrete;
    map<string, int> arrete;
    std::vector<Avion> AvionAuParking;
    int nb_piste_utiliseATM; /// est egal Ã  atterissageEnCours.size()+decolageEnCours.size()
    int nb_places_sol_DisponibleATM; /// est egal nb_places_sol-AvionAuParking.size()
    std::vector<Avion> atterissageEnCours; /// les avions reste dans ce vecteur un certains temps avant de ce garer
    std::vector<Avion> decolageEnCours; /// les avions reste dans ce vecteur un certains temps avant de decoller completement de l'aeroport
    std::vector<Avion> File_Atteente_Atterissage;/// ici stocker les avion en attente pour atterir par ordre d'urgence(manque d'essence etc)
    std::vector<Avion> File_Atteente_Decolage;
    std::vector<Avion> Accede_au_piste;
    //nouveau derniere version
    std::vector<Avion> AvionAdecole;
    int altitude;
    int Couleur;

public:

    aeroport();
    aeroport(int _num_sommet, string _nom, int _loca_x, int _loca_y, int _nb_piste, int _nb_places_sol, int _attente_sol, int _temps_acces_piste, int _temps_atter, int _anti_collision, int _boucle_attente, int _nb_arrete, map<string, int> _arrete);
    ~aeroport();
    void remplirAvionParking(Avion Avion_Atterissant);
    int getternb_piste();
    int getternb_places_sol();
    string getterNom(){
        return nom;
    }
    int getNum_sommet();
    void atterir(Avion Avion_en_Aterissage);
    void afficheLesAvionSurPlace();
    void actualisationAtterissageToutLesAeroport();
    void decoler(Avion Avion_en_Decolage);
    void actualisationDecolageToutLesAeroport();
    void InitialiseAeroport();
    std::vector<Avion> partir(int depart,int arrive);
    void ActualisationCompteurUTATTERISSAGE();
    void ActualisationCompteurUTSOL();
    void ActualisationCompteurUTDECOLAGE();
    //nouveau derniere version
    std::vector<Avion> ActualisationAvionDecoler();
    void nettoyervecteurAvionADecoler();
    void initialiseDebutVol();
    //
    void icitoutcepasse();
    void setaltitude(int altitude1)
    {
        altitude = altitude1;
    }
    int getaltitude()
    {
        return altitude;
    }
    int gettempssol()
    {
        return attente_sol;
    }
    int getattenteaccesaupiste()
    {
        return temps_acces_piste;
    }
    int getTempsAtterisage()
    {
        return temps_atter;
    }
    int getDelaisAntiColision()
    {
        return anti_collision;
    }
    int getdelaisboucleattenteavantatterisage()
    {
        return boucle_attente;
    }
    void setCouleur(int Couleur1)
    {
        Couleur = Couleur1;
    }
    int getCouleur()
    {
        return Couleur;
    }
    float getLoca_x(){
        return loca_x;
    }
    float getLoca_y(){
        return loca_y;
    }
    int getDistance(string cle){
        return arrete[cle];
    }
    void setPermDecoler(int Decoler)
    {
        PermDecoler = Decoler;
    }
    bool getPermDecoler()
    {
        return PermDecoler;
    }
    void setCompteurPermDecoler(int CompteurDecolage)
    {
        CompteurPermissionDecolage = CompteurDecolage;
    }
    int getCompteurPermDecoler()
    {
        return CompteurPermissionDecolage;
    }
};

class Graph
{
    int V;
    list<int> *adj;
    std::map<int,int> sommetAltitude;

public:

    Graph(int V)   { this->V = V; adj = new list<int>[V]; }
    ~Graph()       { delete [] adj; }


    void addEdge(int v, int w);


    std::map<int,int> greedyColoring();
};

class Carte{
private:
    std::vector<aeroport> ToutLesAeroport;
    std::vector<Avion> AvionEnVol;
public:
    void IciToutCePasse();
    void initialiseAeroport();
    void derouledujeu();
    std::map<int,int> initialisePowel();
};


string conversionSommetVille(int nombre);
std::string choixavion();
std::vector<aeroport> remplirAeroAleatoirement(std::vector<aeroport> ListeAeroport);
void image(string image_path);
void drawSprite(sf::Sprite image);
sf::CircleShape afficherAvion(float x, float y);


#endif //SWIMMING_POOL_CLASSES_H