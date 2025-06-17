#include "include/Threads/Threads.h"
#include "include/Threads/Threads2.h"
#include "include/Threads/Threads3.h"
#include "include/Threads/Threads_datarace.h"
#include "include/Threads/Challenge_1.h"
#include "include/Threads/Challenge_2.h"
#include <iostream>
#include <memory>

int main() {
    std::cout << "Threads!" << std::endl;

    // std::unique_ptr<threads::Threads> myThreads = std::make_unique<threads::Threads>();
    // std::unique_ptr<threads::Threads2> myThreads2 = std::make_unique<threads::Threads2>();
    // std::unique_ptr<threads::Threads3> myThreads3 = std::make_unique<threads::Threads3>();
    // std::unique_ptr<threads::Threads_datarace> myThreads_datarace = std::make_unique<threads::Threads_datarace>();
    // std::unique_ptr<threads::Challenge_1> challenge_1 = std::make_unique<threads::Challenge_1>();
    std::unique_ptr<threads::Challenge_2> challenge_2 = std::make_unique<threads::Challenge_2>();

    return 0;
}