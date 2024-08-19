/*
    Autore: HAJJAJ BARISON
*/


#ifndef ROOK_H
#define ROOK_H

#include "chess.h"
#include "king.h"

class Rook : public Chess { // TORRE
public:
    Rook(bool w) {
        is_white = w;
        chess_char = 't';
    }

    bool is_move_legal(std::array<std::array<Chess*, 8>, 8>& board, const Position p1, const Position p2) const;

};

#endif // ROOK_H