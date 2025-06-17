#include "Threads/Threads3.h"
#include <iostream>
#include <thread>
#include <unistd.h>
#include <string>

namespace threads
{
using namespace std;


void worker3(std::string worker_name) {
    cout << "Thread: " << worker_name << " starts working."<< endl;
    while (true)
    {
        cout << "new_thread working..." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    cout << "Thread: " << worker_name << " finsihed working."<< endl;
}


void Threads3::run() {
    /** Demo detached thread -> thread.join() & thread.joinable() */
    // cout << "Main Process ID: " << getpid() << endl;
    // cout << "Main thread ID: " << std::this_thread::get_id() << endl;

    auto time_counting{3};
    std::thread thread1(worker3, "new_thread");
    thread1.detach();

    cout << "Main Thread started working ..." << endl;
    std::this_thread::sleep_for(std::chrono::seconds(time_counting));
    cout << "Main Thread finished working ..." << endl;

    // Detaching the thread, makes it not joinable, no need next line anymore
    // thread1.join();

    cout << "Both Threads are finished!!!" << endl;

}

} // threads