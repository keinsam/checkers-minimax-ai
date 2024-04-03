#include "Capture.hpp"
#include <iostream>

using namespace std;

void Capture::get_chemin_case(const vector<vector<Case*>>& plateau, int ancienneLigne, int ancienneColonne, int nouvelleLigne, int nouvelleColonne, vector<Case*>& v) const {

    if (abs(nouvelleLigne - ancienneLigne) != abs(nouvelleColonne - ancienneColonne)) {
        return;
    }

    int directionLigne = (nouvelleLigne > ancienneLigne) ? 1 : -1;
    int directionColonne = (nouvelleColonne > ancienneColonne) ? 1 : -1;

    for (int i = ancienneLigne + directionLigne, j = ancienneColonne + directionColonne;
         i != nouvelleLigne && j != nouvelleColonne;
         i += directionLigne, j += directionColonne) {
        
        v.push_back(plateau[i][j]);
    }
}


Capture::Capture(vector<vector<Case*>>& plateau_, int ancienneLigne, int ancienneColonne, int nouvelleLigne, int nouvelleColonne) 
    : plateau{plateau_} {

    this->pion = (PionD *) plateau[ancienneLigne][ancienneColonne]->getPion();;
    this->chemin.push_back(plateau[ancienneLigne][ancienneColonne]);

    vector <Case*> chemin_case{};
    get_chemin_case(plateau, ancienneLigne, ancienneColonne, nouvelleLigne, nouvelleColonne, chemin_case);
    for(Case* c : chemin_case) {
        if(!c->estVide()) {
            this->pions_captures.push_back(make_pair((PionD*) c->getPion(), c));
        } else {
            this->chemin.push_back(c);
        }
    }
    
    this->chemin.push_back(plateau[nouvelleLigne][nouvelleColonne]);

}

Capture::Capture(Capture& capture, int ancienneLigne, int ancienneColonne, int nouvelleLigne, int nouvelleColonne) 
    : plateau{capture.plateau}, chemin{capture.chemin}, pions_captures{capture.pions_captures}, pion{capture.pion} {

    vector <Case*> chemin_case{};
    get_chemin_case(plateau, ancienneLigne, ancienneColonne, nouvelleLigne, nouvelleColonne, chemin_case);
    for(Case* c : chemin_case) {
        if(!c->estVide()) {
            this->pions_captures.push_back(make_pair((PionD*) c->getPion(), c));
        } else {
            this->chemin.push_back(c);
        }
    }

    this->chemin.push_back(plateau[nouvelleLigne][nouvelleColonne]);
}


Capture::~Capture() {
    pion = nullptr;
    chemin.clear();
    pions_captures.clear();
}


ostream& operator<<(ostream& os, const Capture& capture) {
        os << "   Chemin de capture : ";
        for (Case* c: capture.chemin) {
            os << "(" << c->getLigne(capture.plateau) << ", " << c->getColonne(capture.plateau) << ") ";
        }
        os << endl;

        os << "   Pions capturés : ";
        for (pair<PionD*, Case*> pion : capture.pions_captures) {
            os << "(" << pion.second->getLigne(capture.plateau) << ", " << pion.second->getColonne(capture.plateau) << ") ";
        }

        return os;
}