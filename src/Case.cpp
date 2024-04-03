#include "Case.hpp"
#include <vector>

using namespace std;

Case::Case(Couleur couleur_)
	: pion{nullptr}, couleur{couleur_}, marque{false} {}

Pion* Case::getPion() const {
	return this->pion;
}

Couleur Case::getCouleur() const {
	return this->couleur;
}

int Case::getLigne(const vector<vector<Case*>>& plateau) const {
	for(int i = 0; i < plateau.size(); i++) {
		for(int j = 0; j < plateau[i].size(); j++) {
			if(plateau[i][j] == this)
				return i;
		}
	}
	return -1; // créer une exception ici
}

int Case::getColonne(const vector<vector<Case*>>& plateau) const {
	for(int i = 0; i < plateau.size(); i++) {
		for(int j = 0; j < plateau[i].size(); j++) {
			if(plateau[i][j] == this)
				return j;
		}
	}
	return -1; // créer une exception ici
}

void Case::setPion(Pion* pion_) {
	this->pion = pion_;
}

bool Case::estVide() const {
	return this->pion == nullptr;
};

bool Case::estMarque() const {
	return marque;
}

void Case::clearMarque() {
	marque= false;
}

void Case::setMarque() {
	marque = true;
}