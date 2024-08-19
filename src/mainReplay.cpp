/*
    Autore: HAJJAJ BARISON
*/

#include <iostream>
#include <fstream>
#include <unistd.h>
#include "../include/chessboard.h"

using namespace std;

/**
 * Questo e' il main associato al replay. \n
 * Si occupa di gestire il replay in base al carattere indicato in posizione argv[1]. \n
 * Se 'v': viene stampato a video il replay del file di log indicato su riga di comando. \n
 * Se 'f': scrive su file il replay del file di log indicato su riga di comando.
 *
 * @param argc: contiene il numero dei parametri presenti sulla riga di comando
 * @param argv: array di puntatori a char che contiene gli elementi inseriti da riga di comando
 */
int main(int argc, char *argv[]) {
    Chessboard board = Chessboard();
    string line, p1, p2;

    ifstream log;
    ofstream out;

    log.open(argv[2]);
    out.open(argv[3]);

    if(argc > 2) {
        if(log.is_open()) {
            while(getline(log, line)) {
                if(*argv[1] == 'v') cout << board.print_board() << "------------------" << endl;
                if(*argv[1] == 'f') {
                    out << board.print_board();
                    out << "\n------------------\n\n";
                }

                p1 = line.substr(0,2);
                p2 = line.substr(3,2);
                char prom_char;
                if(line.size() > 8) prom_char = line.at(8);
                
                board.move_chess(p1,p2);
                if(prom_char != 0) {
                    board.replay_promotion(convert_position(p2), prom_char);
                    prom_char = 0;
                }

                if(*argv[1] == 'v') sleep(1);
            }
            if(*argv[1] == 'v') cout << board.print_board();
            if(*argv[1] == 'f') out << board.print_board();
        }
        else throw runtime_error("Log file not found.");


        log.close();
        out.close();
    }
    else throw runtime_error("Insert log file name.");
}