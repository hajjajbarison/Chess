/*
    Autore: HAJJAJ BARISON
*/

#include "../include/knight.h"

/**
 * Questa funzione effettua i controlli per vedere se il movimento del cavallo da p1 a p2 e' possibile. \n
 * Il controllo e' fatto basandosi sul movimento ad "L" del cavallo.
 *
 * @param board: stato attuale della scacchiera
 * @param p1: posizione attuale del cavallo
 * @param p2: posizione finale del cavallo
 * @return Valore bool che ci indica se la mossa e' possibile o meno
 */


bool Knight::is_move_legal(std::array<std::array<Chess*, 8>, 8>& board, const Position p1, const Position p2) const {

    if ((board[p2.row][p2.col]->is_white != is_white) || board[p2.row][p2.col]->get_char() == ' '){
        if((p2.row == p1.row-1 && (p2.col == p1.col-2 || p2.col == p1.col+2))
            || (p2.row == p1.row+1 && (p2.col == p1.col-2 || p2.col == p1.col+2))
            || (p2.row == p1.row-2 && (p2.col == p1.col-1 || p2.col == p1.col+1))
            || (p2.row == p1.row+2 && (p2.col == p1.col-1 || p2.col == p1.col+1)) ){
            return true;
        }
        else return false;
    }

    return false;
}