#include "../src/Modele/JeuD.hpp"
#include <iostream>
#define RESET "\033[0m"
#define BEIGE "\033[38;2;255;255;204m"
#define BROWN "\033[38;2;139;69;19m"


using namespace std;

class TestD {

public :

	void ask_user_deplacer(vector<int>& v) {

		v.clear();
		char action;
		int ancienneLigne, ancienneColonne, nouvelleLigne, nouvelleColonne = 0;

		cout << "Choisissez l'action D[déplacer] ou Q[quittez] : ";
		cin >> action;
		if(action == 'Q')
			exit(0);
			if(action != 'D' && action != 'Q')
				ask_user_deplacer(v);

		cout << "Entrez les coordonnées de votre case de départ puis de votre case d'arrivée :\n";
		cin >> ancienneLigne;
		cin >> ancienneColonne;
		cin >> nouvelleLigne;
		cin >> nouvelleColonne;
		if( ancienneLigne>=0 && ancienneLigne<=9 && ancienneColonne>=0 && ancienneColonne<=9 &&
			nouvelleLigne>=0 && nouvelleLigne<=9 && nouvelleColonne>=0 && nouvelleColonne<=9 ) {
			v.push_back(action);
			v.push_back(ancienneLigne);
			v.push_back(ancienneColonne);
			v.push_back(nouvelleLigne);
			v.push_back(nouvelleColonne);
			return;
		}
		ask_user_deplacer(v);

	}

	void ask_user_capturer(int nombre_captures, int &numero_capture) {

		char action;

		cout << "Choisissez l'action C[captuer] ou Q[quittez] : ";
		cin >> action;
		if(action == 'Q')
			exit(0);
			if(action != 'C' && action != 'Q')
				ask_user_capturer(nombre_captures, numero_capture);

		cout << "Entrez le numéro de la capture que vous voulez effectuer :\n";
		cin >> numero_capture;

		if(numero_capture >= 0 && numero_capture < nombre_captures) {
			return;
		}

		ask_user_capturer(nombre_captures, numero_capture);

	}


	void affiche (Jeu *jeu) {
		cout << " " << endl;
		for (int i = 9; i < jeu->getPlateau().size(); i--) {
			for (int j = 0; j < jeu->getPlateau().front().size(); j++) {
				if( !jeu->getPlateau()[i][j]->estVide() ) {
					if(((PionD*)(jeu->getPlateau()[i][j]->getPion()))->getCouleur()==Blanc)
						cout << BEIGE << ((PionD*) (jeu->getPlateau()[i][j]->getPion()))->getIsDame() << RESET << "  ";
					else
						cout << BROWN << ((PionD*) (jeu->getPlateau()[i][j]->getPion()))->getIsDame()  << RESET << "  " ;
				} else {
					cout << "-" << "  " ;
				}
			}
			cout << endl;
		}
	}


	void runJeu() {

		JeuD* jeu = new JeuD();

		while(!jeu->termine()) {

			affiche(jeu);
		
			jeu->captures.clear();
			jeu->captureMaximum();

			vector<int> v;
			int nombre_captures = jeu->captures.size();
			int numero_capture = 999;

			if(jeu->getJoueurCourant()==0)
				cout << "Joueur: " <<  BEIGE << jeu->getJoueurCourant() << RESET << endl;
			else
				cout << "Joueur: " <<  BROWN << jeu->getJoueurCourant() << RESET << endl;
			
			if(nombre_captures == 0) {
				ask_user_deplacer(v);
				while( !jeu->deplacementValide(v[1],v[2],v[3],v[4]) ) {
					cout << "Veuillez entrer un déplacement valide" << endl;
					if(jeu->getJoueurCourant()==0)
						cout << "Joueur: " <<  BEIGE << jeu->getJoueurCourant() << RESET << endl;
					else
						cout << "Joueur: " <<  BROWN << jeu->getJoueurCourant() << RESET << endl;
					ask_user_deplacer(v);
				}
				jeu->deplacer(v[1], v[2], v[3], v[4]);
				jeu->maj_tour();
				jeu->suivant();
			} else {
				cout << "\nVoici vos captures possibles :\n";
				for(int i = 0; i < jeu->captures.size(); i++) {
					cout << "Capture numéro " << i << endl;
					cout << *(jeu->captures[i]) << endl;
				}

				ask_user_capturer(nombre_captures, numero_capture);
				while(numero_capture < 0 || numero_capture >= nombre_captures) {
					cout << "Veuillez entrer une capture valide" << endl;
					if(jeu->getJoueurCourant()==0)
						cout << "Joueur: " <<  BEIGE << jeu->getJoueurCourant() << RESET << endl;
					else
						cout << "Joueur: " <<  BROWN << jeu->getJoueurCourant() << RESET << endl;
					ask_user_capturer(nombre_captures, numero_capture);
				}
				jeu->capturer(jeu->captures[numero_capture]);
				jeu->maj_tour();
				jeu->suivant();
			}

		}
		if(jeu->getGagnant()==0)
			cout << "Le joueur blanc a gagné !" << endl;
		else
			cout << "Le joueur noir a gagné !" << endl;
		
		delete jeu;
	}

};


int main() {

	TestD* test_dames = new TestD();

	test_dames->runJeu();

	delete test_dames;

}