#pragma once

#include <cstdint>
#include <map>
#include <vector>
struct Board
{
    uint64_t WHITE_PAWN;
    uint64_t BLACK_PAWN;
    uint64_t WHITE_ROOK;
    uint64_t BLACK_ROOK;
    uint64_t WHITE_KNIGHT;
    uint64_t BLACK_KNIGHT;
    uint64_t WHITE_BISHOP;
    uint64_t BLACK_BISHOP;
    uint64_t WHITE_QUEEN;
    uint64_t BLACK_QUEEN;
    uint64_t WHITE_KING;
    uint64_t BLACK_KING;
    std::map<int, uint64_t> PieceCodeMap;

    Board();
    void printBoard();
    std::vector<std::vector<int>> storeBoard();
    std::vector<std::vector<int>> possibleMoves(int PieceCode, int row, int col, std::map<int, uint64_t> PieceCodeMap);
    uint64_t getWhiteCells(std::map<int, uint64_t> PieceCodeMap);
    uint64_t getBlackCells(std::map<int, uint64_t> PieceCodeMap);
    bool updateBoard(int Piececode, int init_row, int init_col, int end_row, int end_col);
    bool inCheckCondition(int TURN, std::map<int, uint64_t> PieceCodeMap);
    bool validateMove(int Piececode, int init_row, int init_col, int end_row, int end_col);
};
