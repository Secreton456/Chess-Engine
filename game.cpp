#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <cstdint>
#include <bitset>
#include <bits/stdc++.h>
typedef uint64_t U64;

namespace py = pybind11;

struct Board
{
    // clang-format off
    U64 WHITE_PAWN   = 0b11111111ULL << 8;
    U64 BLACK_PAWN   = 0b11111111ULL << 48;
    U64 WHITE_ROOK   = 0b10000001ULL;
    U64 BLACK_ROOK   = 0b10000001ULL << 56;
    U64 WHITE_KNIGHT = 0b01000010ULL;
    U64 BLACK_KNIGHT = 0b01000010ULL << 56;
    U64 WHITE_BISHOP = 0b00100100ULL;
    U64 BLACK_BISHOP = 0b00100100ULL << 56;
    U64 WHITE_QUEEN  = 0b00001000ULL;
    U64 BLACK_QUEEN  = 0b00001000ULL << 56;
    U64 WHITE_KING   = 0b00010000ULL;
    U64 BLACK_KING   = 0b00010000ULL << 56;
    // clang-format on
    void printBoard()
    {
        for (int row = 7; row >= 0; row--)
        {
            std::cout << row + 1 << "  ";

            for (int column = 0; column < 8; column++)
            {
                int cell = row * 8 + column;
                U64 mask = 1ULL << cell;

                char piece = '.';

                if (WHITE_PAWN & mask)
                    piece = 'P';
                else if (BLACK_PAWN & mask)
                    piece = 'p';
                else if (WHITE_ROOK & mask)
                    piece = 'R';
                else if (BLACK_ROOK & mask)
                    piece = 'r';
                else if (WHITE_KNIGHT & mask)
                    piece = 'N';
                else if (BLACK_KNIGHT & mask)
                    piece = 'n';
                else if (WHITE_BISHOP & mask)
                    piece = 'B';
                else if (BLACK_BISHOP & mask)
                    piece = 'b';
                else if (WHITE_QUEEN & mask)
                    piece = 'Q';
                else if (BLACK_QUEEN & mask)
                    piece = 'q';
                else if (WHITE_KING & mask)
                    piece = 'K';
                else if (BLACK_KING & mask)
                    piece = 'k';

                std::cout << piece << " ";
            }

            std::cout << std::endl;
        }

        std::cout << "\n   a b c d e f g h\n";
    }
    std::vector<std::vector<int>> storeBoard()
    {
        std::vector<std::vector<int>> board(8, std::vector<int>(8));
        for (int row = 7; row >= 0; row--)
        {
            for (int column = 0; column <= 7; column++)
            {
                int cell = 8 * row + column;
                U64 mask = 1LL << cell;
                board[row][column] = 0;
                if (WHITE_PAWN & mask)
                    board[row][column] = 1;
                else if (BLACK_PAWN & mask)
                    board[row][column] = -1;
                else if (WHITE_ROOK & mask)
                    board[row][column] = 4;
                else if (BLACK_ROOK & mask)
                    board[row][column] = -4;
                else if (WHITE_KNIGHT & mask)
                    board[row][column] = 2;
                else if (BLACK_KNIGHT & mask)
                    board[row][column] = -2;
                else if (WHITE_BISHOP & mask)
                    board[row][column] = 3;
                else if (BLACK_BISHOP & mask)
                    board[row][column] = -3;
                else if (WHITE_QUEEN & mask)
                    board[row][column] = 5;
                else if (BLACK_QUEEN & mask)
                    board[row][column] = -5;
                else if (WHITE_KING & mask)
                    board[row][column] = 6;
                else if (BLACK_KING & mask)
                    board[row][column] = -6;
            }
        }
        return board;
    }
};

PYBIND11_MODULE(game, m)
{
    m.doc() = "The back-end for the chess game engine";
    py::class_<Board>(m, "Board")
        .def(py::init<>())
        .def("printBoard", &Board::printBoard)
        .def("storeBoard", &Board::storeBoard)
        .def_readwrite("WHITE_PAWN", &Board::WHITE_PAWN)
        .def_readwrite("BLACK_PAWN", &Board::BLACK_PAWN)
        .def_readwrite("WHITE_ROOK", &Board::WHITE_ROOK)
        .def_readwrite("BLACK_ROOK", &Board::BLACK_ROOK)
        .def_readwrite("WHITE_BISHOP", &Board::WHITE_BISHOP)
        .def_readwrite("BLACK_BISHOP", &Board::BLACK_BISHOP)
        .def_readwrite("WHITE_QUEEN", &Board::WHITE_QUEEN)
        .def_readwrite("BLACK_QUEEN", &Board::BLACK_QUEEN)
        .def_readwrite("WHITE_KNIGHT", &Board::WHITE_KNIGHT)
        .def_readwrite("BLACK_KNIGHT", &Board::BLACK_KNIGHT)
        .def_readwrite("WHITE_KING", &Board::WHITE_KING)
        .def_readwrite("BLACK_KING", &Board::BLACK_KING);
}