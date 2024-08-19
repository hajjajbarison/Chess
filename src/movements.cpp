/*
    Autore: HAJJAJ BARISON
*/

#include "../include/chessboard.h"
#include <iostream>
#include <ctype.h>
#include <sstream>

/**
 * Questa funzione si occupa di stampare lo stato attuale della scacchiera.
 *
 * @return Sequenza di caratteri che rappresentano le pedine e la scacchiera
 */
std::string Chessboard::print_board() const {
    std::ostringstream oss;
    for(int i = 0; i < 8; i++) {
        oss << 8-i << "  | ";
        for (int j = 0; j < 8; j++) 
            oss << board[i][j]->get_char() << " | ";
        oss << "\n   ---------------------------------\n";
    }

    oss << "\n" << "   | A | B | C | D | E | F | G | H |\n";

    return oss.str();
}


/**
 * Questa funzione riceve in ingresso due posizioni sotto forma di stringa e si occupa di
 * restituirne la posizione associata, di tipo Position, nella forma "B1" "C2"
 *
 * @param pos1: prima posizione
 * @param pos2: seconda posizione
 * @return In un uscita viene invocata la funzione move_chess che accetta come parametri due posizioni di tipo Position
 */
bool Chessboard::move_chess(const std::string pos1, const std::string pos2) {
    Position p1 = convert_position(pos1);
    Position p2 = convert_position(pos2);

    return move_chess(p1, p2);
}


/**
 * Questa funzione si occupa del controllo finale del movimento di una pedina. \n Infatti in questa funzione vengono fatti
 * tutti i tipi di controllo necessari: \n
 * - se le due posizioni passate sono due posizioni valide \n
 * - se il movimento coincide con un arrocco \n
 * - se la mossa e' effettivamente legale per la pedina scelta \n
 * - se c'e' un caso di inchiodamento \n
 * - viene gestito anche il caso speciale di en passant, che viene ultimato nel pawn.cpp \n
 * \n
 * In caso i controlli fossero rispettati, allora possiamo fare la mossa. \n
 * Teniamo la traccia del re, ovvero dove si trova. \n
 * Teniamo conto di quanti movimenti senza mangiata sono stati fatti, per via della regola delle 50 mosse della patta. \n
 *
 * @param p1: posizione iniziale della pedina
 * @param p2: posizione finale della pedina
 * @return Viene restituito un valore bool che ci indica se l'azione di movimento e' possibile
 */
bool Chessboard::move_chess(Position p1, Position p2) {
    if(!p1.is_valid() || !p2.is_valid()) return false;

    // ARROCCO
    if((tolower(get_cell(p1.row, p1.col)->get_char()) == 'r') && (p2.row == p1.row) && (p2.col == p1.col+2 || p2.col == p1.col-2)){
        if(king_castling(p1, p2)) {
            delete board[p2.row][p2.col];
            board[p2.row][p2.col] = board[p1.row][p1.col];
            board[p1.row][p1.col] = new Empty();
            if(board[p2.row][p2.col]->is_white)
                king_w = p2;
            else
                king_b = p2;
            only_moves_count++;
            return true;
        }
    }

    if (get_cell(p1.row, p1.col)->is_move_legal(this->board, p1, p2) && !is_pinned(p1, p2)) {
        get_cell(p1.row, p1.col)->is_first_move = false;
        if(board[p2.row][p2.col]->get_char() == ' ') only_moves_count++;
        else only_moves_count = 0;

        if (tolower(board[p1.row][p1.col]->get_char()) == 'p'   
            && abs(p2.row - p1.row) == abs(p2.col - p1.col) // controlla se il pedone si sposta in diagonale
            && board[p2.row][p2.col]->get_char() == ' ')
        {
            // cancella pedina mangiata in caso di en passant
            only_moves_count = 0;
            delete board[p1.row][p2.col];
            board[p1.row][p2.col] = new Empty();
        }

        delete board[p2.row][p2.col];
        board[p2.row][p2.col] = board[p1.row][p1.col];
        board[p1.row][p1.col] = new Empty();

        // elimina il vecchio possibile en passant (ed eventualmente salva il nuovo)
        if (tolower(board[p2.row][p2.col]->get_char()) == 'p' && abs(p2.row - p1.row) == 2) {
            if (en_passant != nullptr)
                en_passant->set_en_passant(false);
            
            en_passant = dynamic_cast<Pawn*>(board[p2.row][p2.col]);
            en_passant->set_en_passant(true);
        }
        else {
            if(en_passant != nullptr) {
                en_passant->set_en_passant(false);
                en_passant = nullptr;
            }
        }
        if(board[p2.row][p2.col]->get_char() == 'r')
            king_w = p2;
        else if (board[p2.row][p2.col]->get_char() == 'R')
            king_b = p2;
        return true;
    }
    return false;
}

/**
 * Questa funzione si occupa di trattare il movimento lato computer. \n
 * Innanzitutto andiamo a inserire in un vettore le posizioni di tutte le pedine rimaste in vita. \n
 * Andiamo a prendere in modo casuale una di queste pedine tramite la funzione random, andiamo a cercare sempre in modo
 * casuale una delle sue possibili mosse. \n
 * Andiamo a vedere se questa mossa scelta e' possibile con la funzione move_chess; continuiamo in questo
 * modo finche' non troviamo una posizione possibile di una pedina. \n Le pedine "non valide" e le loro mosse associate,
 * verranno cancellate da quelle possibili ad ogni turno ciclando.
 *
 * @param is_white: colore della pedina da muovere, true se bianca, false se nera
 * @return Andiamo a restituire la stringa, che contiene la prima possibile mossa trovata, formata dalle due posizioni
 */
std::string Chessboard::random_move(bool is_white) {
    std::vector<Position> possible_pawns = std::vector<Position>();
    
    for (int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            if(board[i][j]->get_char() != ' ' && board[i][j]->is_white == is_white)
                possible_pawns.push_back(Position{i, j});

    while (possible_pawns.size() != 0) {
        int rand_pawn = std::rand() % possible_pawns.size();
        Position p1 = possible_pawns.at(rand_pawn);
        
        std::vector<Position> final_pos = board[p1.row][p1.col]->possible_final_positions(board, p1);
        int rand_move;
        while (final_pos.size() != 0) {
            rand_move = std::rand() % final_pos.size();
            Position p2 = final_pos.at(rand_move);
            if (move_chess(p1, p2)) {
                std::string to_ret = p1.reverse_position() + " " + p2.reverse_position() + " " + board[p2.row][p2.col]->get_char();
                return to_ret;
            } else 
                final_pos.erase(final_pos.begin() + rand_move);
        } 
        possible_pawns.erase(possible_pawns.begin() + rand_pawn);
    }
    return "end_game";
}