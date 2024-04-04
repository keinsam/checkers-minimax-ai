#ifndef BOARD_HPP
#define BOARD_HPP

#include "square.hpp"
#include <vector>

class Board {

public :
    static const int ROWS;
    static const int COLS;
    std::vector<std::vector<Square*>> squares;
    std::vector<Piece*> pieces;

    Board();
    Board(Board &other) = delete;
    Board& operator=(Board &other) = delete;

    friend class Square;

};

#endif