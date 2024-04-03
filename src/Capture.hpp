#ifndef CAPTURE_HPP
#define CAPTURE_HPP

#include "PionD.hpp"
#include "Case.hpp"
#include <vector>
#include <iostream>

class Capture {

private:
    const std::vector<std::vector<Case*>>& plateau;
    std::vector<Case*> chemin;
    std::vector<std::pair<PionD*, Case*>> pions_captures;
    PionD* pion;

    void get_chemin_case(const std::vector<std::vector<Case*>>& plateau, int ancienneLigne, int ancienneColonne, int nouvelleLigne, int nouvelleColonne, std::vector<Case*>& v) const;
    Capture(std::vector<std::vector<Case*>>& plateau, int ancienneLigne, int ancienneColonne, int nouvelleLigne, int nouvelleColonne);
    Capture(Capture& capture, int ancienneLigne, int ancienneColonne, int nouvelleLigne, int nouvelleColonne);
    ~Capture();

    Capture& operator=(Capture &other) = delete;
    
    friend std::ostream& operator<<(std::ostream& os, const Capture& capture);
    friend class JeuD;
};

#endif