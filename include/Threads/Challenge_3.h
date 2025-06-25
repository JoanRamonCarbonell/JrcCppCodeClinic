#pragma once

#include "IThreads.h"
#include <mutex>

namespace threads
{

class Challenge_3 : public IThreads
{
  public:
  /**
   * @brief Constructor
   */
    Challenge_3() { run(); }
    
  /**
   * @brief Main function that runs the algorithm
   */
    void run() override;
};

} // threads