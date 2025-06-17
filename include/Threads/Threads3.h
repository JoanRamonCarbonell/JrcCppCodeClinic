#pragma once

#include "IThreads.h"

namespace threads
{

class Threads3 : public IThreads
{
  public:
  /**
   * @brief Constructor
   */
    Threads3() { run(); }
    
  /**
   * @brief Main function that runs the algorithm
   */
    void run() override;
   
};

} // threads