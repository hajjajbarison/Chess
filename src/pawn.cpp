/*
    Autore: MARCO FACCO
*/

#include "../include/pawn.h"

/**
 * @brief 
 * Controllo per verificare se il pedone puo' eseguire la mossa (l'inchiodamento viene gestito a parte)
 * @param board scacchiera
 * @param p1 posizione iniziale
 * @param p2 posizione finale
 * @return true - mossa possibile
 * @return false - mossa non possibile
 */
bool Pawn::is_move_legal(std::array<std::array<Chess*, 8>, 8>& board, const Position p1, const Position p2) const {
    int sgn = direction_up ? +1 : -1;

    // MOVIMENTO
    if(p1.col == p2.col) {
        if(p1.row-(1*sgn) == p2.row) {
            if(board[p2.row][p2.col]->get_char() == ' ') return true;
        }
        else if(is_first_move && board[p1.row-sgn][p1.col]->get_char() == ' ')
            if(p1.row-(2*sgn) == p2.row) {
                return true;
            }
    }

    // MANGIARE
    if(p1.col-(1*sgn) == p2.col || p1.col+(1*sgn) == p2.col) // controllo colonna a destra o a sinistra
        if(p1.row-(1*sgn) == p2.row) { // controllo movimento di una casella in avanti
            if(board[p2.row][p2.col]->get_char() != ' ') {
                if (board[p2.row][p2.col]->is_white != is_white)
                    return true;
            }
            else if ((tolower(board[p1.row][p2.col]->get_char()) == 'p')  // controllo en_passant
                    && (board[p1.row][p2.col]->is_white != is_white)
                    && (dynamic_cast<Pawn*>(board[p1.row][p2.col])->is_en_passant()))
                        return true;
    }

    return false;
}

/**
 * @brief 
 * Funzione per il controllo se il pedone puo' mangiare nella posizione finale - va solo associata con l'is_move_legal (utile per il check)
 * @param board scacchiera
 * @param p1 posizione iniziale
 * @param p2 posizione finale
 * @return true - il pedone puo' mangiare nella posizione finale
 * @return false - il pedone non puo' mangiare nella posizione finale
 */
bool Pawn::can_take(std::array<std::array<Chess*, 8>, 8>& board, const Position p1, const Position p2) const {
    int sgn = direction_up ? +1 : -1;

    // MANGIARE
    if(p1.col-1 == p2.col || p1.col+1 == p2.col) // Controllo colonna a destra o a sinistra
        if(p1.row-(1*sgn) == p2.row) // Controllo movimento di una casella in avanti
            return true;

    return false;
}
