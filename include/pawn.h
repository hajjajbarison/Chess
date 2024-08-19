/*
    Autore: MARCO FACCO
*/

#ifndef PAWN_H
#define PAWN_H

#include "chess.h"

class Pawn : public Chess { // PEDONE
public:
    Pawn(bool w, bool direction) {
        is_white = w;
        direction_up = direction;
        chess_char = 'p';
        en_passant = false;
    }

    bool is_move_legal(std::array<std::array<Chess*, 8>, 8>& board, const Position p1, const Position p2) const;
    bool can_take(std::array<std::array<Chess*, 8>, 8>& board, const Position p1, const Position p2) const;

    bool direction() const { return direction_up; }
    bool is_en_passant() const { return en_passant; }
    void set_en_passant(bool b) { en_passant = b; }
private:
    bool direction_up;
    bool en_passant;
};

#endif // PAWN_H