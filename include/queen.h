/*
    Autore: MARCO MASIERO
*/

#ifndef QUEEN_H
#define QUEEN_H

#include "chess.h"

class Queen : public Chess { // REGINA
public:
    Queen(bool w) {
        is_white = w;
        chess_char = 'd';
    }

    bool is_move_legal(std::array<std::array<Chess*, 8>, 8>& board, const Position p1, const Position p2) const;
};

#endif // QUEEN_H