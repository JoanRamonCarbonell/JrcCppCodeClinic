#pragma once

#include "IThreads.h"

namespace threads
{

class Threads2 : public IThreads
{
  public:
  /**
   * @brief Constructor
   */
    Threads2() { run(); }
    
  /**
   * @brief Main function that runs the algorithm
   */
    void run() override;
   
};

} // threads