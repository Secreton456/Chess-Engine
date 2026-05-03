#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <cstdint>
#include <bitset>
#include <bits/stdc++.h>
typedef uint64_t U64;

namespace py = pybind11;

struct Board
{
    /**
     * Initialise the Board to the default chess board using a 64 bit integer.
     */
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
        /**
         * Prints the board on terminal with row 0 at top and column 0 at the left.
         * White pieces are initialised at the top.
         * The position of a specific piece in a 64 bit integer format is given by:
         *          1ULL << ( 8*row + column )
         */
        for (int row = 0; row <= 7; row++)
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
        /**
         * @returns A 8x8 vector storing the current state of the board with each piece represented by
         *          a distinct integer
         * cell = 8 * row + col
         */
        std::vector<std::vector<int>> board(8, std::vector<int>(8));
        for (int row = 0; row <= 7; row++)
        {
            for (int column = 0; column <= 7; column++)
            {
                int cell = 8 * row + column;
                U64 mask = 1ULL << cell;
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
    std::vector<std::vector<int>> possibleMoves(int PieceCode, int row, int col)
    {
        /**
         * @returns An 8×8 boolean vector(resultingBoard) where each cell is true
         * if it represents a possible move, and false otherwise.
         *
         * Takes the PieceCode, row, column as an argument and uses the current board state to
         * evaluate all possible moves by that certain piece.
         *
         */
        std::vector<std::vector<int>> resultingBoard(8, std::vector<int>(8, 0));
        std::vector<std::pair<int, int>> possibleMoves = {};

        // Stores the Cells of it's colour and enemy's colour in a 64 bit integer respectively.
        U64 SELF_CELLS = (PieceCode > 0) ? this->getWhiteCells() : this->getBlackCells();
        U64 ENEMY_CELLS = (PieceCode > 0) ? this->getBlackCells() : this->getWhiteCells();
        // Update possibleMoves for a Pawn
        if (PieceCode == 1 || PieceCode == -1)
        {
            // Handling a case for moving 2 cells in case the pawn hasn't moved.
            int initial_row = (PieceCode > 0) ? 1 : 6;
            if (PieceCode > 0)
            {
                // Handling a white pawn.
                // Create a mask for the required piece cell.
                int cell = 8 * row + col;
                U64 mask = 1ULL << cell;
                // Check if an enemy cell is present in a diagonal cell.
                if (ENEMY_CELLS >> 7 & mask)
                    possibleMoves.push_back({1, -1});
                if (ENEMY_CELLS >> 9 & mask)
                    possibleMoves.push_back({1, 1});
                // Check if the cell ahead (one or two squares forward) is empty.
                if (!(((ENEMY_CELLS | SELF_CELLS) >> 8) & mask))
                {
                    possibleMoves.push_back({1, 0});
                    if (!(((ENEMY_CELLS | SELF_CELLS) >> 16) & mask) && row == initial_row)
                        possibleMoves.push_back({2, 0});
                }
            }
            else
            {
                // Handling a Black pawn similar to above.
                int cell = 8 * row + col;
                U64 mask = 1ULL << cell;
                if (ENEMY_CELLS << 7 & mask)
                    possibleMoves.push_back({-1, 1});
                if (ENEMY_CELLS << 9 & mask)
                    possibleMoves.push_back({-1, -1});
                if (!(((ENEMY_CELLS | SELF_CELLS) << 8) & mask))
                {
                    possibleMoves.push_back({-1, 0});
                    if (!(((ENEMY_CELLS | SELF_CELLS) << 16) & mask) && row == initial_row)
                        possibleMoves.push_back({-2, 0});
                }
            }
        }
        // Update possibleMoves for a knight.
        else if (PieceCode == 2 || PieceCode == -2)
        {
            possibleMoves = {{2, 1}, {1, 2}, {-2, 1}, {1, -2}, {2, -1}, {-1, 2}, {-2, -1}, {-1, -2}};
        }
        // Update possibleMoves for a bishop.
        else if (PieceCode == 3 || PieceCode == -3)
        {
            int cell = 8 * row + col;
            U64 mask = 1ULL << cell;
            for (int i = 1; i <= 7; i++)
            {
                if ((mask << (7 * i)) & ENEMY_CELLS)
                {
                    possibleMoves.push_back({i, -i});
                    break;
                }
                else if ((mask << (7 * i)) & SELF_CELLS)
                {
                    break;
                }
                else
                {
                    possibleMoves.push_back({i, -i});
                }
            }
            for (int i = 1; i <= 7; i++)
            {
                if ((mask << (9 * i)) & ENEMY_CELLS)
                {
                    possibleMoves.push_back({i, i});
                    break;
                }
                else if ((mask << (9 * i)) & SELF_CELLS)
                {
                    break;
                }
                else
                {
                    possibleMoves.push_back({i, i});
                }
            }
            for (int i = 1; i <= 7; i++)
            {
                if ((mask >> (9 * i)) & ENEMY_CELLS)
                {
                    possibleMoves.push_back({-i, -i});
                    break;
                }
                else if ((mask >> (9 * i)) & SELF_CELLS)
                {
                    break;
                }
                else
                {
                    possibleMoves.push_back({-i, -i});
                }
            }
            for (int i = 1; i <= 7; i++)
            {
                if ((mask >> (7 * i)) & ENEMY_CELLS)
                {
                    possibleMoves.push_back({-i, i});
                    break;
                }
                else if ((mask >> (7 * i)) & SELF_CELLS)
                {
                    break;
                }
                else
                {
                    possibleMoves.push_back({-i, i});
                }
            }
        }
        // Update possibleMoves for a rook.
        else if (PieceCode == 4 || PieceCode == -4)
        {
            int cell = 8 * row + col;
            U64 mask = 1ULL << cell;
            // Along Vertical direction
            for (int i = 1; i <= 7; i++)
            {
                if ((mask << (8 * i)) & ENEMY_CELLS)
                {
                    possibleMoves.push_back({i, 0});
                    break;
                }
                else if ((mask << (8 * i)) & SELF_CELLS)
                {
                    break;
                }
                else
                {
                    possibleMoves.push_back({i, 0});
                }
            }
            for (int i = 1; i <= 7; i++)
            {
                if ((mask >> (8 * i)) & ENEMY_CELLS)
                {
                    possibleMoves.push_back({-i, 0});
                    break;
                }
                else if ((mask >> (8 * i)) & SELF_CELLS)
                {
                    break;
                }
                else
                {
                    possibleMoves.push_back({-i, 0});
                }
            }
            // Along horizontal direction
            for (int i = 1; i <= 7; i++)
            {
                if ((mask << i) & ENEMY_CELLS)
                {
                    possibleMoves.push_back({0, i});
                    break;
                }
                else if ((mask << (8 * i)) & SELF_CELLS)
                {
                    break;
                }
                else
                {
                    possibleMoves.push_back({0, i});
                }
            }
            for (int i = 1; i <= 7; i++)
            {
                if ((mask >> i) & ENEMY_CELLS)
                {
                    possibleMoves.push_back({0, -i});
                    break;
                }
                else if ((mask >> i) & SELF_CELLS)
                {
                    break;
                }
                else
                {
                    possibleMoves.push_back({0, -i});
                }
            }
        }
        // Update possibleMoves for a Queen.
        else if (PieceCode == 5 || PieceCode == -5)
        {
            int cell = 8 * row + col;
            U64 mask = 1ULL << cell;
            // Along Vertical direction
            for (int i = 1; i <= 7; i++)
            {
                if ((mask << (8 * i)) & ENEMY_CELLS)
                {
                    possibleMoves.push_back({i, 0});
                    break;
                }
                else if ((mask << (8 * i)) & SELF_CELLS)
                {
                    break;
                }
                else
                {
                    possibleMoves.push_back({i, 0});
                }
            }
            for (int i = 1; i <= 7; i++)
            {
                if ((mask >> (8 * i)) & ENEMY_CELLS)
                {
                    possibleMoves.push_back({-i, 0});
                    break;
                }
                else if ((mask >> (8 * i)) & SELF_CELLS)
                {
                    break;
                }
                else
                {
                    possibleMoves.push_back({-i, 0});
                }
            }
            // Along horizontal direction
            for (int i = 1; i <= 7; i++)
            {
                if ((mask << i) & ENEMY_CELLS)
                {
                    possibleMoves.push_back({0, i});
                    break;
                }
                else if ((mask << (8 * i)) & SELF_CELLS)
                {
                    break;
                }
                else
                {
                    possibleMoves.push_back({0, i});
                }
            }
            for (int i = 1; i <= 7; i++)
            {
                if ((mask >> i) & ENEMY_CELLS)
                {
                    possibleMoves.push_back({0, -i});
                    break;
                }
                else if ((mask >> i) & SELF_CELLS)
                {
                    break;
                }
                else
                {
                    possibleMoves.push_back({0, -i});
                }
            }
            for (int i = 1; i <= 7; i++)
            {
                if ((mask << (7 * i)) & ENEMY_CELLS)
                {
                    possibleMoves.push_back({i, -i});
                    break;
                }
                else if ((mask << (7 * i)) & SELF_CELLS)
                {
                    break;
                }
                else
                {
                    possibleMoves.push_back({i, -i});
                }
            }
            for (int i = 1; i <= 7; i++)
            {
                if ((mask << (9 * i)) & ENEMY_CELLS)
                {
                    possibleMoves.push_back({i, i});
                    break;
                }
                else if ((mask << (9 * i)) & SELF_CELLS)
                {
                    break;
                }
                else
                {
                    possibleMoves.push_back({i, i});
                }
            }
            for (int i = 1; i <= 7; i++)
            {
                if ((mask >> (9 * i)) & ENEMY_CELLS)
                {
                    possibleMoves.push_back({-i, -i});
                    break;
                }
                else if ((mask >> (9 * i)) & SELF_CELLS)
                {
                    break;
                }
                else
                {
                    possibleMoves.push_back({-i, -i});
                }
            }
            for (int i = 1; i <= 7; i++)
            {
                if ((mask >> (7 * i)) & ENEMY_CELLS)
                {
                    possibleMoves.push_back({-i, i});
                    break;
                }
                else if ((mask >> (7 * i)) & SELF_CELLS)
                {
                    break;
                }
                else
                {
                    possibleMoves.push_back({-i, i});
                }
            }
        }
        // Update possibleMoves for a king.
        else if (PieceCode == 6 || PieceCode == -6)
        {
            possibleMoves = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
        }
        // check if each move lies withing the board and update resultingBoard.
        for (auto move : possibleMoves)
        {
            if (row + move.first <= 7 && row + move.first >= 0 && col + move.second <= 7 && col + move.second >= 0)
            {
                resultingBoard[row + move.first][col + move.second] = 1;
            }
        }
        // Remove any possible move that lands on a piece of the same color.
        for (int row = 0; row <= 7; row++)
        {
            for (int col = 0; col <= 7; col++)
            {
                if (resultingBoard[row][col])
                {
                    int cell = row * 8 + col;
                    U64 mask = 1ULL << cell;
                    if (mask & SELF_CELLS)
                        resultingBoard[row][col] = 0;
                }
            }
        }

        return resultingBoard;
    }
    U64 getWhiteCells()
    {
        U64 WHITE_CELLS = this->WHITE_BISHOP | this->WHITE_KING | this->WHITE_KNIGHT | this->WHITE_PAWN | this->WHITE_QUEEN | this->WHITE_ROOK;
        return WHITE_CELLS;
    }
    U64 getBlackCells()
    {
        U64 BLACK_CELLS = this->BLACK_BISHOP | this->BLACK_KING | this->BLACK_KNIGHT | this->BLACK_PAWN | this->BLACK_QUEEN | this->BLACK_ROOK;
        return BLACK_CELLS;
    }
};

PYBIND11_MODULE(board, m)
{
    m.doc() = "The back-end for the chess game engine";
    py::class_<Board>(m, "Board")
        .def(py::init<>())
        .def("printBoard", &Board::printBoard)
        .def("storeBoard", &Board::storeBoard)
        .def("possibleMoves", &Board::possibleMoves)
        .def("getWhiteCells", &Board::getWhiteCells)
        .def("getBlackCells", &Board::getBlackCells)
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