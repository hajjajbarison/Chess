/*
    Autore: MARCO MASIERO
*/

#include "../include/queen.h"

bool Queen::is_move_legal(std::array<std::array<Chess*, 8>, 8>& board, const Position p1, const Position p2) const {
    int dr = p2.row - p1.row; // delta row: numero di caselle in orizzontale di quanto ci si e' spostati
    int dc = p2.col - p1.col; // delta col: numero di caselle in verticale di quanto ci si e' spostati

    if(dr == 0 && dc == 0) return false; // se rimango nella stessa posizione la mossa non e' valida
    
    /*  ===========================
        |  MOVIMENTO IN VERTICALE |
        =========================== */
    if(p1.col == p2.col) {
        if(dr < 0) { // Mi sto muovendo in avanti
            for(int i = -1; i > dr; i--) {
                // Controllo se in mezzo al percorso ci sono altre pedine TRANNE NELLA POSIZIONE FINALE
                // Se ci sono pedine in mezzo al percorso la mossa non e' valida
                if(board[p1.row+i][p1.col]->get_char() != ' ') return false;
            }
        }

        else if(dr > 0) { // Mi sto muovendo indietro
            for(int i = 1; i < dr; i++) {
                // Controllo se in mezzo al percorso ci sono altre pedine TRANNE NELLA POSIZIONE FINALE
                // Se ci sono pedine in mezzo al percorso la mossa non e' valida
                if(board[p1.row+i][p1.col]->get_char() != ' ') return false;
            }
        }

        // Controllo la posizione finale in cui ci puo essere una pedina nemica
        if(board[p2.row][p2.col]->get_char() == ' ') return true; // Se ce il vuoto la mossa e' valida
        else if(board[p2.row][p2.col]->get_char() != ' ')
            if(board[p2.row][p2.col]->is_white != is_white) // Se c'e' una pedina avversaria allora e' valido
                return true;
    }

    /*  =============================
        |  MOVIMENTO IN ORIZZONTALE |
        ============================= */
    if(p1.row == p2.row) {
        if(dc < 0) { // Mi sto muovendo a sinistra
            for(int i = -1; i < dc; i--) {
                // Controllo se in mezzo al percorso ci sono altre pedine TRANNE NELLA POSIZIONE FINALE
                // Se ci sono pedine in mezzo al percorso la mossa non e' valida
                if(board[p1.row][p1.col+i]->get_char() != ' ') return false;
            }
        }

        else if(dc > 0) { // Mi sto muovendo a destra
            for(int i = 1; i < dc; i++) {
                // Controllo se in mezzo al percorso ci sono altre pedine TRANNE NELLA POSIZIONE FINALE
                // Se ci sono pedine in mezzo al percorso la mossa non e' valida
                if(board[p1.row][p1.col+i]->get_char() != ' ') return false;
            }
        }

        // Controllo la posizione finale in cui ci puo essere una pedina nemica
        if(board[p2.row][p2.col]->get_char() == ' ') return true; // Se ce il vuoto la mossa e' valida
        else if(board[p2.row][p2.col]->get_char() != ' ')
            if(board[p2.row][p2.col]->is_white != is_white) // Se c'e' una pedina avversaria allora e' valido
                return true;
    }

    /*  ===========================
        |  MOVIMENTO IN DIAGONALE |
        ===========================  */
    if(abs(dr) == abs(dc)) { // solo quando mi muovo dello stesso numero di caselle in vert. e orizz.
        if(dc > 0 && dr < 0) {
            for(int i = 1; i < dc; i++) {
                // Controllo se in mezzo al percorso ci sono altre pedine TRANNE NELLA POSIZIONE FINALE
                // Se ci sono pedine in mezzo al percorso la mossa non e' valida
                if(board[p1.row-i][p1.col+i]->get_char() != ' ') return false;
            }
        }

        else if(dc > 0 && dr > 0) {
            for(int i = 1; i < dc; i++) {
                // Controllo se in mezzo al percorso ci sono altre pedine TRANNE NELLA POSIZIONE FINALE
                // Se ci sono pedine in mezzo al percorso la mossa non e' valida
                if(board[p1.row+i][p1.col+i]->get_char() != ' ') return false;
            }
        }

        else if(dc < 0 && dr > 0) {
            for(int i = 1; i < dr; i++) {
                // Controllo se in mezzo al percorso ci sono altre pedine TRANNE NELLA POSIZIONE FINALE
                // Se ci sono pedine in mezzo al percorso la mossa non e' valida
                if(board[p1.row+i][p1.col-i]->get_char() != ' ') return false;
            }
        }

        else if(dc < 0 && dr < 0) {
            for(int i = 1; i < -dc; i++) {
                // Controllo se in mezzo al percorso ci sono altre pedine TRANNE NELLA POSIZIONE FINALE
                // Se ci sono pedine in mezzo al percorso la mossa non e' valida
                if(board[p1.row-i][p1.col-i]->get_char() != ' ') return false;
            }
        }

        // Controllo la posizione finale in cui ci puo essere una pedina nemica
        if(board[p2.row][p2.col]->get_char() == ' ') return true; // Se ce il vuoto la mossa e' valida
        else if(board[p2.row][p2.col]->get_char() != ' ')
            if(board[p2.row][p2.col]->is_white != is_white) // Se c'e' una pedina avversaria allora e' valido
                return true;
    }

    return false;
}