#ifndef PIOND_HPP
#define PIOND_HPP

#include "Pion.hpp"
#include "../../utils/Couleurs.hpp"

class PionD : public Pion {

private:
    const Couleur couleur;
    bool isDame;

    PionD(Couleur couleur_);
    void setIsDame();

public :
    Couleur getCouleur() const;
    bool getIsDame() const;

    friend class JeuD;

};

#endif