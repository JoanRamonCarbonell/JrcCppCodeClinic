#pragma once

#include "IThreads.h"

namespace threads
{

class Threads : public IThreads
{
  public:
  /**
   * @brief Constructor
   */
    Threads() { run(); }
    
  /**
   * @brief Main function that runs the algorithm
   */
    void run() override;
   
};

} // threads