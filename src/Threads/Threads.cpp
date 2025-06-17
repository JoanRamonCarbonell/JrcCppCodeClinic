#include "Threads/Threads.h"
#include <iostream>
#include <thread>
#include <unistd.h>
#include <string>

namespace threads
{
using namespace std;

bool counting{true};

void worker(std::string worker_name) {
    unsigned int counter{0};

    while(counting){ counter++; }
    cout << "Worker: " << worker_name << ", counted: " << counter << endl;
}


void Threads::run() {

    /** My first threads */
    // cout << "Main Process ID: " << getpid() << endl;
    // cout << "Main thread ID: " << std::this_thread::get_id() << endl;

    auto time_counting{1};
    std::thread thread1(worker, "first");
    std::thread thread2(worker, "second");

    cout << "Thread1 and Thread2 are counting during " << time_counting << "seconds" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(time_counting));
    counting=false;
    thread1.join();
    thread2.join();

    // while(true) {
    //     std::this_thread::sleep_for(std::chrono::seconds(1));
    // }
    // run
}

} // threads