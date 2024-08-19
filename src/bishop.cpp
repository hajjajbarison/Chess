/*
    Autore: MARCO FACCO
*/

#include "../include/bishop.h"

/**
 * @brief 
 * Controllo per verificare se l'alfiere puo' eseguire la mossa (l'inchiodamento viene gestito a parte)
 * @param board scacchiera
 * @param p1 posizione iniziale
 * @param p2 posizione finale
 * @return true - mossa possibile
 * @return false - mossa non possibile
 */
bool Bishop::is_move_legal(std::array<std::array<Chess*, 8>, 8>& board, const Position p1, const Position p2) const {

    int mov = abs(p2.row - p1.row);

    if (mov != abs(p2.col - p1.col)) return false; // Controllo che la pedina si sposti in diagonale

    int s_r = (p2.row - p1.row)/mov; // Segno per spostamento sulle righe
    int s_c = (p2.col - p1.col)/mov; // Segno per spostamento sulle colonne

    // Controllo che tra la posizione iniziale e quella finale non ci siano pedine
    for (int i = 1; i < mov; i++)
        if (board[p1.row + i * s_r][p1.col + i * s_c]->get_char() != ' ') return false;

    //Controllo che l'alfiere possa essere nella posizione finale
    if (board[p1.row][p1.col]->is_white == board[p2.row][p2.col]->is_white && board[p2.row][p2.col]->get_char() != ' ') return false;

    return true;
}