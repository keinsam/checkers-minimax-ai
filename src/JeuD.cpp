#include "JeuD.hpp"
#include <iostream>

using namespace std;

JeuD::JeuD() : Jeu(), captures{} {
    // On crée le plateau 10 Cases x 10 Cases
    for (int i = 0; i < 10; i++) {
        vector<Case*> ligne;
        for (int j = 0; j < 10; j++) {
            if ((i + j) % 2 == 0) {
                ligne.push_back(new Case(Fonce));
            } else {
                ligne.push_back(new Case(Clair));
            }
        }
        plateau.push_back(ligne);
    }
    
    // On donne 20 pions à chaque joueur
    Couleur couleur = Blanc;
	for (int i=0; i<2; i++) {
		joueurs.push_back(new Joueur());
		for (int j=0; j<20 ; j++) {
			joueurs[i]->ajouterPion(new PionD(couleur));
		}
		couleur = Noir;
	}

    // On associe les pions et les cases
    for(int i = 0; i < 4; i++) { // Pour le joueur blanc
        int compteur_1 = 0;
        for (Case* c : plateau[i]) {
            if(c->getCouleur() == Fonce) {
                c->setPion(joueurs[0]->getPions()[compteur_1]);
                compteur_1++;
            }
        }
    }
    for(int i = 6; i < 10; i++) { // Pour le joueur noir
        int compteur_2 = 0;
        for (Case* c : plateau[i]) {
            if(c->getCouleur() == Fonce) {
                c->setPion(joueurs[1]->getPions()[compteur_2]);
                compteur_2++;
            }
        }
    }


}

