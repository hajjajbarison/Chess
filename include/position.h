/*
    Autore: MARCO FACCO
*/

#ifndef POSITION_H
#define POSITION_H

#include <string>
#include <sstream>

struct Position {
    int row, col;
    Position() {};
    Position(int r, int c) : row{r}, col{c} {};

    std::string reverse_position();

    bool is_valid() {
        return row >= 0 && col >= 0 && row < 8 && col < 8;
    }

    bool operator==(const Position& p2) const;
    bool operator!=(const Position& p2) const;
};

Position convert_position(const std::string pos);

#endif
