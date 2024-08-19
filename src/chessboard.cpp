/*
    Autore: MARCO MASIERO
*/

#include "../include/chessboard.h"
#include <iostream>
#include <ctype.h>
#include <sstream>

/**
 * @brief Costruttore della classe Chessboard
 * Crea un nuovo oggetto scacchiera inizializzata nella posizione di inizio partita
 */
Chessboard::Chessboard() {
    bool color = rand() > (RAND_MAX / 2);
    color_player = !color;

    // INIZIALIZZO LA SCACCHIERA CON CELLE VUOTE
    for(int i = 2; i < 6; i++)
        for(int j = 0; j < 8; j++)
            board[i][j] = new Empty();

    // FILA DI SCACCHI AVVERSARI
    board[0][0] = new Rook(color);
    board[0][1] = new Knight(color);
    board[0][2] = new Bishop(color);
    board[0][3] = new Queen(color);
    board[0][4] = new King(color);
    board[0][5] = new Bishop(color);
    board[0][6] = new Knight(color);
    board[0][7] = new Rook(color);

    for(int i = 0; i < 8; i++) // PEDONI LATO AVVERSARIO
        board[1][i] = new Pawn(color, false); 

    for(int i = 0; i < 8; i++) // PEDONI LATO UTENTE
        board[6][i] = new Pawn(!color, true); 


    // FILA DI SCACCHI UTENTE
    board[7][0] = new Rook(!color);
    board[7][1] = new Knight(!color);
    board[7][2] = new Bishop(!color);
    board[7][3] = new Queen(!color);
    board[7][4] = new King(!color);
    board[7][5] = new Bishop(!color);
    board[7][6] = new Knight(!color);
    board[7][7] = new Rook(!color);

    // MEMORIZZO LE VABIABILI DI POSIZIONE DEI RE
    if(color) {
        king_w = Position {0, 4}; // 0 4
        king_b = Position {7, 4}; // 7 4
    }
    else  {
        king_b = Position {0, 4}; // 0 4
        king_w = Position {7, 4}; // 7 4
    }

    en_passant = nullptr;
    only_moves_count = 0;
}

/**
 * @brief Funzione per la restituzione di una pedina in una determinata posizione al di fuori della classe Chessboard
 * 
 * @param row Riga della pedina selezionata
 * @param col Colonna della pedina selezionata
 * @return Puntatore alla pedina selezionata
 */
Chess* Chessboard::get_cell(const int row, const int col) const {
    return board[row][col];
}

/**
 * @brief Restituice l'intera scacchiera al di fuori della classe per permettere i controlli di is_move_legal delle pedine
 * 
 * @return Ritorna la matrice di puntatori alle pedine
 */
std::array<std::array<Chess*, 8>, 8> Chessboard::get_board() const {
    return board;
}

/**
 * @brief Restituisce al di fuori della classe Chessboard il colore del giocatore umano se e' presente nel gioco
 * 
 * @return true: Se il giocatore e' di colore bianco
 * @return false: Se il giocatore e' di colore nero
 */
bool Chessboard::get_color_player() const { 
    return color_player; 
}



