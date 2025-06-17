#pragma once

#include "IThreads.h"

namespace threads
{

class Challenge_1 : public IThreads
{
  public:
  /**
   * @brief Constructor
   */
    Challenge_1() { run(); }
    
  /**
   * @brief Main function that runs the algorithm
   */
    void run() override;
   
};

} // threads