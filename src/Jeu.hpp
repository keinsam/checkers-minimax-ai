#ifndef JEU_HPP
#define JEU_HPP

#include "Elements/Pion.hpp"
#include "Elements/Case.hpp"
#include "Joueur.hpp"
#include "../utils/Jeu_name.hpp"
#include "../utils/Info_Joueur.hpp"
#include <vector>

class Jeu {

protected :
    std::vector<Joueur*> joueurs;
    std::vector<std::vector<Case*>> plateau;
    int joueur_courant;
    int gagnant;

    Jeu();
    Jeu(Jeu &other) = delete;
    Jeu& operator=(Jeu &other) = delete;

public:
    virtual ~Jeu();
    virtual bool deplacementValide(int, int, int, int) const = 0;
    virtual void deplacer(int, int , int , int) = 0;
    virtual void maj_tour() = 0;
    void suivant();
    vector<vector<Case*>>& getPlateau();

    int getJoueurCourant() const;
    int getGagnant() const;
    void get_chemin_case(int i, int j, int x, int y, std::vector <Case*>& v) const;
    std::vector<Joueur*>& getJoueurs();
    Case* getCase(int i, int j);

    bool contientPion(int, int) const;
    bool contientPion_jc(int, int) const;

    bool termine() const;

};

#endif
