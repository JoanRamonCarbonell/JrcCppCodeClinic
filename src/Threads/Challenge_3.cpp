/**
 * Challenge: Multiply two matrices
 */
#include "Threads/Challenge_3.h"
#include <thread>
#include <cstring>
#include <curl/curl.h> // curl support https://curl.haxx.se/
#include <cmath>
#include <iostream>
#include <mutex>
#include <future>
#include <boost/asio.hpp>
#include <future>
#include <numeric>

namespace threads
{

using namespace std;

std::mutex mtx;
/* declarations for download_image helper function */
size_t download_image(int image_num);
size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp);

/* sequential implementation of image downloader */
size_t sequential_image_downloader(int num_images) {
	size_t total_bytes = 0;
	for (int i=1; i<=num_images; i++) {
		total_bytes += download_image(i);
	}
	return total_bytes;
}

void worker_v1(int i, size_t& total_bytes) {
    size_t bytes{download_image(i)};
    {
        std::lock_guard<std::mutex> m_lock(mtx);
        total_bytes += bytes;
    }
} 

size_t worker_v2(int i) {
//    std::lock_guard<std::mutex> m_lock(mtx);

    return download_image(i);
} 

size_t thread_pool_version(int num_images)  {
    // It took almost the same.. why? ask jarvis...
    size_t total_bytes{0};

    boost::asio::thread_pool pool(std::thread::hardware_concurrency());
    cout << "Threadpool version." << endl;

    for (int image_index = 1; image_index <= num_images; image_index++) {
        boost::asio::post(pool, std::bind(worker_v1, image_index, std::ref(total_bytes)));
    }
    pool.join();

    return total_bytes;
}

size_t threads_version_1(int num_images)  {
    std::vector<std::thread> workers;
    size_t total_bytes{0};
    cout << "Just threads version." << endl;
    for (int worker_index = 1; worker_index <= num_images; worker_index++) {
        workers.emplace_back(worker_v1, worker_index, std::ref(total_bytes));
    }

    for (auto& working_core : workers) {
        working_core.join();
    }
    return total_bytes;
}

size_t async_version(int num_images) {
    size_t total_bytes{0};
    std::vector<std::future<size_t>> results;
    auto cores_max{std::thread::hardware_concurrency()};
    cout << "Async version." << endl;

    for (auto image_id = 1; image_id <= num_images; image_id++) {
    // for (auto core = 0; core < cores_max-1; core++) {
        results.emplace_back(std::async(std::launch::async, worker_v2, image_id));
    }
    total_bytes = std::accumulate(results.begin(), results.end(), 0, [](size_t total, std::future<size_t>& value){return total + value.get();});

    return total_bytes;
}

/* parallel implementation of image downloader */
size_t parallel_image_downloader(int num_images) {
	size_t total_bytes = 0;

    /***********************
     * YOUR CODE GOES HERE *
     ***********************/
    // I can use threads
    // total_bytes = threads_version_1(num_images);
    
    // I can use a thread pool
    total_bytes = thread_pool_version(num_images);
    
    // I can use async, since I have something to return in each concurrent iteration
    // total_bytes = async_version(num_images);
	return total_bytes;
}

/* helper function to download a single image and return size in bytes */
size_t download_image(int image_num) { 
	char url[] = "http://699340.youcanlearnit.net/imageXXX.jpg";
	sprintf(url, "http://699340.youcanlearnit.net/image%03d.jpg", ((image_num % 50) + 1));

    CURLcode res;
    curl_off_t num_bytes = 0;
    CURL *curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        res = curl_easy_getinfo(curl, CURLINFO_SIZE_DOWNLOAD_T, &num_bytes);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_getinfo() failed: %s\n", curl_easy_strerror(res));
        }
        curl_easy_cleanup(curl);
    }
    // cout << "Image downloaded: " << image_num << "| [" << num_bytes << " bytes]" << endl;
    return num_bytes;
}

/* support function for the download_image helper function */
size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    return size * nmemb;
}

void Challenge_3::run () {
    cout << "Challenge 3" << endl;
    const int NUM_EVAL_RUNS = 3;
	const int NUM_IMAGES = 20;

	printf("Evaluating Sequential Implementation...\n");
	std::chrono::duration<double> sequential_time(0);
    cout << "First download" << endl;
    size_t sequential_result = sequential_image_downloader(NUM_IMAGES); // "warm up"
    for (int i=0; i<NUM_EVAL_RUNS; i++) {
        auto startTime = std::chrono::high_resolution_clock::now();
        cout << "Download: " << i << endl;
        sequential_image_downloader(NUM_IMAGES);
        sequential_time += std::chrono::high_resolution_clock::now() - startTime;
    }
    sequential_time /= NUM_EVAL_RUNS;

    printf("Evaluating Parallel Implementation...\n");
	std::chrono::duration<double> parallel_time(0);
    cout << "First download" << endl;
    size_t parallel_result = parallel_image_downloader(NUM_IMAGES); // "warm up"
    for (int i=0; i<NUM_EVAL_RUNS; i++) {
        auto startTime = std::chrono::high_resolution_clock::now();
        cout << "Download: " << i << endl;
        parallel_image_downloader(NUM_IMAGES);
        parallel_time += std::chrono::high_resolution_clock::now() - startTime;
    }
    parallel_time /= NUM_EVAL_RUNS;
    
    // display sequential and parallel results for comparison
    if (sequential_result != parallel_result) {
        printf("ERROR: Result mismatch!\n  Sequential Result = %zd\n  Parallel Result = %zd\n", sequential_result, parallel_result);
    }
    printf("Average Sequential Time: %.2f ms\n", sequential_time.count()*1000);
    printf("  Average Parallel Time: %.2f ms\n", parallel_time.count()*1000);
    printf("Speedup: %.2f\n", sequential_time/parallel_time);
    printf("Efficiency %.2f%%\n", 100*(sequential_time/parallel_time)/std::thread::hardware_concurrency());
}
}  // namespace threads