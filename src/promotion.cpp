/*
    Autore: MARCO MASIERO
*/

#include "../include/chessboard.h"
#include <iostream>


/**
 * @brief Funzione per la promozione del pedone \n
 * Controlla ad ogni turno se un pedone e' entrato nelle posizioni di promozione. \n
 * Se viene attivato il metodo fa scegliere il giocatore la nuova pedina o prende una decisione casuale per il computer
 * 
 * @param is_player_game Indica se e' presente il giocatore nella partita in corso, necessario per decidere se scegliere autonomamente 
 * la nuova pedina o fare una scelta casuale
 * @return Il carattere della nuova pedina scelta per inserirla nel log 
 */
char Chessboard::check_for_promotion(bool is_player_game) {
    char s = 0;

    for(int i = 0; i < 8; i += 7) {
        for(int j = 0; j < 8; j++) {
            Chess* chess = get_cell(i,j);
            bool chess_color = chess->is_white;
            // se un pedone che si muove verso l'alto e' arrivato alla fine (pedone del player)
            if(tolower(chess->get_char()) == 'p') {
                // Se nella partita c'e' il giocatore e la pedina in promozione e' la sua
                if(is_player_game && chess_color == color_player) s = promotion_chess_choose();
                // altrimenti promozione casuale
                else {
                    std::vector<char> possible_promotions = {'a','d','c','t'};
                    int random_i = rand()%4;
                    s = possible_promotions[random_i];
                } 

                switch(tolower(s)) {
                    case 'd':
                        delete board[i][j];
                        board[i][j] = new Queen(chess_color);
                        break;
                    case 'c':
                        delete board[i][j];
                        board[i][j] = new Knight(chess_color);
                        break;
                    case 'a':
                        delete board[i][j];
                        board[i][j] = new Bishop(chess_color);
                        break;
                    case 't':
                        delete board[i][j];
                        board[i][j] = new Rook(chess_color);
                        break;
                }
            }
        }
    }

    return s;
}


/**
 * @brief Funzione privata per la scelta della nuova pedina casuale \n
 * Nel caso un pedone appartenente al computer entra nella zona di promozione viene presa una scelta casuale tra le 4 scelte disponibili
 * 
 * @return Il carattere della nuova pedina scelta per inserirla nel log 
 */
char Chessboard::promotion_chess_choose() {
    char c = 0;
    bool valid = false;

    while(!valid) {
        std::cout << "Pawn Promotion! Choose a new chess [D/C/A/T]: ";
        std::cin >> c;

        char c_low = tolower(c);
        if(c_low == 'd' || c_low == 'c' || c_low == 'a' || c_low == 't') valid = true;
        else std::cout << "Inserted letter not valid\n";
    }

    return c;
}
 

/**
 * @brief Funzione per gestire la promozione nel programma di replay
 * 
 * @param pos Indica la posizione in cui il pedone e' andato in promozione e la posizione della nuova pedina
 * @param chess_char Indica il carattere identificativo del nuovo scacco che prendera' il posto del pedone promosso
 */
void Chessboard::replay_promotion(Position pos, char chess_char) {
    bool color = get_cell(pos.row, pos.col)->is_white;
    switch(tolower(chess_char)) {
        case 'd':
            delete board[pos.row][pos.col];
            board[pos.row][pos.col] = new Queen(color);
            break;
        case 'c':
            delete board[pos.row][pos.col];
            board[pos.row][pos.col] = new Knight(color);
            break;
        case 'a':
            delete board[pos.row][pos.col];
            board[pos.row][pos.col] = new Bishop(color);
            break;
        case 't':
            delete board[pos.row][pos.col];
            board[pos.row][pos.col] = new Rook(color);
            break;
    }
}