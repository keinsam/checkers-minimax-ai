#include "piece.hpp"

Piece::Piece(Color color_)
	: color{color_}, king{false}
	{}

void Piece::set_king() {
	king = true;
}