#include "board.hpp"

using namespace std;

const int Board::ROWS = 8;
const int Board::COLS = 8;

Board::Board() {

    // Create the board of squares
    for (int i = 0; i < ROWS; i++) {
        vector<Square*> row;
        int id_count = 1;
        for (int j = 0; j < COLS; j++) {
            if ((i + j) % 2 != 0) {
                row.push_back(new Square(to_string(id_count), BROWN, i, j));
                id_count++;
            } else {
                row.push_back(new Square(BEIGE, i, j));
            }
        }
        squares.push_back(row);
    }

    // Add the pieces on the board
    for(int i = 0; i < ROWS-ROWS/2-1; i++) { // For BLACK
        for (Square* square: this->squares[i]) {
            if(square->color == BROWN) {
                Piece* piece = new Piece(BLACK);
                square->set_piece(piece);
                this->pieces.push_back(piece);
            }
        }
    }
    for(int i = ROWS-ROWS/2+1; i < ROWS; i++) { // For WHITE
        for (Square* square: this->squares[i]) {
            if(square->color == BROWN) {
                Piece* piece = new Piece(WHITE);
                square->set_piece(piece);
                this->pieces.push_back(piece);
            }
        }
    }

}