/*
    Autore: MARCO FACCO
*/


#include "../include/king.h"

/**
 * @brief 
 * Controllo per verificare se il re puo' eseguire la mossa
 * @param board scacchiera
 * @param p1 posizione iniziale
 * @param p2 posizione finale
 * @return true - mossa possibile
 * @return false - mossa non possibile
 */
bool King::is_move_legal(std::array<std::array<Chess*, 8>, 8>& board, const Position p1, const Position p2) const {

    // Controllo che le posizioni differenzino al piu' di una
    if (abs(p2.row - p1.row) > 1 || abs(p2.col - p1.col) > 1) return false;
    // Controllo che non ci sia una pedina amica nella posizione finale
    if (this->is_white == board[p2.row][p2.col]->is_white && board[p2.row][p2.col]->get_char() != ' ') return false;

    // Controllo che tutte le pedine avversarie non possano spostarsi nella posizione finale
    return !check(board, p1, p2);
}

/**
 * @brief 
 * Controllo se il re e' sotto scacco nella posizione finale
 * @param board scacchiera
 * @param p1 posizione iniziale
 * @param p2 posizione finale
 * @return true - il re e' sotto scacco nella posizione finale
 * @return false - il re non e' sotto scacco nella posizione finale
 */
bool King::check(std::array<std::array<Chess*, 8>, 8>& board, const Position p1, const Position p2) const {
    // eseguo momentaneamente la mossa del re
    Chess* p2_chess = board[p2.row][p2.col];
    if(p1 != p2) {
        board[p2.row][p2.col] = board[p1.row][p1.col];
        board[p1.row][p1.col] = new Empty();
    }

    // nel caso in cui il re nella posizione finale abbia attorno il re avversario sarebbe sotto scacco
    for (int i = -1; i < 2; i++)
        for (int j = -1; j < 2; j++)
            if (Position{i, j}.is_valid() && tolower(board[i][j]->get_char()) == 'r') {
                if(p1 != p2) { // annullo mossa temporanea
                    delete board[p1.row][p1.col];
                    board[p1.row][p1.col] = board[p2.row][p2.col];
                    board[p2.row][p2.col] = p2_chess;
                }
                return true;
            }

    // nel caso le altre pedine avversarie possano catturare il re nella posizione finale non e' scacco in quella posizione
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j]->get_char() != ' ' && tolower(board[i][j]->get_char()) != 'r')
                if(board[i][j]->is_white != this->is_white && board[i][j]->can_take(board, Position {i, j}, p2)) {
                    if(p1 != p2) { // annullo mossa temporanea
                        delete board[p1.row][p1.col];
                        board[p1.row][p1.col] = board[p2.row][p2.col];
                        board[p2.row][p2.col] = p2_chess;
                    }
                    return true;
                }
        }
    }

    if(p1 != p2) { // annullo mossa temporanea
        delete board[p1.row][p1.col];
        board[p1.row][p1.col] = board[p2.row][p2.col];
        board[p2.row][p2.col] = p2_chess;
    }
    
    return false;
}
