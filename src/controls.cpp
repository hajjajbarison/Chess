/*
    Autore: MARCO FACCO
*/


#include "../include/chessboard.h"
#include <iostream>
#include <ctype.h>
#include <sstream>

/**
 * @brief 
 * Controllo se una pedina sarebbe inchiodata nella posizione finale
 * @param p1 posizione iniziale della pedina
 * @param p2 posizione finale della pedina
 * @return true - la pedina e' inchiodata: non si potrebbe muovere
 * @return false - la pedina non e' inchiodata: si potrebbe muovere
 */
bool Chessboard::is_pinned(const Position p1, const Position p2) {
    
    if(tolower(board[p1.row][p1.col]->get_char()) == 'r')
        return false; // tenendo conto che precedentemente e' stato fatto l'is_move_legal

    bool to_ret = false;

    // attuo la mossa temporaneamente
    Chess* p2_chess = board[p2.row][p2.col];
    if (p1 != p2) {
        board[p2.row][p2.col] = board[p1.row][p1.col];
        board[p1.row][p1.col] = new Empty();
    }
    
    // controllo se il re e' sotto scacco dopo avere effettuato la mossa
    if (board[p2.row][p2.col]->is_white)
        to_ret = dynamic_cast<King*>(board[king_w.row][king_w.col])->check(board, king_w, king_w);
    else
        to_ret = dynamic_cast<King*>(board[king_b.row][king_b.col])->check(board, king_b, king_b);

    // annullo la mossa temporanea
    if(p1 != p2) {
        delete board[p1.row][p1.col];
        board[p1.row][p1.col] = board[p2.row][p2.col];
        board[p2.row][p2.col] = p2_chess;
    }
    return to_ret;
}

/**
 * @brief 
 * controllo se uno dei due re ha subito scacco matto
 * @return true - uno dei due re ha subito scacco matto
 * @return false - nessuno dei re ha subito scacco matto
 */
bool Chessboard::is_game_finished() {
    if (check_mate(true) || check_mate(false))
        return true;
    return false;
}

/**
 * @brief 
 * Controllo se un giocatore ha subito lo scacco matto
 * @param is_white colore del giocatore
 * @return true - il giocatore ha subito lo scacco matto
 * @return false - il giocatore non ha subito lo scacco matto
 */
bool Chessboard::check_mate(bool is_white) {

    Position pos_king;
    if (is_white)
        pos_king = king_w;
    else
        pos_king = king_b;
    
    King* king = dynamic_cast<King*>(board[pos_king.row][pos_king.col]);
    
    // Nel caso in cui il re non sarebbe sotto scacco nella sua posizione attuale e in quelle vicine a lui restituisce false
    for (int i = -1; i < 2; i++)
        for (int j = -1; j < 2; j++)
            if (Position{i, j}.is_valid() && !king->check(board, pos_king, Position {pos_king.row + i, pos_king.col + j}))
                return false;

    // vector con tutte le posizioni delle pedine del colore del re
    // (che spostandosi potrebbero eventualmente coprire il re da un eventuale scacco matto)
    std::vector<Position> possible_pawns = std::vector<Position>();
    
    for (int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            if(board[i][j]->get_char() != ' ' && board[i][j]->is_white == is_white && tolower(board[i][j]->get_char()) != 'r')
                possible_pawns.push_back(Position{i, j});

    
    while (possible_pawns.size() != 0) {
        
        Position p1 = possible_pawns.at(0);
        std::vector<Position> final_pos = board[p1.row][p1.col]->possible_final_positions(board, p1);

        while (final_pos.size() != 0) {
            Position p2 = final_pos.at(0);
            
            // nel caso in cui la pedina non sia inchiodata anche dopo avere fatto la mossa (re non sotto scacco) restituisce false
            if (!is_pinned(p1, p2))
                 return false;
            else
                // la pedina rimane inchiodata nella posizione presa in considerazione: elimino posizione finale della pedina
                final_pos.erase(final_pos.begin());
        }
        // la pedina non ha piu' mosse disponibili: elimino posizione della pedina
        possible_pawns.erase(possible_pawns.begin());
    }
    // caso finale: nessuna pedina puo' eseguire una mossa valida: il re ha subito scacco matto
    return true;
}

/**
 * @brief 
 * Controllo patta
 * @param log_name log della partita attuale
 * @param move stringa dell'ultima mossa eseguita
 * @return true - le condizioni per la patta sono valide
 * @return false - le condizioni per la patta non sono valide
 */
bool Chessboard::draw(std::string log_name, std::string move) {
    if(only_moves_count > 50) return true;

    std::ifstream log;
    log.open(log_name);
    std::string line;
    int count = 0;

    while(getline(log, line)) { 
        if(line.substr(0,7) == move) count++;
    }
    log.close();

    if(count >= 3) return true;
    
    return false;
}