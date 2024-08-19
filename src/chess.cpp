/*
    Autore: HAJJAJ BARISON
*/

#include "../include/chess.h"

/**
 * Questa funzione ci fornisce tutte le mosse possibili che puo' fare una pedina partendo da p1.
 *
 * @param board: stato attuale della scacchiera
 * @param p1: posizione iniziale della pedina
 * @return Possibili posizioni finali di p1
 */
std::vector<Position> Chess::possible_final_positions(std::array<std::array<Chess*, 8>, 8>& board, const Position p1) const {
    std::vector<Position> to_return = std::vector<Position>{};
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Position p2 {i, j};
            if((p1 != p2) && is_move_legal(board, p1, p2))
                to_return.push_back(p2);
        }
    }
    return to_return;
}