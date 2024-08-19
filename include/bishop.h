/*
    Autore: MARCO FACCO
*/

#ifndef BISHOP_H
#define BISHOP_H

#include "chess.h"

class Bishop : public Chess { // ALFIERE
public:
    Bishop(bool w) {
        is_white = w;
        chess_char = 'a';
    }

    bool is_move_legal(std::array<std::array<Chess*, 8>, 8>& board, const Position p1, const Position p2) const;
};

#endif // BISHOP_H