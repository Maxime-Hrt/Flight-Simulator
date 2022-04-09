#include "Classes.h"



void Avion::afficheAttribut()
{
    std::cout<<"Le NOM de cet avion est : "<<nomAvion<<std::endl;
    std::cout<<"Le type de cet avion est : "<<type<<std::endl;
    std::cout<<"La consomation au 100 Km de cet avion est : "<<consomation<<std::endl;
    std::cout<<"Le reservoir de cet avion est de : "<<reservoir<<std::endl;
    std::cout<<"La distance que cet avion peut parcourir en autonomie est : "<<DistanceAutonomie<<std::endl;
}

std::string Avion::getNom()
{
    return nomAvion;
}


Avion::Avion(std::string _type):type(_type)
{
    EtatAvion["Sol"] = 0;
    EtatAvion["Vol"] = 0;
    EtatAvion["Atterit"] = 0;
    EtatAvion["Decole"] = 0;
    EtatAvion["Attend"] = 0;
    EtatAvion["AccedePiste"] = 0;
    TrajetDeCetteAvionEnregistre = false;


    /// Initialisation graphique
    srand(time(NULL));
    sf::CircleShape shape(10.f);
    design = shape;
    design.setFillColor(sf::Color(rand()%256, rand()%256, rand()%256));

    if(_type == "Cours_Courrier")
    {
        ifstream fichier("Avion.txt");
        if(fichier)
        {
            std::string inutileString;
            fichier >> inutileString;
            fichier >> consomation;
            fichier >> reservoir;
            fichier >> DistanceAutonomie;
        }
        else {
            cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
        }

    }
    else if(_type == "Moyen_Courrier")
    {
        ifstream fichier("Avion.txt");
        if(fichier)
        {
            std::string inutileString;
            int inutile;
            fichier >> inutileString;
            for(int i = 0;i<3;i++)
            {
                fichier >> inutile;
            }
            fichier >> inutileString;
            fichier >> consomation;
            fichier >> reservoir;
            fichier >> DistanceAutonomie;
        }
        else {
            cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
        }

    }
    else if(_type == "Long_Courrier")
    {
        ifstream fichier("Avion.txt");
        if(fichier)
        {
            std::string inutileString;
            int inutile;
            fichier >> inutileString;
            for(int i = 0;i<3;i++)
            {
                fichier >> inutile;
            }
            fichier >> inutileString;
            for(int i = 0;i<3;i++)
            {
                fichier >> inutile;
            }
            fichier >> inutileString;
            fichier >> consomation;
            fichier >> reservoir;
            fichier >> DistanceAutonomie;
        }
        else {
            cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
        }

    }
}

void Avion::setNom(std::string nouveauNom)
{
    nomAvion = nouveauNom;
}


int Avion::getMin(int dist[], bool visited[]) {
    int key = 0;
    int min = INT_MAX;
    for(int i=0;i < nbs; i++){
        if(!visited[i] && dist[i]<min) {
            min = dist[i];
            key = i;
        }
    }
    return key ;
}

vector<int> Avion::display(int dist[], int par[], int end) {
    vector<int> trajet;
    int temp = par[end];
    trajet.push_back(end);
    cout<< conversionSommetVille(end) + " <- ";
    while(temp!=-1) {
        trajet.push_back(temp);
        cout<< conversionSommetVille(temp) + " <- ";
        temp = par[temp];
    }
    cout<<endl;
    cout<<"Distance = " << dist[end];
    cout<<endl;
    return trajet;
}

void Avion::ParametrageGPSdijkstra()
{
    std::cout<<"le nom de fichier est:  "<<type<<std::endl;
    std::ifstream fichier(type+".txt");
    /// lecture du fichier ( structure du fichier est celui donné dans le tp )///
    if(fichier) {
        fichier>>nbs;
        for(int i=0; i<nbs; i++){
            for(int j=0; j<nbs; j++) {
                if(i==j){
                    cost[i][j]=0;
                }
                else{
                    cost[i][j]=999;
                }
            }
        }
        while(fichier>>Sommet_) {
            fichier>>Adjacence;
            fichier>>ponderation_;
            cost[Sommet_][Adjacence]=ponderation_;
        }
    }
    else {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
    }

}

std::string Avion::getType()
{
    return type;
}

