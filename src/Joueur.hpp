#ifndef JOUEUR_HPP
#define JOUEUR_HPP

#include "Elements/Pion.hpp"
#include <vector>

class Joueur {

private:
    static int compteur_joueurs;
    const int id;
    std::vector<Pion*> pions;

    Joueur();
    Joueur(Joueur &other) = delete;
    Joueur& operator=(Joueur &other) = delete;

    void ajouterPion(Pion *p);
    void enleverPion(const Pion* p);

public:
    ~Joueur();
    int getId() const;
    std::vector<Pion*>& getPions();
    bool contientPion(const Pion* p) const;

    friend class JeuI;
    friend class JeuD;
    friend class JeuS;

};

#endif
