/*
    Autore: HAJJAJ BARISON
*/

#include "../include/rook.h"

/**
 * Questa funzione effettua i controlli per vedere se il movimento della torre da p1 a p2 e' possibile. \n
 * Il controllo e' stato fatto suddividendo il movimento tra quello orizzontale e quello verticale. \n
 * La torre andra' avanti fino alla posizione precedente a p2, controllando che non ci siano pedine di mezzo. \n
 * Ci fermiamo nella posizione precedente a p2, in quanto sappiamo gia' che p2 sara' sicuramente vuota o che non contiene
 * una pedina dello stesso colore della torre, per il controllo iniziale.
 *
 * @param board: stato attuale della scacchiera
 * @param p1: posizione attuale del cavallo
 * @param p2: posizione finale del cavallo
 * @return Valore bool che ci indica se la mossa e' possibile o meno
 */
bool Rook::is_move_legal(std::array<std::array<Chess*, 8>, 8>& board, const Position p1, const Position p2) const {

    if(board[p2.row][p2.col]->is_white != is_white || board[p2.row][p2.col]->get_char() == ' '){
        // LE VARIABILE i E' STATA AGGIUNTA PER "MODIFICARE MOMENTANEAMENTE" LA POSIZIONE DELLA TORRE, IN QUANTO
        // LA POSIZIONE PASSATA E' CONST E QUINDI NON MODIFICABILE

        // ANDAMENTO VERTICALE
        if(p2.col == p1.col){
            if(p2.row < p1.row){    // SE LA POSIZIONE FINALE SI TROVA SOPRA LA TORRE
                int i = p1.row;
                while(i-1 != p2.row){   // CICLA FINCHE' LA POSIZIONE SUCCESSIVA NON E' UGUALE ALLA POSIZIONE FINALE
                    if(board[i-1][p1.col]->get_char() == ' '){  // SE LA POSIZIONE SUCCESSIVA E' VUOTA OK
                        i--;
                    }
                    else return false;  // ALTRIMENTI LA C'E' UNA PEDINA TRA LA TORRE E LA POSIZIONE FINALE, DI CONSEGUENZA
                                        // BISOGNA REINSERIRE LA POSIZIONE FINALE
                }
                // USCITI DAL CICLO WHILE CI TROVEREMO PRIMA DELLA POSIZIONE FINALE SENZA AVER AVUTO PROBLEMI, QUINDI
                // RESTITUIAMO TRUE, IN QUANTO SONO SICURO CHE LA POSIZIONE FINALE NON E' UNA PEDINA BIANCA
                return true;
            }
            else{   // LA POSIZIONE FINALE SI TROVA SOTTO LA TORRE
                int i = p1.row;
                while(i+1 != p2.row){   // CICLA FINCHE' LA POSIZIONE SUCCESSIVA NON E' UGUALE ALLA POSIZIONE FINALE
                    if(board[i+1][p1.col]->get_char() == ' '){  // SE LA POSIZIONE SUCCESSIVA E' VUOTA OK
                        i++;
                    }
                    else return false;  // ALTRIMENTI LA C'E' UNA PEDINA TRA LA TORRE E LA POSIZIONE FINALE, DI CONSEGUENZA
                    // BISOGNA REINSERIRE LA POSIZIONE FINALE
                }
                // USCITI DAL CICLO WHILE CI TROVEREMO PRIMA DELLA POSIZIONE FINALE SENZA AVER AVUTO PROBLEMI, QUINDI
                // RESTITUIAMO TRUE, IN QUANTO SONO SICURO CHE LA POSIZIONE FINALE NON E' UNA PEDINA BIANCA
                return true;
            }
        }
        // ANDAMENTO ORIZZONTALE
        else if(p2.row == p1.row){
            if(p2.col < p1.col){    // SE LA POSIZIONE FINALE SI TROVA A SINISTRA LA TORRE
                int i = p1.col;
                while(i-1 != p2.col){   // CICLA FINCHE' LA POSIZIONE SUCCESSIVA NON E' UGUALE ALLA POSIZIONE FINALE
                    if(board[p1.row][i-1]->get_char() == ' '){  // SE LA POSIZIONE SUCCESSIVA E' VUOTA OK
                        i--;
                    }
                    else return false;  // ALTRIMENTI LA C'E' UNA PEDINA TRA LA TORRE E LA POSIZIONE FINALE, DI CONSEGUENZA
                                        // BISOGNA REINSERIRE LA POSIZIONE FINALE
                }
                // USCITI DAL CICLO WHILE CI TROVEREMO PRIMA DELLA POSIZIONE FINALE SENZA AVER AVUTO PROBLEMI, QUINDI
                // RESTITUIAMO TRUE, IN QUANTO SONO SICURO CHE LA POSIZIONE FINALE NON E' UNA PEDINA BIANCA
                return true;
            }
            else{   // LA POSIZIONE FINALE SI TROVA A DESTRA LA TORRE
                int i = p1.col;
                while(i+1 != p2.col){   // CICLA FINCHE' LA POSIZIONE SUCCESSIVA NON E' UGUALE ALLA POSIZIONE FINALE
                    if(board[p1.row][i+1]->get_char() == ' '){  // SE LA POSIZIONE SUCCESSIVA E' VUOTA OK
                        i++;
                    }
                    else return false;  // ALTRIMENTI LA C'E' UNA PEDINA TRA LA TORRE E LA POSIZIONE FINALE, DI CONSEGUENZA
                    // BISOGNA REINSERIRE LA POSIZIONE FINALE
                }
                // USCITI DAL CICLO WHILE CI TROVEREMO PRIMA DELLA POSIZIONE FINALE SENZA AVER AVUTO PROBLEMI, QUINDI
                // RESTITUIAMO TRUE, IN QUANTO SONO SICURO CHE LA POSIZIONE FINALE NON E' UNA PEDINA BIANCA
                return true;
            }
        }
        else return false;
    }

    return false;
}