vector<int> Avion::dijkstra(int src , int end) {
    int par[100], dist[100];
    bool visited[100] ={0};
    fill(dist, dist+nbs, INT_MAX );
    dist[src] =0;
    par[src] =-1;
    for(int g = 0; g<nbs-1; g++){
        int u = getMin(dist, visited );
        visited[u] = true ;
        for(int v =0 ; v< nbs ;v++){
            if(!visited[v] && (dist[u]+cost[u][v]) <  dist[v] && cost[u][v]!=999)
            {
                par[v] = u;
                dist[v] = dist[u] + cost[u][v];
            }
        }
    }
    return display(dist, par, end);
}

/// modification methode
vector<int> Avion::trajet_de_lavion(int depart,int arrive)
{


    if(type == "Cours_Courrier")
    {
        int inutile;
        int verifarriveexiste;
        int verifdepartexiste;
        bool verifarriveexiste1 = false;
        bool verifdepartexiste1 = false;
        bool Trajet_existe = false;
        std::ifstream fichier("Cours_Courrier.txt");
        /// lecture du fichier ( structure du fichier est celui donné dans le tp )///
        if(fichier) {
            fichier>>inutile;
            while(fichier>>verifdepartexiste) {
                fichier>>verifarriveexiste;
                fichier>>inutile;
                if(verifdepartexiste == depart)
                {
                    verifdepartexiste1 = true;
                }
                if(verifarriveexiste == arrive)
                {
                    verifarriveexiste1 = true;
                }
            }
        }
        else {
            std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
        }
        if((verifdepartexiste1 == true)&&(verifarriveexiste1 == true))
        {
            Trajet_existe = true;
        }
        if( Trajet_existe == true)
        {
            return dijkstra(depart, arrive);
        }
        else
        {
            std::cout<<"Cet avion ne peut pas effectuer ce trajet desole"<<std::endl;
        }

        /// afficher les trajet possible sur allegro et blinder les entré en dessous pour le choix des sommmet depart et arrivé

    }
    else if(type == "Moyen_Courrier")
    {

        int inutile;
        int verifarriveexiste;
        int verifdepartexiste;
        bool verifarriveexiste1 = false;
        bool verifdepartexiste1 = false;
        bool Trajet_existe = false;
        std::ifstream fichier("Moyen_Courrier.txt");
        /// lecture du fichier ( structure du fichier est celui donné dans le tp )///
        if(fichier) {
            fichier>>inutile;
            while(fichier>>verifdepartexiste) {
                fichier>>verifarriveexiste;
                fichier>>inutile;
                if(verifdepartexiste == depart)
                {
                    verifdepartexiste1 = true;
                }
                if(verifarriveexiste == arrive)
                {
                    verifarriveexiste1 = true;
                }
            }
        }
        else {
            std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
        }
        if((verifdepartexiste1 == true)&&(verifarriveexiste1 == true))
        {
            Trajet_existe = true;
        }
        if( Trajet_existe == true)
        {
            return dijkstra(depart, arrive);
        }
        else
        {
            std::cout<<"Cet avion ne peut pas effectuer ce trajet desole"<<std::endl;
        }
        /// afficher les trajet possible sur allegro et blinder les entré en dessous pour le choix des sommmet depart et arrivé
    }
    else if(type == "Long_Courrier")
    {

        int inutile;
        int verifarriveexiste;
        int verifdepartexiste;
        bool verifarriveexiste1 = false;
        bool verifdepartexiste1 = false;
        bool Trajet_existe = false;
        std::ifstream fichier("Long_Courrier.txt");
        /// lecture du fichier ( structure du fichier est celui donné dans le tp )///
        if(fichier) {
            fichier>>inutile;
            while(fichier>>verifdepartexiste) {
                fichier>>verifarriveexiste;
                fichier>>inutile;
                if(verifdepartexiste == depart)
                {
                    verifdepartexiste1 = true;
                }
                if(verifarriveexiste == arrive)
                {
                    verifarriveexiste1 = true;
                }
            }
        }
        else {
            std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
        }
        if((verifdepartexiste1 == true)&&(verifarriveexiste1 == true))
        {
            Trajet_existe = true;
        }
        if( Trajet_existe == true)
        {
            return dijkstra(depart, arrive);
        }
        else
        {
            std::cout<<"Cet avion ne peut pas effectuer ce trajet desole"<<std::endl;
        }
        /// afficher les trajet possible sur allegro et blinder les entré en dessous pour le choix des sommmet depart et arrivé
    }

}

