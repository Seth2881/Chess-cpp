#include <iostream>
#include <bitset>
#include <utility>
#include <string>
#include <cmath>

using namespace std;

uint64_t FILE_A = 0x8080808080808080;
uint64_t FILE_H = 0x0101010101010101;
uint64_t FILE_AB = 0xC0C0C0C0C0C0C0C0;
uint64_t FILE_GH = 0x0303030303030303;

uint64_t NOT_FILE_A = 0x7F7F7F7F7F7F7F7F;
uint64_t NOT_FILE_H = 0xFEFEFEFEFEFEFEFE;
uint64_t NOT_FILE_AB = 0x3F3F3F3F3F3F3F3F;
uint64_t NOT_FILE_GH = 0xFCFCFCFCFCFCFCFC;

extern uint64_t FILE_A;
extern uint64_t FILE_H;
extern uint64_t FILE_AB;
extern uint64_t FILE_GH;
extern uint64_t NOT_FILE_A;
extern uint64_t NOT_FILE_H;
extern uint64_t NOT_FILE_AB;
extern uint64_t NOT_FILE_GH;


void displayBitboard(uint64_t bb) {
    for (int r = 7; r >= 0; r--) { // On commence par la ligne du haut (8)
        for (int c = 0; c < 8; c++) {
            int index = r * 8 + c;
            
            // On vérifie si le bit à cet index est à 1
            if ((bb >> index) & 1) {
                cout << "1 ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
}

short convertCoordToInt(pair<short, short> pieceCoord) {
    return pieceCoord.second * 8 + pieceCoord.first;
}

pair<short, short> convertIntToCoord(short index) {
    return { (short)(index % 8), (short)(index / 8) };
}

pair<short, short> getCoord (string chessCoord){
    return {(chessCoord[0] - 'a'), (chessCoord[1] - '0') - 1};
}

uint64_t getPiecePosBitboard (pair<short, short> position) {
    short piecePos = position.second*8 + position.first;

    uint64_t pieceBitboard = 1ULL;
    pieceBitboard = pieceBitboard << piecePos;

    return pieceBitboard;
}

uint64_t getRookBitboard(pair<short, short> position) {
    short columnMagicNumber = 1ULL << position.first;

    uint64_t rookBitboard = 0x0000000000000000;
    uint64_t column = columnMagicNumber * 0x0101010101010101;
    uint64_t line = 0xFFULL << (position.second * 8);
    uint64_t rookPosBitboard = getPiecePosBitboard(position);

    //adding columns and lines attacks
    rookBitboard = ((rookBitboard | column) | line) ^ rookPosBitboard;

    return rookBitboard;
}

uint64_t getBishopBitboard (pair<short, short> position) {
    uint64_t bishopPosBitboard = getPiecePosBitboard(position);
    uint64_t bishopBitboard = 0x0000000000000000;
    uint64_t mask = bishopPosBitboard;
    pair<short, short> tempPos = position;

    while (tempPos.first > 0 && tempPos.second > 0) {
        tempPos.first--;
        tempPos.second--;

        mask = mask >> 9;
        bishopBitboard = bishopBitboard | mask;
    }

    tempPos = position;
    mask = bishopPosBitboard;
    while (tempPos.first > 0 && tempPos.second < 7) {
        tempPos.first--;
        tempPos.second++;

        mask = mask << 7;
        bishopBitboard = bishopBitboard | mask;
    }

    tempPos = position;
    mask = bishopPosBitboard;
    while (tempPos.first < 7 && tempPos.second > 0) {
        tempPos.first++;
        tempPos.second--;

        mask = mask >> 7;
        bishopBitboard = bishopBitboard | mask;
    }

    tempPos = position;
    mask = bishopPosBitboard;
    while (tempPos.first < 7 && tempPos.second < 7) {
        tempPos.first++;
        tempPos.second++;

        mask = mask << 9;
        bishopBitboard = bishopBitboard | (mask);
    }

    return bishopBitboard;
}

uint64_t getQueenBitboard(pair<short, short> position) {
    return getRookBitboard(position) | getBishopBitboard(position);
}

uint64_t getKingBitboard(pair<short, short> position) {
    uint64_t kingPosBitboard = getPiecePosBitboard(position);
    uint64_t kingbitboard = 0x0000000000000000;
    uint64_t mask;

    kingbitboard = kingbitboard | (kingPosBitboard << 8);
    kingbitboard = kingbitboard | (kingPosBitboard >> 8);

    mask = kingPosBitboard & NOT_FILE_A;
    kingbitboard = kingbitboard | (mask << 1);
    kingbitboard = kingbitboard | (mask << 9);
    kingbitboard = kingbitboard | (mask >> 7);

    mask = kingPosBitboard & NOT_FILE_H;
    kingbitboard = kingbitboard | (mask >> 1);
    kingbitboard = kingbitboard | (mask >> 9);
    kingbitboard = kingbitboard | (mask << 7);

    return kingbitboard;
}

uint64_t getKnightbBitboard(pair<short, short> position) {
    uint64_t knightPosBitboard = getPiecePosBitboard(position);
    uint64_t knightbitboard = 0x0000000000000000;
    uint64_t mask;

    mask = knightPosBitboard & NOT_FILE_A;
    knightbitboard = knightbitboard | (mask << 17);
    knightbitboard = knightbitboard | (mask >> 15);

    mask = knightPosBitboard & NOT_FILE_H;
    knightbitboard = knightbitboard | (mask >> 17);
    knightbitboard = knightbitboard | (mask << 15);

    mask = knightPosBitboard & NOT_FILE_AB;
    knightbitboard = knightbitboard | (mask << 10);
    knightbitboard = knightbitboard | (mask >> 6);

    mask = knightPosBitboard & NOT_FILE_GH;
    knightbitboard = knightbitboard | (mask >> 10);
    knightbitboard = knightbitboard | (mask << 6);

    return knightbitboard;
}

uint64_t getWhitePawnBitboard(pair<short, short> position) {
    uint64_t pawnPosBitboard = getPiecePosBitboard(position);
    uint64_t pawnbitboard = 0x0000000000000000;
    uint64_t mask;

    mask = pawnPosBitboard & NOT_FILE_A;
    pawnbitboard = pawnbitboard | (mask << 9);

    mask = pawnPosBitboard & NOT_FILE_H;
    pawnbitboard = pawnbitboard | (mask << 7);

    return pawnbitboard;
}

uint64_t getBlackPawnBitboard(pair<short, short> position) {
    uint64_t pawnPosBitboard = getPiecePosBitboard(position);
    uint64_t pawnbitboard = 0x0000000000000000;
    uint64_t mask;

    mask = pawnPosBitboard & NOT_FILE_A;
    pawnbitboard = pawnbitboard | (mask >> 7);

    mask = pawnPosBitboard & NOT_FILE_H;
    pawnbitboard = pawnbitboard | (mask >> 9);

    return pawnbitboard;
}