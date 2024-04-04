#include "square.hpp"

using namespace std;

Square::Square(std::string id_, Color color_, int row_, int col_)
	: piece{nullptr}, id{id_}, color{color_}, row{row_}, col{col_}
	{}

Square::Square(Color color_, int row_, int col_)
	: piece{nullptr}, color{color_}, row{row_}, col{col_}
	{}

void Square::set_piece(Piece* piece_) {
	this->piece = piece_;
}

bool Square::is_empty() const {
	return this->piece == nullptr;
};