bool Avion::Verifietrajet_de_lavion(int depart,int arrive)
{

    if(type == "Cours_Courrier")
    {
        int inutile;
        int verifarriveexiste;
        int verifdepartexiste;
        bool verifarriveexiste1 = false;
        bool verifdepartexiste1 = false;
        bool Trajet_existe = false;
        std::ifstream fichier("Cours_Courrier.txt");
        /// lecture du fichier ( structure du fichier est celui donné dans le tp )///
        if(fichier) {
            fichier>>inutile;
            while(fichier>>verifdepartexiste) {
                fichier>>verifarriveexiste;
                fichier>>inutile;
                if(verifdepartexiste == depart)
                {
                    verifdepartexiste1 = true;
                }
                if(verifarriveexiste == arrive)
                {
                    verifarriveexiste1 = true;
                }
            }
        }
        else {
            std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
        }
        if((verifdepartexiste1 == true)&&(verifarriveexiste1 == true))
        {
            Trajet_existe = true;
        }
        if( Trajet_existe == true)
        {
            std::cout<<"Cet avion peut effectuer ce trajet"<<std::endl;
            return true;
        }
        else
        {
            std::cout<<"Cet avion ne peut pas effectuer ce trajet desole"<<std::endl;
            return false;
        }

        /// afficher les trajet possible sur allegro et blinder les entré en dessous pour le choix des sommmet depart et arrivé

    }
    else if(type == "Moyen_Courrier")
    {

        int inutile;
        int verifarriveexiste;
        int verifdepartexiste;
        bool verifarriveexiste1 = false;
        bool verifdepartexiste1 = false;
        bool Trajet_existe = false;
        std::ifstream fichier("Moyen_Courrier.txt");
        /// lecture du fichier ( structure du fichier est celui donné dans le tp )///
        if(fichier) {
            fichier>>inutile;
            while(fichier>>verifdepartexiste) {
                fichier>>verifarriveexiste;
                fichier>>inutile;
                if(verifdepartexiste == depart)
                {
                    verifdepartexiste1 = true;
                }
                if(verifarriveexiste == arrive)
                {
                    verifarriveexiste1 = true;
                }
            }
        }
        else {
            std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
        }
        if((verifdepartexiste1 == true)&&(verifarriveexiste1 == true))
        {
            Trajet_existe = true;
        }
        if( Trajet_existe == true)
        {
            std::cout<<"Cet avion peut effectuer ce trajet"<<std::endl;
            return true;
        }
        else
        {
            std::cout<<"Cet avion ne peut pas effectuer ce trajet desole"<<std::endl;
            return false;
        }
        /// afficher les trajet possible sur allegro et blinder les entré en dessous pour le choix des sommmet depart et arrivé
    }
    else if(type == "Long_Courrier")
    {

        int inutile;
        int verifarriveexiste;
        int verifdepartexiste;
        bool verifarriveexiste1 = false;
        bool verifdepartexiste1 = false;
        bool Trajet_existe = false;
        std::ifstream fichier("Long_Courrier.txt");
        /// lecture du fichier ( structure du fichier est celui donné dans le tp )///
        if(fichier) {
            fichier>>inutile;
            while(fichier>>verifdepartexiste) {
                fichier>>verifarriveexiste;
                fichier>>inutile;
                if(verifdepartexiste == depart)
                {
                    verifdepartexiste1 = true;
                }
                if(verifarriveexiste == arrive)
                {
                    verifarriveexiste1 = true;
                }
            }
        }
        else {
            std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
        }
        if((verifdepartexiste1 == true)&&(verifarriveexiste1 == true))
        {
            std::cout<<"Cet avion peut effectuer ce trajet"<<std::endl;
            Trajet_existe = true;
        }
        if( Trajet_existe == true)
        {
            return true;
        }
        else
        {
            std::cout<<"Cet avion ne peut pas effectuer ce trajet desole"<<std::endl;
            return false;
        }
        /// afficher les trajet possible sur allegro et blinder les entré en dessous pour le choix des sommmet depart et arrivé
    }

}

void Avion::setEtatAvion(map<string,int> MAJEtatAvion)
{
    EtatAvion = MAJEtatAvion;
}

map<string,int> Avion::getEtatAvion()
{
    return EtatAvion;
}

















Avion::~Avion() {}
