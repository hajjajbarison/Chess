/*
    Autore: HAJJAJ BARISON
*/

#include "../include/chessboard.h"
#include <iostream>

/**
 * Questa funzione si occupa di controllare se il movimento dell'arrocco e' possibile. \n
 * L'arrocco viene chiamato quando il re viene spostato di 2 posizioni verso destra o sinistra. \n
 * La funzione si occupa di gestire tutti e 4 i tipi di arrocco possibili, "lato utente" e "lato avversario", sia verso
 * destra che sinistra.
 *
 * @param p1: posizione iniziale del re
 * @param p2: posizione finale del re
 * @return Valore bool che ci indica se l'arrocco e' possibile o meno
 */
bool Chessboard::king_castling(Position p1, Position p2) {
    if(board[p2.row][p2.col]->is_white != board[p1.row][p1.col]->is_white || board[p2.row][p2.col]->get_char() == ' '){
        // ARROCCO VERSO SINISTRA - LATO UTENTE
        if((p2.row == 7 && p2.col == 2) && (p1.row == 7 && p1.col == 4)){
            // CONTROLLO SE P1 E' IL RE E SE BOARD[7][0] E' LA TORRE
            if(tolower(board[p1.row][p1.col]->get_char()) == 'r' && tolower(board[7][0]->get_char()) == 't'){
                // CONTROLLARE SE PER ENTRAMBI E' LA PRIMA MOSSA
                if(board[p1.row][p1.col]->is_first_move && board[7][0]->is_first_move){
                    // CONTROLLO SE NON C'E' NULLA TRA RE E TORRE
                    if(board[7][1]->get_char() == ' ' && board[7][3]->get_char() == ' ' && board[p2.row][p2.col]->get_char() == ' '){
                        // CONTROLLO SE IL RE NON VA MAI IN SCACCO DURANTE QUESTO ATTRAVERSAMENTO
                        King* king = dynamic_cast<King *>(board[7][4]);
                        Position pos_king = Position {7,4};
                        if(!king->check(board, pos_king, pos_king) && !king->check(board, pos_king, Position {7,3}) && !king->check(board, pos_king, Position {7,2})){
                            // MOVIMENTO DELLA TORRE CON GESTIONE DEL MEMORY LEAK, E ACCETTIAMO LO SPOSTAMENTO DEL RE
                            delete board[7][3];
                            board[7][3] = board[7][0];
                            board[7][0] = new Empty();
                            return true;
                        }
                    }
                }
            }
        }
        // ARROCCO VERSO DESTRA - LATO UTENTE
        else if (p2.row == 7 && p2.col == 6 && (p1.row == 7 && p1.col == 4)){
            // CONTROLLO SE P1 E' IL RE E SE BOARD[7][7] E' LA TORRE
            if(tolower(board[p1.row][p1.col]->get_char()) == 'r' && tolower(board[7][7]->get_char()) == 't'){
                // CONTROLLARE SE PER ENTRAMBI E' LA PRIMA MOSSA
                if(board[p1.row][p1.col]->is_first_move && board[7][7]->is_first_move){
                    // CONTROLLO SE NON C'E' NULLA TRA RE E TORRE
                    if(board[7][5]->get_char() == ' ' && board[p2.row][p2.col]->get_char() == ' '){
                        King* king = dynamic_cast<King *>(board[7][4]);
                        Position pos_king = Position {7,4};
                        // CONTROLLO SE IL RE NON VA MAI IN SCACCO DURANTE QUESTO ATTRAVERSAMENTO
                        if(!king->check(board, pos_king, pos_king) && !king->check(board, pos_king, Position {7,5}) && !king->check(board, pos_king, Position {7,6})){
                            // MOVIMENTO DELLA TORRE CON GESTIONE DEL MEMORY LEAK, E ACCETTIAMO LO SPOSTAMENTO DEL RE
                            delete board[7][5];
                            board[7][5] = board[7][7];
                            board[7][7] = new Empty();
                            return true;
                        }
                    }
                }
            }
        }
            // ARROCCO VERSO SINISTRA - LATO AVVERSARIO
        else if((p2.row == 0 && p2.col == 2) && (p1.row == 0 && p1.col == 4)){
            // CONTROLLO SE P1 E' IL RE E SE BOARD[0][0] E' LA TORRE
            if(tolower(board[p1.row][p1.col]->get_char()) == 'r' && tolower(board[0][0]->get_char()) == 't'){
                // CONTROLLARE SE PER ENTRAMBI E' LA PRIMA MOSSA
                if(board[p1.row][p1.col]->is_first_move && board[0][0]->is_first_move){
                    // CONTROLLO SE NON C'E' NULLA TRA RE E TORRE
                    if(board[0][1]->get_char() == ' ' && board[0][3]->get_char() == ' ' && board[p2.row][p2.col]->get_char() == ' '){
                        // CONTROLLO SE IL RE NON VA MAI IN SCACCO DURANTE QUESTO ATTRAVERSAMENTO
                        King* king = dynamic_cast<King *>(board[0][4]);
                        Position pos_king = Position {0,4};
                        if(!king->check(board,pos_king, pos_king) && !king->check(board,pos_king, Position{0,3}) && !king->check(board,pos_king, Position {0,2})){
                            // MOVIMENTO DELLA TORRE CON GESTIONE DEL MEMORY LEAK, E ACCETTIAMO LO SPOSTAMENTO DEL RE
                            delete board[0][3];
                            board[0][3] = board[0][0];
                            board[0][0] = new Empty();
                            return true;
                        }
                    }
                }
            }
        }
            // ARROCCO VERSO DESTRA - LATO AVVERSARIO
        else if (p2.row == 0 && p2.col == 6 && (p1.row == 0 && p1.col == 4)){
            // CONTROLLO SE P1 E' IL RE E SE BOARD[0][7] E' LA TORRE
            if(tolower(board[p1.row][p1.col]->get_char()) == 'r' && tolower(board[0][7]->get_char()) == 't'){
                // CONTROLLARE SE PER ENTRAMBI E' LA PRIMA MOSSA
                if(board[p1.row][p1.col]->is_first_move && board[0][7]->is_first_move){
                    // CONTROLLO SE NON C'E' NULLA TRA RE E TORRE
                    if(board[0][5]->get_char() == ' ' && board[p2.row][p2.col]->get_char() == ' '){
                        // CONTROLLO SE IL RE NON VA MAI IN SCACCO DURANTE QUESTO ATTRAVERSAMENTO
                        King* king = dynamic_cast<King *>(board[0][4]);
                        Position pos_king = Position {0,4};
                        if(!king->check(board,pos_king, pos_king) && !king->check(board,pos_king, Position{0,5}) && !king->check(board,pos_king, Position{0,6})){
                            // MOVIMENTO DELLA TORRE CON GESTIONE DEL MEMORY LEAK, E ACCETTIAMO LO SPOSTAMENTO DEL RE
                            delete board[0][5];
                            board[0][5] = board[0][7];
                            board[0][7] = new Empty();
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}