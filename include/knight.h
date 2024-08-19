/*
    Autore: HAJJAJ BARISON
*/

#ifndef KNIGHT_H
#define KNIGHT_H

#include "chess.h"

class Knight : public Chess { // CAVALLO
public:
    Knight(bool w) {
        is_white = w;
        chess_char = 'c';
    }

    bool is_move_legal(std::array<std::array<Chess*, 8>, 8>& board, const Position p1, const Position p2) const;
};

#endif // KNIGHT_H