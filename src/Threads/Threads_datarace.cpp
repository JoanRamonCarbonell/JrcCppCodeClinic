#include "Threads/Threads_datarace.h"
#include <iostream>
#include <thread>
#include <unistd.h>
#include <string>
#include <mutex>
#include <atomic>

namespace threads
{
using namespace std;

unsigned int count{0};
std::atomic<unsigned int> atomic_count(0);
std::mutex my_lock;

void worker_datarace_1(std::string worker_name) {
    cout << "Worker 1: " << worker_name << " starts working."<< endl;
    for (unsigned int i = 0; i<100000000; i++) {
        // cout << "Picking lock: " << worker_name << endl;
        my_lock.lock();
        count++;
        my_lock.unlock();
        // cout << "Releasing lock: " << worker_name << endl;
    }
}

void worker_datarace_2(std::string worker_name) {
    cout << "worker 2: " << worker_name << " starts working."<< endl;
    for (unsigned int i = 0; i<100000000; i++) {
        std::lock_guard<std::mutex> my_lock_guard(my_lock);
        // cout << "Picking lock: " << worker_name << endl;
        count++;
        // cout << "Releasing lock: " << worker_name << endl;
    }
}

void worker_datarace_3(std::string worker_name) {
    cout << "worker 3: " << worker_name << " starts working."<< endl;
    for (unsigned int i = 0; i<100000000; i++) {
        // cout << "Picking lock: " << worker_name << endl;
        atomic_count++;
        // cout << "Releasing lock: " << worker_name << endl;
    }
}

void worker_datarace_4(std::string worker_name) {
    cout << "worker 4: " << worker_name << " starts working."<< endl;
    for (unsigned int i = 0; i<100000000; i++) {
        // cout << "Picking lock: " << worker_name << endl;
        atomic_count++;
        // cout << "Releasing lock: " << worker_name << endl;
    }
}

void worker_datarace_5(std::string worker_name) {
    cout << "worker 5: " << worker_name << " starts working."<< endl;
    for (unsigned int i = 0; i<100000000; i++) {
        // cout << "Picking lock: " << worker_name << endl;
        atomic_count++;
        // cout << "Releasing lock: " << worker_name << endl;
    }
}

/** 
 * Recomendación general:
 * Usa **std::lock_guard** (o std::unique_lock si necesitas más control) siempre que puedas.
 * Solo usa **std::mutex::lock()/unlock()** directamente cuando necesites una flexibilidad 
 * muy específica y estés seguro de manejarlo correctamente. 
 */
void Threads_datarace::run() {
    /** Demo data race and how to avoid it ->  */
    auto time_counting{3};
    /* std::mutex */
    // std::thread thread1(worker_datarace_1, "new_thread_1");
    // std::thread thread2(worker_datarace_1, "new_thread_2");

    /* std::lock_guard C++ 11 */
    // std::thread thread1(worker_datarace_2, "new_thread_1");
    // std::thread thread2(worker_datarace_2, "new_thread_2");

    /* std::atomic value C++ 11 */
    // std::thread thread1(worker_datarace_3, "new_thread_1");
    // std::thread thread2(worker_datarace_3, "new_thread_2");

    /* std::unique_lock C++ 11 */
    // std::thread thread1(worker_datarace_4, "new_thread_1");
    // std::thread thread2(worker_datarace_4, "new_thread_2");

    /* std::scoped_lock C++ 17 */
    std::thread thread1(worker_datarace_5, "new_thread_1");
    std::thread thread2(worker_datarace_5, "new_thread_2");

    thread2.join();
    thread1.join();

//    cout << "Both Threads are finished and counted to :" << count << endl;
    cout << "Both Threads are finished and counted to :" << atomic_count.load() << endl;

}

} // threads