void JeuD::get_chemin_case(int ancienneLigne, int ancienneColonne, int nouvelleLigne, int nouvelleColonne, vector<Case*>& v) const {

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


// Pour cette méthode, je suppose que les pions blancs démarrent sur la ligne 0 et les pions noirs sur la ligne 9
bool JeuD::deplacementValide(int ancienneLigne, int ancienneColonne, int nouvelleLigne, int nouvelleColonne) const {

    if( ancienneLigne<0 || ancienneLigne>9 || ancienneColonne<0 || ancienneColonne>9 ||
        nouvelleLigne<0 || nouvelleLigne>9 || nouvelleColonne<0 || nouvelleColonne>9 ||
        plateau[ancienneLigne][ancienneColonne]->estVide() ||
        !plateau[nouvelleLigne][nouvelleColonne]->estVide()) {
        return false;
    }
    
    Joueur* joueur = joueurs[joueur_courant];
    PionD* pion = (PionD *) plateau[ancienneLigne][ancienneColonne]->getPion();
    Couleur couleur_joueur = ((PionD*) (joueur->getPions()[0]))->getCouleur();

    if(pion->getCouleur() != couleur_joueur) {
        return false;
    }

	// Pour une dame quelconque : vérifie si le déplacement est diagonal
	if(pion->getIsDame() && abs(nouvelleLigne-ancienneLigne)==abs(nouvelleColonne-ancienneColonne)) {
		return true;
	}

	// Pour un pion blanc : vérifie si le déplacement est diagonal en avant d'une case
    if (!pion->getIsDame() && couleur_joueur==Blanc && (nouvelleLigne - ancienneLigne)==1 && abs(nouvelleColonne - ancienneColonne)==1) {
        return true;
    }

	// Pour un pion noir : vérifie si le déplacement est diagonal en avant d'une case
	if (!pion->getIsDame() && couleur_joueur==Noir && (nouvelleLigne - ancienneLigne)==-1 && abs(nouvelleColonne - ancienneColonne)==1) {
        return true;
    }

    return false;
}


void JeuD::deplacer(int ancienneLigne, int ancienneColonne, int nouvelleLigne, int nouvelleColonne) {
	plateau[nouvelleLigne][nouvelleColonne]->setPion(plateau[ancienneLigne][ancienneColonne]->getPion());
	plateau[ancienneLigne][ancienneColonne]->setPion(nullptr);
}


bool JeuD::captureValide(int ancienneLigne, int ancienneColonne, int nouvelleLigne, int nouvelleColonne) const {

    // Vérifie que les indices des lignes soient corrects et que le deplacement soit diagonal
    if( ancienneLigne<0 || ancienneLigne>9 || ancienneColonne<0 || ancienneColonne>9 ||
        nouvelleLigne<0 || nouvelleLigne>9 || nouvelleColonne<0 || nouvelleColonne>9 ||
        abs(nouvelleLigne - ancienneLigne) != abs(nouvelleColonne - ancienneColonne) ) {
            return false;
        }

    if(plateau[ancienneLigne][ancienneColonne]->estVide()) {return false;}

    Joueur* joueur = joueurs[joueur_courant];
    PionD* pion = (PionD *) plateau[ancienneLigne][ancienneColonne]->getPion();
    Couleur couleur_joueur = ((PionD*) (joueur->getPions()[0]))->getCouleur();

    if(!pion->getIsDame() && (abs(nouvelleLigne - ancienneLigne) != 2 || abs(nouvelleColonne - ancienneColonne) != 2)) {
        return false;
    }

    vector <Case*> chemin_case;
    get_chemin_case(ancienneLigne, ancienneColonne, nouvelleLigne, nouvelleColonne, chemin_case);
    PionD* pion_adverse;
    int nombre_pions_intermediaires = 0;
    for(Case* c : chemin_case) {
        if(!c->estVide()) {
            nombre_pions_intermediaires++;
            pion_adverse = (PionD*) c->getPion();
        }
    }

    return  plateau[nouvelleLigne][nouvelleColonne]->estVide() &&
            nombre_pions_intermediaires == 1 &&
            couleur_joueur != pion_adverse->getCouleur();
}

void JeuD::capturer(int ancienneLigne, int ancienneColonne, int nouvelleLigne, int nouvelleColonne) {
    vector <Case*> chemin_case;
    get_chemin_case(ancienneLigne, ancienneColonne, nouvelleLigne, nouvelleColonne, chemin_case);
    for(Case* c : chemin_case) {
        if(!c->estVide()) {
            // supprimer le pion
            c->setPion(nullptr);
        }
    }
    deplacer(ancienneLigne, ancienneColonne, nouvelleLigne, nouvelleColonne);
}

void JeuD::capturer(Capture* capture) {
    for(pair<PionD*, Case*>& pion_int : capture->pions_captures) {
        pion_int.second->setPion(nullptr);
    }

    for(Case* c : capture->chemin) {
        if(!c->estVide()) {
            c->setPion(nullptr);
        }
    }

    Case* arrivee = capture->chemin.back();
    arrivee->setPion(capture->pion);
}


void JeuD::annulerCapture(const vector<Capture*>& captures_, int ligne, int colonne) {

    PionD* pion = (PionD *) plateau[ligne][colonne]->getPion();
    Capture* capture = captures_.back();

    // Remettre le pion courant à sa place
    Case* case_depart = capture->chemin.at(capture->chemin.size()-2);
    plateau[ligne][colonne]->setPion(nullptr);
    case_depart->setPion(pion);
    // Remettre les pions capturés à leur place
    capture->pions_captures.back().second->setPion( capture->pions_captures.back().first );

}


void JeuD::capturePossiblePion(vector<Capture*>& captures_pion, PionD* pion, int ligne, int colonne) {

    // PionD* pion_de_la_case = (PionD *) plateau[ligne][colonne]->getPion();
    // TO DO : raise error si pion != pion_de_la_case ici

    vector<Capture*> captures_pion_copy = captures_pion;

    for(int i=-2; i<=2; i+=4) {
        for(int j=-2; j<=2; j+=4) {
            if(this->captureValide(ligne, colonne, ligne+i, colonne+j)) {
                if(captures_pion.size() == 0) {
                    Capture* nouvelle_capture = new Capture{plateau, ligne, colonne, ligne+i, colonne+j};
                    captures_pion.push_back(nouvelle_capture);
                    this->capturer(ligne, colonne, ligne+i, colonne+j);
                    // Appel récursif
                    capturePossiblePion(captures_pion, pion, ligne+i, colonne+j);
                    // Annuler la capture pour explorer d'autres possibilités
                    this->annulerCapture(captures_pion, ligne+i, colonne+j);
                } else {
                    Capture* nouvelle_capture = new Capture{*captures_pion.back(), ligne, colonne, ligne+i, colonne+j};
                    captures_pion_copy.push_back(nouvelle_capture);
                    this->capturer(ligne, colonne, ligne+i, colonne+j);
                    // Appel récursif
                    capturePossiblePion(captures_pion_copy, pion, ligne+i, colonne+j);
                    // Annuler la capture pour explorer d'autres possibilités
                    this->annulerCapture(captures_pion_copy, ligne+i, colonne+j);
                }
            }
        }
    }

    for(Capture* c1 : captures_pion_copy) {
        int estDedans = 0;
        for(Capture* c2 : captures_pion) {
            if(c1 == c2) {
                estDedans = 1;
            }
        }
        if(estDedans == 0) {
            captures_pion.push_back(c1);
        }
    }
}


vector<Capture*> JeuD::capturePossible() {

    Joueur* joueur = joueurs[joueur_courant];
    vector<Capture*> captures_possibles{};
    vector<Pion*> pions = joueur->getPions();

    // Pour chaque case on veut savoir si elle a un pion appartenant au joueur courant
    // Si c'est le cas, on veut vérifier si ce pion peut faire des captures
    int ligne_index = 0;
    for(vector<Case*> ligne : plateau) {
        int colonne_index = 0;
        for(Case* c : ligne) {
            if(!c->estVide()) {
                PionD* pion = (PionD*) c->getPion();
                vector<Capture*> captures_pion{};
                if(joueur->contientPion(pion)) {
                    int ligne_pion = ligne_index;
                    int colonne_pion = colonne_index;
                    PionD* pion = (PionD*) c->getPion();
                    // Trouver les captures possibles en sachant le pion, sa ligne et sa colonne
                    capturePossiblePion(captures_pion, pion, ligne_pion, colonne_pion);
                    captures_possibles.insert(captures_possibles.end(), captures_pion.begin(), captures_pion.end());
                }
            }
            colonne_index++;
        }
        ligne_index++;
    }

    return captures_possibles;
}

void JeuD::captureMaximum() {
    vector<Capture*> captures_possibles = capturePossible();

    int max = 0;
    int nombre_captures;
    for(Capture* capture : captures_possibles) {
        nombre_captures = capture->pions_captures.size();
        if(capture->pions_captures.size() > max) {
            max = nombre_captures;
        }
    }

    for(Capture* capture : captures_possibles) {
        if(capture->pions_captures.size() == max)
            this->captures.push_back(capture);
        else
            delete capture; // Ici on delete les captures qui ne sont pas maximales
    }

}


void JeuD::maj_tour() {

    int ligne;
    Couleur couleur;
    if (joueur_courant==0) {
        ligne=9; couleur=Blanc;
    } else {
        ligne=0; couleur=Noir;
    }

    // On vérifie si on a une nouvelle dame
    PionD* pion;
    for(Case* c : plateau[ligne]) {
        if(!c->estVide()) {
            pion = (PionD*) c->getPion();
            if(pion->getCouleur() == couleur)
                pion->setIsDame();
        }
    }

    // On vérifie si un joueur n'a plus de pions
    Joueur* joueur_adverse = joueurs[(joueur_courant+1) % 2];
    if(joueur_adverse->getPions().size() == 0) {
        gagnant = joueur_courant;
    }

    // On supprime les captures
    for(Capture* ancienne_capture : captures) {
        delete ancienne_capture;
    }
    captures.clear();

}


