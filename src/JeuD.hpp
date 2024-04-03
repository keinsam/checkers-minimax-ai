#ifndef JEUD_HPP
#define JEUD_HPP

#include "Jeu.hpp"
#include "Elements/PionD.hpp"
#include "Elements/Capture.hpp"

class JeuD : public Jeu {

private :
    std::vector<Capture*> captures;
    void capturer(int ancienneLigne, int ancienneColonne, int nouvelleLigne, int nouvelleColonne);
    bool captureValide(int ancienneLigne, int ancienneColonne, int nouvelleLigne, int nouvelleColonne) const;
    void annulerCapture(const std::vector<Capture*>& captures_, int ligne, int colonne);
    void capturePossiblePion(std::vector<Capture*>& captures_pion, PionD* pion, int ligne, int colonne);
    std::vector<Capture*> capturePossible();

    bool deplacementValide(int ancienneLigne, int ancienneColonne, int nouvelleLigne, int nouvelleColonne) const;
    void deplacer(int ancienneLigne, int ancienneColonne, int nouvelleLigne, int nouvelleColonne);
    void maj_tour();

public:
    JeuD();

    void get_chemin_case(int ancienneLigne, int ancienneColonne, int nouvelleLigne, int nouvelleColonne, std::vector<Case*>& v) const;

    void captureMaximum();

    void capturer(Capture *capture);

    friend class TestD;

};

#endif