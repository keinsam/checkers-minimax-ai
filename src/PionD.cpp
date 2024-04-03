#include "PionD.hpp"

PionD::PionD(Couleur couleur_)
	: Pion(), couleur{couleur_}, isDame{false}
	{}

Couleur PionD::getCouleur() const {
	return couleur;
}

bool PionD::getIsDame() const {
	return isDame;
}

void PionD::setIsDame() {
	isDame = true;
}