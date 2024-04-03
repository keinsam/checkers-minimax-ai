#include "Jeu.hpp"
#include "JeuI.hpp"
#include "JeuD.hpp"
#include "JeuS.hpp"
#include "../utils/utils.hpp"

using namespace std;

Jeu::Jeu() : joueurs{}, plateau{}, joueur_courant{0} ,gagnant{-1} {}

Jeu::~Jeu() {
	for(Joueur* joueur : joueurs) {
		for(Pion* pion : joueur->getPions()) {
			delete pion;
		}
		delete joueur;
	}

	for(vector<Case*> ligne : plateau) {
		for(Case* c : ligne) {
			delete c;
		}
	}
}

vector<vector<Case *>> &Jeu::getPlateau() {
	return plateau;
}

vector<Joueur*>& Jeu::getJoueurs() {
	return joueurs;
}

int Jeu::getJoueurCourant() const {
	return joueur_courant;
}

int Jeu::getGagnant() const {
	return gagnant;
}

Case* Jeu::getCase(int i, int j) {
    return plateau[i][j];
}

void Jeu::get_chemin_case(int i, int j, int x, int y, vector <Case*>& v) const {
	vector<pair<int,int>> voisins=get_voisins_all(i,j,5);
	double min= dist(i,j,x,y);
	int a,b=0;
	for (int k = 0; k <voisins.size() ; k++) {
		double dist_c=dist(voisins[k].first,voisins[k].second,x,y);
		if(dist_c<min){
			min=dist_c;
			a=voisins[k].first;
			b=voisins[k].second;
		}

	}
	if(min==0)
		return;
	v.push_back(plateau[a][b]);
	get_chemin_case(a,b,x,y,v);
}

bool Jeu::contientPion(int ligne, int colonne) const {
	return !plateau[ligne][colonne]->estVide();
}

bool Jeu::contientPion_jc(int ligne, int colonne) const {
	return (contientPion(ligne, colonne) && joueurs[joueur_courant]->contientPion(plateau[ligne][colonne]->getPion()));
}

void Jeu::suivant() {
	joueur_courant = (joueur_courant+1) % joueurs.size();
}

bool Jeu::termine() const {
	return (gagnant!=-1);
}