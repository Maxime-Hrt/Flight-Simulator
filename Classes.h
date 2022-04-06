#ifndef SWIMMING_POOL_CLASSES_H
#define SWIMMING_POOL_CLASSES_H
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <sstream>

#define WIDTH 1707
#define HEIGHT 1067


using namespace std;

class Avion
{
private:
    std::string type;
    std::string nomAvion;
    int consomation;
    int reservoir;
    int positionActuelle; ///la position de l'avion dit dans quel aeroport se trouve l'avion
    int cost[100][100], nbs, Sommet_, Adjacence, ponderation_;
    int DistanceAutonomie;
public:
    Avion();
    Avion(std::string type);
    ~Avion();
    void ParametrageGPSdijkstra();
    int getMin(int dist[], bool visited[]);
    void display(int dist[], int par[], int end);
    void dijkstra(int src , int end);
    void trajet_de_lavion();
    void afficheAttribut();
    std::string getType();
    void setNom(std::string nouveauNom);
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
    int nb_arrete;
    map<string, int> arrete;
    std::vector<Avion> AvionAuParking;
    int nb_piste_utiliseATM; /// est egal à atterissageEnCours.size()+decolageEnCours.size()
    int nb_places_sol_DisponibleATM; /// est egal nb_places_sol-AvionAuParking.size()
    std::vector<Avion> atterissageEnCours; /// les avions reste dans ce vecteur un certains temps avant de ce garer
    std::vector<Avion> decolageEnCours; /// les avions reste dans ce vecteur un certains temps avant de decoller completement de l'aeroport
    std::vector<Avion> File_Atteente_Atterissage;/// ici stocker les avion en attente pour atterir par ordre d'urgence(manque d'essence etc)
    std::vector<Avion> File_Atteente_Decolage;

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
};

string conversionSommetVille(int nombre);
std::string choixavion();
std::vector<aeroport> remplirAeroAleatoirement(std::vector<aeroport> ListeAeroport);
void image(string image_path);
void drawSprite(sf::Sprite image);
void coordoTrajet(aeroport aeroportD, aeroport aeroportF);
sf::CircleShape afficherAvion(float x, float y);

#endif //SWIMMING_POOL_CLASSES_H
