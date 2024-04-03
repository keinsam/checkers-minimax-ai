#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "piece.hpp"
#include "color.hpp"

#include <string>

class Square {

private :
    const std::string id;
    const Color color;
    const int row;
    const int col;
    Piece* piece;

    Square(std::string id_, Color color_, int row_, int col_);
    Square(Square &other) = delete;
    Square& operator=(Square &other) = delete;

    void set_piece(Piece* piece_);

public :
    bool is_empty() const;

};


#endif
