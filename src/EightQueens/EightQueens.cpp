#include "EightQueens/EightQueens.h"
#include <iostream>
#include <cstdlib>

namespace eight_queens
{
using namespace std;

void EightQueens::run() {

    cout << BEGIN_MSG << endl;
    int successful_combinations{0};
    bool all_combinations_tried{false};

    auto locate_queen{[&](int i, int j){
        m_chess_board[i][j] = QUEEN;
        m_queens_position.insert({m_located_queens, {i, j}});
        m_located_queens++;
    }};
    
    auto first_queen_i{0};
    auto first_queen_j{0};
    while (!all_combinations_tried) {
        cout << "___________________________________________" << endl;
        cout << "+++ Starting with first queen at (" << first_queen_i << "," << first_queen_j << ") +++" << endl;
        // Locate 1st queen in current combination
        locate_queen(first_queen_i, first_queen_j);
        // find where to locate next queen
        for (auto i=0; i<MAX_POSITION ; i++) {
            if (!is_queen_in_row(i)) {
                for (auto j=0; j<MAX_POSITION ; j++) {
                    if (!is_queen_in_col(j)) {
                        if (!is_queen_in_diagonal(i,j)) {
                            locate_queen(i,j);
                            break;
                        }
                    }
                }
            }
        }
        
        if (m_located_queens == QUEENS_NUM) {
            // when 8 queens are located, we have a successful solution
            paint_chess_board();
            cout << SUCCESS_MSG << endl;
            successful_combinations++;
        } else {
            // the combination is not valid
            cout << "Starting from (" 
                 << first_queen_i << "," 
                 << first_queen_j << ")" 
                 << " only " << m_located_queens 
                 << " Queens were located." << endl;
            
            // reset and try again
            m_located_queens = 0;
            for (auto& row : m_chess_board) {
                row.fill('\0');
            }
            m_queens_position.clear();
        }

        // each combination, starts from each position in the chess board
        if (first_queen_i < MAX_POSITION-1) {
            first_queen_i++;
        } else {
            first_queen_i = 0;
            first_queen_j++;
            if (first_queen_j>=MAX_POSITION) {
                all_combinations_tried=true;
                cout << "====================================" << endl;
                cout << FINISH_MSG << endl;
                cout << successful_combinations << " successful combinations found!!!" << endl;
                cout << "====================================" << endl;
            }
        }
    }
    cout << END_MSG << endl;

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

bool EightQueens::is_queen_in_diagonal(const int& i, const int& j) {

    pair<int, int> diag_increment{i,j};
    bool limit_reached{false};

    auto is_queen_found{[this](pair<int, int> diag_increment){
        for (const auto& [key, queen_position] : m_queens_position) {
            if ((queen_position.first == diag_increment.first) &&
                (queen_position.second == diag_increment.second)) {
                // queen found diagonally
                return true;
            }
        }
        return false;
    }};

    // diagonal down-rigth
    while (!limit_reached) {
        diag_increment.first++;
        diag_increment.second++;
        if ((diag_increment.first < MAX_POSITION) && 
            (diag_increment.second < MAX_POSITION)) {
            if (is_queen_found(diag_increment)) { return true; }
        } else {
            // limit reached down-right
            limit_reached=true;
        }
    }

    // diagonal up-left
    limit_reached=false;
    diag_increment={i,j};

    while (!limit_reached) {
        diag_increment.first--;
        diag_increment.second--;
        if ((diag_increment.first >= 0) && 
            (diag_increment.second >= 0)) {
            if (is_queen_found(diag_increment)) { return true; }
        } else {
            // limit reached up-left
            limit_reached=true;
        }
    }

    // diagonal up-right
    limit_reached=false;
    diag_increment={i,j};

    while (!limit_reached) {
        diag_increment.first++;
        diag_increment.second--;
        if ((diag_increment.first < MAX_POSITION) && 
            (diag_increment.second >= 0)) {
            if (is_queen_found(diag_increment)) { return true; }
        } else {
            // limit reached up-right
            limit_reached=true;
        }
    }

    // diagonal down-left
    limit_reached=false;
    diag_increment={i,j};

    while (!limit_reached) {
        diag_increment.first--;
        diag_increment.second++;
        if ((diag_increment.first >= 0) && 
            (diag_increment.second < MAX_POSITION)) {
            if (is_queen_found(diag_increment)) { return true; }
        } else {
            // limit reached down-left
            limit_reached=true;
        }
    }

    return false;
}

void EightQueens::paint_chess_board() {

    std::string line;

    cout << CHESS_BOARD_TITLE << endl;
    cout << BOARD_LIMIT << endl;
    int interline_counter{0};

    // paint a chess board
    for (const auto& row : m_chess_board) {
        line = "";
        line += COLUMN_LIMIT;
        for (const auto& col : row) {
            // if a queen is found, paint it 
            // paint a space otherwise
            line += (col == '\0' ? ' ' : col );
            line += COLUMN_LIMIT;
        }
        cout << line << endl;

        interline_counter++;
        if (interline_counter < MAX_POSITION) { 
            cout << BOARD_INTERLINE << endl;
        }
    }
    cout << BOARD_LIMIT << endl;
}

} // eight_queens