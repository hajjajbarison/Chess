/*
    Autore: MARCO MASIERO
*/


#include "../include/chessboard.h"

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]) {
    Chessboard board = Chessboard();
    bool move_player = board.get_color_player();
    string p1, p2;
    string draw_move = "";
    char promotion_char = 0;


    ofstream log;
    

    if (argc == 2) {
        string arg1(argv[1]);
        if (arg1 == "pc") { // PARTITA GIOCATORE VS COMPUTER
            log.open("../logpc.txt"); // APERTURA E CHIUSURA PER LA PULIZIA DEL FILE DI LOG DELLA PARTITA PRECEDENTE
            log.close();

            // draw variabile di flag per capire se la partita finisce in parita'.
            bool draw = false;
            while(!(draw = board.draw("../logpc.txt", draw_move))) {                
                if (move_player) {

                    cout << "\nWrite move >>> ";
                    cin >> p1; // b2 oppure 2b
                    cin >> p2; // c2 oppure 2c
                    
                    // move flag per capire se la mossa e' andata a buon fine
                    bool move = false;
                    Position pos1 = convert_position(p1);
                    Position pos2 = convert_position(p2);

                    if (pos1.is_valid() && pos2.is_valid()) {
                        if (board.get_cell(pos1.row, pos1.col)->is_white == board.get_color_player()) {
                            // Provo a fare la mossa, se e' valida il metodo move_chess va a buon fine
                            move = board.move_chess(p1, p2);
                            // Controllo se ci sono pedoni nella posizione di promozione
                            promotion_char = board.check_for_promotion(true);
                            cout << "------------------" << endl;
                        }

                        if(!move) cout << "Mossa non valida.\nInserire nuova posizione \n\n\n";
                        else {
                            // La mossa e' andata a buon fine e inserisco nel log tutti i dati necessari
                            log.open("../logpc.txt", std::ios_base::app);
                            log << p1 << " " << p2 << " " << board.get_cell(pos2.row, pos2.col)->get_char();
                            draw_move = p1 + " " + p2 + " " + board.get_cell(pos2.row, pos2.col)->get_char();
                            if(promotion_char != 0) log << " " << promotion_char;
                            log << "\n";
                            log.close();
                            move_player = !move_player;
                        }
                    }
                    // Controllo per stampa scacchiera
                    else if (tolower(p1.at(0)) == 'x' && tolower(p1.at(1)) == 'x' && tolower(p2.at(0)) == 'x' && tolower(p2.at(1)) == 'x')
                        cout << board.print_board();

                    // Controllo per richiesta di parita'
                    else if (tolower(p1.at(0)) == 'p' && tolower(p1.at(1)) == 'p' && tolower(p2.at(0)) == 'p' && tolower(p2.at(1)) == 'p') {
                            if (rand() % 2) {
                                cout << "Patta accettata. \n";
                                break;
                            }
                            else
                                cout << "Patta non accettata, continuo partita. \n";
                        }
                    else
                        cout << "Posizione inserita non valida! \nInserire nuova posizione. \n";

                } else {
                    // MUOVE IL COMPUTER 

                    // random_move gestisce tutte le mosse possibili e ne restituisce una casule
                    // La mossa scelta viene memorizzata in pos
                    string pos = board.random_move(!board.get_color_player());
                    promotion_char = board.check_for_promotion(true);
                    sleep(1);

                    // se random_move restituisce "end_game" significa che nessuna mossa e' possibile, quindi il computer perde
                    if (pos == "end_game") { // vedova nera muore
                        cout << "Scacco matto! Vince il giocatore!\n";
                        break;
                    }
                    
                    // Se faccio la mossa stampo nel log
                    log.open("../logpc.txt", std::ios_base::app);
                    log << pos;
                    draw_move = pos;
                    if(promotion_char != 0) log << " " << promotion_char;
                    log << "\n";
                    log.close();

                    // Controllo se il giocatore ha subito uno scacco matto dal computer
                    if (board.check_mate(board.get_color_player())) {
                        cout << "Scacco matto! Vince il computer!\n";
                        break;
                    }
                    move_player = !move_player;
                }
            }

            // con la flag draw controllo se la partita finisce per patta
            if(draw) cout << "Si e' verificata una patta!" << endl;
            cout << "Partita finita!";
        }
        else if (arg1 == "cc") { 
            // PARTITA COMPUTER VS COMPUTER 
             
            log.open("../logcc.txt"); // APERTURA E CHIUSURA PER LA PULIZIA DEL FILE DI LOG DELLA PARTITA PRECEDENTE
            log.close(); 

            // count_moves tiene il conto delle mosse eseguite, con un massimo di 100
            int count_moves = 0;
            bool white_moves = true;
            string pos = "";

            bool draw = false;
            while(!(draw = board.draw("../logcc.txt", draw_move)) && count_moves < 100) {

                pos = board.random_move(white_moves);
                promotion_char = board.check_for_promotion(false);

                if(pos != "end_game") { // muore thanos
                    log.open("../logcc.txt", std::ios_base::app);
                    log << pos;
                    draw_move = pos;
                    if(promotion_char != 0) log << " " << promotion_char;
                    log << std::endl;
                    log.close();
                }
                else {
                    cout << "Partita finita!";
                    break;
                }
                
                count_moves++;
                white_moves = !white_moves;
            }
            if(draw) cout << "Si e' verificata una patta! Partita finita." << endl;

        }
    }

    // se non vengono inseriti i parametri in riga di comando viene lanciato un errore
    else throw runtime_error("Please insert \"pc\" or \"cc\" as arguments.");
}
