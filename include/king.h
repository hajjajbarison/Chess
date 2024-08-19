/*
    Autore: MARCO FACCO
*/

#ifndef KING_H
#define KING_H

#include "chess.h"
#include "position.h"
#include "pawn.h"
#include "empty.h"

#include <array>

class King : public Chess { // RE
public:
    King(bool w) {
        is_white = w;
        chess_char = 'r';
    }

    bool is_move_legal(std::array<std::array<Chess*, 8>, 8>& board, const Position p1, const Position p2) const;
    bool check(std::array<std::array<Chess*, 8>, 8>& board, const Position p1, const Position p2) const; // Scacco al re
};

#endif // KING_H