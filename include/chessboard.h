/*
    Autore: MARCO MASIERO
*/

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "chess.h"
#include "pawn.h"
#include "rook.h"
#include "bishop.h"
#include "king.h"
#include "queen.h"
#include "knight.h"
#include "empty.h"
#include "position.h"

#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <iostream>

class Chessboard {
public:
    // COSTRUTTORE E GETTER, DEFINITI NEL FILE chessboard.cpp
    
    Chessboard();
    Chess* get_cell(const int row, const int col) const;
    bool get_color_player() const;
    std::array<std::array<Chess*, 8>, 8> get_board() const;


    // FUNZIONI DI MOVIMENTO, DEFINITE NEL FILE movements.cpp

    std::string print_board() const;
    bool move_chess(const std::string pos1, const std::string pos2); // muove lo scacco dalla posizione pos1 alla posizione pos2
    std::string random_move(bool is_white); // is_white indica di che colore e' il giocatore
    
    
    // FUNZIONI DI CONTROLLO PARTITA, DEFINITE NEL FILE controls.cpp

    bool check_mate(bool is_white);
    bool is_game_finished();
    bool draw(std::string log_name, std::string move);
    bool is_pinned(const Position p1, const Position p2);
    
    
    // FUNZIONI MOSSE SPECIALI, DEFINITE NEI FILE promotion.cpp castling.cpp
    
    char check_for_promotion(bool is_player_game); 
    // Promozione del pedone per il replay partita
    void replay_promotion(Position pos, char chess_char); 
    bool king_castling(Position p1, Position p2);
 
private:
    std::array<std::array<Chess*, 8>, 8> board;
    bool color_player;

    // contatore per le mosse consecutive in cui non viene mangiata nessuna pedina
    int only_moves_count; 

    // variabili per memorizzare le posizioni dei re nella scacchiera
    Position king_w;
    Position king_b;

    // puntatore alla pedina che potrebbe essere mangiata tramite en passant
    Pawn* en_passant;  
    
    bool move_chess(Position pos1, Position pos2);
    
    // fa scegliere al player la nuova pedina che sostituisce il pedone in promozione
    char promotion_chess_choose();
};

#endif