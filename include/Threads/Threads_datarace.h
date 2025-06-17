#pragma once

#include "IThreads.h"

namespace threads
{

class Threads_datarace : public IThreads
{
  public:
  /**
   * @brief Constructor
   */
    Threads_datarace() { run(); }
    
  /**
   * @brief Main function that runs the algorithm
   */
    void run() override;
   
};

} // threads