#pragma once

#include "IThreads.h"

namespace threads
{

class Challenge_2 : public IThreads
{
  public:
  /**
   * @brief Constructor
   */
    Challenge_2() { run(); }
    
  /**
   * @brief Main function that runs the algorithm
   */
    void run() override;
   
};

} // threads