#include "EightQueens/EightQueens.h"
#include <iostream>

namespace eight_queens
{
using namespace std;

void EightQueens::run() {

    cout << "Running : Eight Queens" << endl;

    // Locate 1st queen (hardcoded in v1)
    auto locate_queen{[&](int i, int j){
        m_chess_board[i][j] = QUEEN;
        m_queens_position.insert({m_located_queens, {i, j}});
        cout << "### Queen located at : (" << i << "," << j << ") ###" << endl;
        m_located_queens++;
    }};

    locate_queen(3,5);
    while (m_located_queens < QUEENS_NUM) {
        // locate next queen
        for (auto i=0; i<POS_NUMBER ; i++) {
            if (!is_queen_in_row(i)) {
                for (auto j=0; j<POS_NUMBER ; j++) {
                    if (!is_queen_in_col(j)) {
                        if (!is_queen_in_diagonal(i,j)) {
                            locate_queen(i,j);
                            break;
                        }
                    }
                }
            }
        }
    }

    // Paint chess board
    paint_chess_board();
}

bool EightQueens::is_queen_in_row(int& row) {
    for (const auto& [key, pair] : m_queens_position) {
        if (row == pair.first) { 
            return true;
        }
    }
    return false;
}

bool EightQueens::is_queen_in_col(int& col) {
    for (const auto& [key, pair] : m_queens_position) {
        if (col == pair.second) { 
            return true;
        }
    }
    return false;
}

bool EightQueens::is_queen_in_diagonal(int& i, int& j) {
    return false;
}

void EightQueens::paint_chess_board() {

    std::string line;

    cout << "*** Chess board: ***" << endl;
    cout << BOARD_LIMIT << endl;
    int interline_counter{0};

    for (const auto& row : m_chess_board) {
        line = "";
        line += COLUMN_LIMIT;
        for (const auto& col : row) {
            line += (col == '\0' ? ' ' : col );
            line += COLUMN_LIMIT;
        }
        cout << line << endl;
        interline_counter++;
        if (interline_counter < POS_NUMBER) { 
            cout << BOARD_INTERLINE << endl;
        }
    }
    cout << BOARD_LIMIT << endl;

    cout << "End : Eight Queens" << endl;
}


} // eight_queens