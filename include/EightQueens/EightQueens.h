#pragma once

#include "IEightQueens.h"
#include <array>
#include <string>
#include <map>
#include <utility>
namespace eight_queens
{
constexpr auto POS_NUMBER{8};
constexpr auto QUEENS_NUM{8};
constexpr auto QUEEN{'Q'};
constexpr auto COLUMN_LIMIT{" | "};
const std::string BOARD_LIMIT{" +===============================+"};
const std::string BOARD_INTERLINE{" |-------------------------------|"};



class EightQueens : public IEightQueens
{
public:
    EightQueens() { run(); }
    void run() override;
    void paint_chess_board();
    bool is_queen_in_row(int& row);
    bool is_queen_in_col(int& col);
    bool is_queen_in_diagonal(const int& row, const int& col);

private:
    std::array<std::array<char, POS_NUMBER>, POS_NUMBER> m_chess_board;
    int m_located_queens{0};
    std::map<int, std::pair<int, int>> m_queens_position;
};
} // eight_queens