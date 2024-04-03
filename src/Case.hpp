#ifndef CASE_HPP
#define CASE_HPP

#include "Pion.hpp"
#include "../../utils/Couleurs.hpp"
#include <vector>

class Case {

private :
    Pion* pion;
    const Couleur couleur;
    bool marque;

    Case(Couleur couleur_);
    Case(Case &other) = delete;
    Case& operator=(Case &other) = delete;

    void setPion(Pion* pion_);
    void clearMarque();
    void setMarque();

public :
    Pion* getPion() const;
    Couleur getCouleur() const;
    int getLigne(const std::vector<std::vector<Case*>>& plateau) const;
    int getColonne(const std::vector<std::vector<Case*>>& plateau) const;
    bool estVide() const;
    bool estMarque() const;


    friend class JeuI;
    friend class JeuD;
    friend class JeuS;

};


#endif
