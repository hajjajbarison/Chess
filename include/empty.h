/*
    Autore: MARCO MASIERO
*/

#ifndef EMPTY_H
#define EMPTY_H

#include "chess.h"


 // CASELLA VUOTA
class Empty : public Chess {
public:
    Empty() {
        chess_char = ' ';
    }

    // is_move_legal non e' possibile in una casella vuota, ritorna sempre false
    bool is_move_legal(std::array<std::array<Chess*, 8>, 8>& board, const Position p1, const Position p2) const {return false;}
};

#endif // EMPTY_H