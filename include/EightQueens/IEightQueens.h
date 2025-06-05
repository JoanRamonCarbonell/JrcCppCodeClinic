#pragma once

namespace eight_queens
{

class IEightQueens
{
  public:
    virtual void run() = 0;
    virtual ~IEightQueens() = default;
};

} // eight_queens