#pragma once

#include "IEightQueens.h"
#include <array>
#include <string>
#include <map>
#include <utility>
namespace eight_queens
{
constexpr auto MAX_POSITION{8};
constexpr auto QUEENS_NUM{8};
constexpr auto QUEEN{'Q'};
constexpr auto COLUMN_LIMIT{" | "};

const std::string BOARD_LIMIT{" +===============================+"};
const std::string BOARD_INTERLINE{" |-------------------------------|"};
const std::string SUCCESS_MSG{"The 8 QUEENS were successfully located!!!"}; 
const std::string FINISH_MSG{"All possible cobinations were tried."};
const std::string BEGIN_MSG{"Running : Eight Queens"};
const std::string END_MSG{"End : Eight Queens"};

class EightQueens : public IEightQueens
{
  public:
  /**
   * @brief Constructor
   */
    EightQueens() { run(); }
    
  /**
   * @brief Main function that runs the algorithm
   */
    void run() override;
    
  private:
    std::array<std::array<char, MAX_POSITION>, MAX_POSITION> m_chess_board;
    int m_located_queens{0};
    std::map<int, std::pair<int, int>> m_queens_position;

  /**
   * @brief Paints the chess board, to show where the queens were located
   */
    void paint_chess_board();

  /**
   * @brief checks if a queen is found in a given row
   * @param int& the row to check
   * @return true if a queen is found in this row
   */
    bool is_queen_in_row(int& row);

  /**
   * @brief checks if a queen is found in a given column
   * @param int& the column to check
   * @return true if a queen is found in this column
   */
    bool is_queen_in_col(int& col);

  /**
   * @brief checks if a queen is found any of the four diagonals,
   *        for a given position on the chess board
   * @param int& row of the given position
   * @param int& column of the given position
   * @return true if a queen is found in any of the diagonals
   */
    bool is_queen_in_diagonal(const int& row, const int& col);

};

} // eight_queens