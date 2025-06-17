#include "Threads/Threads2.h"
#include <iostream>
#include <thread>
#include <unistd.h>
#include <string>

namespace threads
{
using namespace std;


void worker2(std::string worker_name) {
    cout << "Thread: " << worker_name << " starts working."<< endl;

    std::this_thread::sleep_for(std::chrono::seconds(5));
    cout << "Thread: " << worker_name << " finsihed working."<< endl;
}


void Threads2::run() {
    /** Demo thread life cycle -> thread.join() & thread.joinable() */
    // cout << "Main Process ID: " << getpid() << endl;
    // cout << "Main thread ID: " << std::this_thread::get_id() << endl;

    auto time_counting{3};
    std::thread thread1(worker2, "new_thread");

    cout << "Main Thread started working ..." << endl;
    std::this_thread::sleep_for(std::chrono::seconds(time_counting));
    cout << "Main Thread finished working ..." << endl;

    if (thread1.joinable()) {
        cout << "thread1 is joinable check 1..." << endl;
    }

    thread1.join();

    if (!thread1.joinable()) {
        cout << "thread1 is not joinable anymore check 2..." << endl;
    }

    cout << "Both Threads are finished." << endl;

}

} // threads