#pragma once

#include "IEightQueens.h"
#include <vector>
#include <string>

namespace eight_queens
{

class EightQueens : public IEightQueens
{
public:
    EightQueens() { run(); }
    void run() override;

private:

};
} // eight_queens