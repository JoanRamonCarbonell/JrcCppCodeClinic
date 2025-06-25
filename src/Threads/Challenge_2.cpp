/**
 * Challenge: Multiply two matrices
 */
#include "Threads/Challenge_2.h"
#include <thread>
#include <cmath>
#include <iostream>
#include <mutex>
#include <future>

namespace threads
{

using namespace std;

auto cores_num{0};
void merge(int * array, unsigned int left, unsigned int mid, unsigned int right);

void print_array(int * array, int n)  {
    cout << "===========" << endl;
    for (int i=0; i < n; i++) {
        cout << " |"  << array[i] << endl;
    }
    cout << "===========" << endl;
}

/* sequential implementation of merge sort */
void sequential_merge_sort(int * array, unsigned int left, unsigned int right) {
	if (left < right) {
		unsigned int mid = (left + right) / 2; // find the middle point
		sequential_merge_sort(array, left, mid); // sort the left half
		sequential_merge_sort(array, mid+1, right); // sort the right half
		merge(array, left, mid, right); // merge the two sorted halves
	}					 
}

/* parallel implementation of merge sort */
void parallel_merge_sort(int * array, unsigned int left, unsigned int right, int depth = 0) {
	/***********************
	 * YOUR CODE GOES HERE *
	 ***********************/
    // find middle point
    // cout << "Depth : " << depth << endl;
    
    if (left < right) {
        if (depth > cores_num) {
            // base case
            // cout << "Merge executed!" << endl;
            sequential_merge_sort(array, left, right);
        } else {
            unsigned int mid = (left + right) / 2;
            // divide & conquer
            depth++;
            std::thread right_thread = std::thread(parallel_merge_sort, array, mid+1, right, depth);
            parallel_merge_sort(array, left, mid, depth);
            right_thread.join();
            merge(array, left, mid, right);
        }
    }
}

/* helper function to merge two sorted subarrays
   array[l..m] and array[m+1..r] into array */
void merge(int * array, unsigned int left, unsigned int mid, unsigned int right) {
	unsigned int num_left = mid - left + 1; // number of elements in left subarray
	unsigned int num_right = right - mid; // number of elements in right subarray
	
	// copy data into temporary left and right subarrays to be merged
	int array_left[num_left], array_right[num_right];
	std::copy(&array[left], &array[mid + 1], array_left);
	std::copy(&array[mid + 1], &array[right + 1], array_right);
	
	// initialize indices for array_left, array_right, and input subarrays
	unsigned int index_left = 0;    // index to get elements from array_left
	unsigned int index_right = 0;    // index to get elements from array_right
	unsigned int index_insert = left; // index to insert elements into input array
	
	// merge temporary subarrays into original input array
	while ((index_left < num_left) || (index_right < num_right)) {
		if ((index_left < num_left) && (index_right < num_right)) {
			if (array_left[index_left] <= array_right[index_right]) {
				array[index_insert] = array_left[index_left];
				index_left++;
			}
			else {
				array[index_insert] = array_right[index_right];
				index_right++;
			}
		}
		// copy any remain elements of array_left into array
		else if (index_left < num_left){
			array[index_insert] = array_left[index_left];
            index_left += 1;
		}
		// copy any remain elements of array_right into array
		else if (index_right < num_right) {
			array[index_insert] = array_right[index_right];
            index_right += 1;
		}
		index_insert++;
	}
}

void Challenge_2::run () {
    cout << "Challenge 2" << endl;
  	const int NUM_EVAL_RUNS = 100;
	const int N = 1000000; // number of elements to sort
    cores_num = std::thread::hardware_concurrency();
    cout << "Cores available : " << cores_num << endl;
	
	int original_array[N], sequential_result[N], parallel_result[N];
	for (int i=0; i<N; i++) {
		original_array[i] = rand();
	}

    cout << "Evaluating Sequential Implementation..." << endl;
	std::chrono::duration<double> sequential_time(0);

    std::fill(std::begin(sequential_result), std::end(sequential_result), 0);
    std::copy(&original_array[0], &original_array[N], sequential_result);
    sequential_merge_sort(sequential_result, 0, N-1); // "warm up"	

    for (int i=0; i<NUM_EVAL_RUNS; i++) {
		std::copy(&original_array[0], &original_array[N], sequential_result); // reset result array
        auto start_time = std::chrono::high_resolution_clock::now();
        sequential_merge_sort(sequential_result, 0, N-1);
        sequential_time += std::chrono::high_resolution_clock::now() - start_time;
    }

    sequential_time /= NUM_EVAL_RUNS;
	
    cout << "Evaluating Parallel Implementation..." << endl;
	std::chrono::duration<double> parallel_time(0);
    std::copy(&original_array[0], &original_array[N], parallel_result);

    parallel_merge_sort(parallel_result, 0, N-1); // "warm up"
    for (int i=0; i<NUM_EVAL_RUNS; i++) {
		std::copy(&original_array[0], &original_array[N], parallel_result); // reset result array
        auto start_time = std::chrono::high_resolution_clock::now();
        parallel_merge_sort(parallel_result, 0, N-1);
        parallel_time += std::chrono::high_resolution_clock::now() - start_time;
    }
    parallel_time /= NUM_EVAL_RUNS;
	
    // verify sequential and parallel results are same
    for (int i=0; i<N; i++) {
		if (sequential_result[i] != parallel_result[i]) {
            cout << "ERROR: Result mismatch at index " << i << "!" << endl;
		}
	}
    cout << "Average Sequential Time: " << sequential_time.count()*1000 << endl;
    cout << "  Average Parallel Time: " << parallel_time.count()*1000 << endl;
    cout << "Speedup: " << sequential_time/parallel_time << endl;
    cout << "Efficiency " << 100*(sequential_time/parallel_time)/std::thread::hardware_concurrency() << endl;
}
}  // namespace threads