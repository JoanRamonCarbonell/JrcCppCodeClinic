/**
 * Challenge: Multiply two matrices
 */
#include "Threads/Challenge_1.h"
#include <thread>
#include <cmath>
#include <iostream>
#include <mutex>

namespace threads
{

using namespace std;

/* sequential implementation of matrix multiply */
void sequential_matrix_multiply(long ** A, size_t num_rows_a, size_t num_cols_a,
                                long ** B, size_t num_rows_b, size_t num_cols_b,
							    long ** C) {
    for (size_t i=0; i<num_rows_a; i++) {
        for (size_t j=0; j<num_cols_b; j++) {
			C[i][j] = 0; // initialize result cell to zero
            for (size_t k=0; k<num_cols_a; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
		}
	}
}

/* worker */
void calculate_position(long ** A, long ** B, long ** C, int row_A, int col_B, size_t num_cols_a) {
    for (int i; i < num_cols_a; i++) {
        C[row_A][col_B] += A[row_A][i] * B[i][col_B];
    }
}

/* parallel implementation of matrix multiply */
void parallel_matrix_multiply(long ** A, size_t num_rows_a, size_t num_cols_a,
                              long ** B, size_t num_rows_b, size_t num_cols_b,
							  long ** C) {
    /***********************
     * YOUR CODE GOES HERE *
     ***********************/
    // Create a thread that calculates first element
    auto finished1{false};
    auto finished2{false};
    auto row_A{0};
    auto col_B{0};
    std::mutex mtx;

    cout << "Start parallel_matrix_multiply" << endl;

    auto next_product{[&mtx](int& row_A, int& col_B, size_t num_rows_a){

        if (row_A < num_rows_a) {
            std::lock_guard<std::mutex> my_mtx(mtx);
            row_A++;
            col_B++;
            return true;
        } else {
            return false;
        }
    }};

    while(!finished1 && !finished2) {
        std::thread t1(calculate_position, A, B, C, row_A, col_B, num_cols_a);
        std::thread t2(calculate_position, A, B, C, row_A, col_B, num_cols_a);
        if (t1.joinable()) {
            if (next_product(row_A, col_B, num_cols_a)) {
                t1.join();
                std::thread t1(calculate_position, A, B, C, row_A, col_B, num_cols_a);
            } else {
                t1.join();
                finished1=true;
            }
        }
        if (t2.joinable()) {
            if (next_product(row_A, col_B, num_cols_a)) {
                t2.join();
                std::thread t2(calculate_position, A, B, C, row_A, col_B, num_cols_a);
            } else {
                t2.join();
                finished2=true;
            }
        }
    }

    cout << "End parallel_matrix_multiply" << endl;
}

void Challenge_1::run () {
	const int NUM_EVAL_RUNS = 3;
	const size_t NUM_ROWS_A = 1000;
	const size_t NUM_COLS_A = 1000;
	const size_t NUM_ROWS_B = NUM_COLS_A;
	const size_t NUM_COLS_B = 1000;

    // intialize A and B with values in range 1 to 100    
    long ** A = (long **)malloc(NUM_ROWS_A * sizeof(long));
    long ** B = (long **)malloc(NUM_ROWS_B * sizeof(long));
    if ((A == NULL) || (A == NULL)) {
        exit(2);
    }
    for (size_t i=0; i<NUM_ROWS_A; i++) {
        A[i] = (long *)malloc(NUM_COLS_A * sizeof(long));
        B[i] = (long *)malloc(NUM_COLS_B * sizeof(long));
        if ((A[i] == NULL) || (A[i] == NULL)) {
            exit(2);
        }
        for (size_t j=0; j<NUM_COLS_A; j++) {
            A[i][j] = rand() % 100 + 1;
            B[i][j] = rand() % 100 + 1;
        }
    }

	// allocate arrays for sequential and parallel results
    long ** sequential_result = (long **)malloc(NUM_ROWS_A * sizeof(long));
    long ** parallel_result = (long **)malloc(NUM_ROWS_A * sizeof(long));
    if ((sequential_result == NULL) || (parallel_result == NULL)) {
        exit(2);
    }
    for (size_t i=0; i<NUM_ROWS_A; i++) {
        sequential_result[i] = (long *)malloc(NUM_COLS_B * sizeof(long));
        parallel_result[i] = (long *)malloc(NUM_COLS_B * sizeof(long));
        if ((sequential_result[i] == NULL) || (parallel_result[i] == NULL)) {
            exit(2);
        }
    }

    cout << "Evaluating Sequential Implementation..." << endl;
	std::chrono::duration<double> sequential_time(0);
    sequential_matrix_multiply(A, NUM_COLS_A, NUM_ROWS_A, B, NUM_COLS_B, NUM_ROWS_B, sequential_result); // "warm up"
    for (int i=0; i<NUM_EVAL_RUNS; i++) {
        auto startTime = std::chrono::high_resolution_clock::now();
        sequential_matrix_multiply(A, NUM_COLS_A, NUM_ROWS_A, B, NUM_COLS_B, NUM_ROWS_B, sequential_result);
        sequential_time += std::chrono::high_resolution_clock::now() - startTime;
    }
    sequential_time /= NUM_EVAL_RUNS;

    cout << "Evaluating Parallel Implementation..." << endl;
	std::chrono::duration<double> parallel_time(0);
    parallel_matrix_multiply(A, NUM_COLS_A, NUM_ROWS_A, B, NUM_COLS_B, NUM_ROWS_B, parallel_result); // "warm up"
    for (int i=0; i<NUM_EVAL_RUNS; i++) {
        auto startTime = std::chrono::high_resolution_clock::now();
        parallel_matrix_multiply(A, NUM_COLS_A, NUM_ROWS_A, B, NUM_COLS_B, NUM_ROWS_B, parallel_result);
        parallel_time += std::chrono::high_resolution_clock::now() - startTime;
    }
    parallel_time /= NUM_EVAL_RUNS;
	
    // verify sequential and parallel results
    for (size_t i=0; i<NUM_ROWS_A; i++) {
        for (size_t j=0; j<NUM_COLS_B; j++) {
            if (sequential_result[i][j] != parallel_result[i][j]) {
                cout << "ERROR: Result mismatch at row " << i << ", col " << j << "!" << endl;
            }
        }
    }
    auto avg_seq_time{sequential_time.count()*1000};
    auto avg_par_time{parallel_time.count()*1000};
    auto speedup{sequential_time/parallel_time};
    auto eff{(100*(sequential_time/parallel_time)/std::thread::hardware_concurrency())};
    cout << "Average Sequential Time: " << avg_seq_time << endl;
    cout << "Average Parallel Time: " << avg_par_time << endl;
    cout << "Speedup: " << speedup << endl;
    cout << "Efficiency " << eff << endl;
}
}  // namespace threads