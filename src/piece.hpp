#ifndef PIECE_HPP
#define PIECE_HPP

#include "color.hpp"

class Piece {

private:
    const Color color;
    bool king;

    Piece(Color color_);
    Piece(Piece &other) = delete;
    Piece& operator=(Piece &other) = delete;

    void set_king();

};

#endif