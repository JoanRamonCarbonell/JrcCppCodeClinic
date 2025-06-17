#pragma once

namespace threads
{

class IThreads
{
  public:
    virtual void run() = 0;
    virtual ~IThreads() = default;
};

} // threads