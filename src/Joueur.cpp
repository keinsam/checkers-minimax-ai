#include "Joueur.hpp"

using namespace std;

int Joueur::compteur_joueurs=0;

Joueur::Joueur() : id{compteur_joueurs++}, pions{} {}

Joueur::~Joueur() {
	pions.clear();
}

int Joueur::getId() const {
	return id;
}

vector <Pion*>& Joueur::getPions() {
	return pions;
}

void Joueur::ajouterPion(Pion *p) {
	pions.push_back(p);
}

void Joueur::enleverPion(const Pion* p) {
	for (int i=0; i<pions.size(); i++) {
		if(pions[i] == p)
			pions.erase(pions.begin()+i);
	}
}

bool Joueur::contientPion(const Pion* p) const {
	for (int i=0; i<pions.size(); i++) {
		if (pions[i] == p) {
			return true;
		}
	}
	return false;
}
