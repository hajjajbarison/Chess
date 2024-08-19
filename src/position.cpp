/*
    Autore: MARCO FACCO
*/

#include "../include/position.h"

/**
 * @brief 
 * Conversione da stringa con le cordinate delle posizioni a oggetto posizione
 * @param pos stringa con le coordinate delle posizioni
 * @return Position - posizione convertita - (-1, -1) se non valida
 */
Position convert_position(const std::string pos) {
    Position position = Position();
    if(pos.length() != 2) return Position(-1, -1);
    bool cond1 = tolower(pos.at(0)) >= 'a' && tolower(pos.at(0)) <= 'h' && tolower(pos.at(1)) >= '1' && tolower(pos.at(1)) <= '8';
    bool cond2 = tolower(pos.at(1)) >= 'a' && tolower(pos.at(1)) <= 'h' && tolower(pos.at(0)) >= '1' && tolower(pos.at(0)) <= '8';

    if(!(cond1 || cond2)) return Position(-1,-1);

    for(char c : pos) {
        switch(tolower(c)) {
            case '1':
            position.row = 7;
                break;
            case '2':
            position.row = 6;
                break;
            case '3':
            position.row = 5;
                break;
            case '4':
            position.row = 4;
                break;
            case '5':
            position.row = 3;
                break;
            case '6':
            position.row = 2;
                break;
            case '7':
            position.row = 1;
                break;
            case '8':
            position.row = 0;
                break;
            case 'a':
            position.col = 0;
                break;
            case 'b':
            position.col = 1;
                break;
            case 'c':
            position.col = 2;
                break;
            case 'd':
            position.col = 3;
                break;
            case 'e':
            position.col = 4;
                break;
            case 'f':
            position.col = 5;
                break;
            case 'g':
            position.col = 6;
                break;
            case 'h':
            position.col = 7;
                break;
            default:
                return Position(-1,-1);
        }
    }

    return position;
}

/**
 * @brief 
 * Conversione da oggetto posizione a stringa con le coordinate delle posizioni
 * @return std::string stringa con le coordinate delle posizioni
 */
std::string Position::reverse_position() {
    std::ostringstream oss;
    oss << (8 - row) << (char) ('a' + col);
    return oss.str();
}

/**
 * @brief 
 * operatore == 
 * @param p2 seconda posizione su cui fare la verifica di uguaglianza
 * @return true - le due posizioni sono equivalenti
 * @return false - le due posizioni non sono equivalenti
 */
bool Position::operator==(const Position& p2) const {
    return this->row == p2.row && this->col == p2.col;
}

/**
 * @brief 
 * operatore !=
 * @param p2 seconda posizione su cui fare la verifica di disuguaglianza
 * @return true - le due posizioni non sono equivalenti
 * @return false - le due posizioni sono equivalenti
 */
bool Position::operator!=(const Position& p2) const {
    return this->row != p2.row || this->col != p2.col;
}
