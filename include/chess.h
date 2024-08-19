/*
    Autore: HAJJAJ BARISON
*/

#ifndef CHESS_H
#define CHESS_H

#include "position.h"

#include <ctype.h>
#include <iostream>
#include <vector>
#include <array>

/**
 * Classe padre di tutte le pedine.
 */
class Chess {
public:
    bool is_first_move = true;
    bool is_white;

    char get_char() {
        if(is_white) return tolower(chess_char);
        return toupper(chess_char);
    }

    virtual bool is_move_legal(std::array<std::array<Chess*, 8>, 8>& board, const Position p1, const Position p2) const = 0;

    virtual bool can_take(std::array<std::array<Chess*, 8>, 8>& board, const Position p1, const Position p2) const {
        return is_move_legal(board, p1, p2);
    }
    
    std::vector<Position> possible_final_positions(std::array<std::array<Chess*, 8>, 8>& board, const Position p1) const;

protected:
    
    char chess_char;
};

#endif