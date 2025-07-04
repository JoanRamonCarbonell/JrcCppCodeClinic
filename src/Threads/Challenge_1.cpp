/**
 * Challenge: Multiply two matrices
 */
#include "Threads/Challenge_1.h"
#include <thread>
#include <cmath>
#include <iostream>
#include <mutex>
#include <vector>

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

void print_matrix(std::string name, long ** A, size_t num_rows, size_t num_cols) {
    uint64_t num_rows_{static_cast<uint64_t>(num_rows)};
    uint64_t num_cols_{static_cast<uint64_t>(num_cols)};
    cout << "+-------" << name << "-------+" << endl;
    for (int i=0; i < num_rows_; i++) {
        for (int j=0; j < num_cols_; j++) {
            cout << " | " << A[i][j];
        }
        cout << " |" << endl;
        cout << "+------------------+" << endl;
    }
}

void rows_product_worker(long ** A, long ** B, long ** C, int row_a, size_t num_cols_a, size_t num_cols_b) {
    // cout << "Calculate the product of the row: " << row_a << "with each of the " << num_cols_b << " columns." << endl;
    uint64_t num_cols_a_{static_cast<uint64_t>(num_cols_a)};
    uint64_t num_cols_b_{static_cast<uint64_t>(num_cols_b)};

    for (uint64_t col_b = 0; col_b < num_cols_b_; col_b++) {
        C[row_a][col_b] = 0;
        for (uint64_t col_a = 0; col_a < num_cols_a_; col_a++) {
            C[row_a][col_b] += A[row_a][col_a] * B[col_a][col_b];
        }
    }
}

/* parallel implementation of matrix multiply */
void parallel_matrix_multiply(long ** A, size_t num_rows_a, size_t num_cols_a,
                              long ** B, size_t num_rows_b, size_t num_cols_b,
							  long ** C) {
    /***********************
     * YOUR CODE GOES HERE *
     ***********************/
    // Every row product will be executed in a different thread -> defined in num_rows_a
    uint64_t num_rows_a_{static_cast<uint64_t>(num_rows_a)};
    std::vector<std::thread> rows_product;

    for (int row = 0; row < num_rows_a_; row++) {
        rows_product.emplace_back(rows_product_worker, A, B, C, row, num_cols_a, num_cols_b);
    }

    for (auto& single_row_product : rows_product) {
        single_row_product.join();
    }
}

void Challenge_1::run () {
	const int NUM_EVAL_RUNS = 3;
    const size_t NUM = 10000;
	const size_t NUM_ROWS_A = NUM;
	const size_t NUM_COLS_A = NUM;
	const size_t NUM_ROWS_B = NUM_COLS_A;
	const size_t NUM_COLS_B = NUM;

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

    // cout << "Matrix A:" << endl;
    // print_matrix("Matrix A", A, NUM_ROWS_A, NUM_COLS_A);

    // cout << "Matrix B:" << endl;
    // print_matrix("Matrix B", B, NUM_ROWS_B, NUM_COLS_B);

    sequential_matrix_multiply(A, NUM_COLS_A, NUM_ROWS_A, B, NUM_COLS_B, NUM_ROWS_B, sequential_result); // "warm up"

    // cout << "Matrix Product Sequential:" << endl;
    // print_matrix("Seq", sequential_result, NUM_ROWS_A, NUM_COLS_B);

    for (int i=0; i<NUM_EVAL_RUNS; i++) {
        auto startTime = std::chrono::high_resolution_clock::now();
        sequential_matrix_multiply(A, NUM_COLS_A, NUM_ROWS_A, B, NUM_COLS_B, NUM_ROWS_B, sequential_result);
        sequential_time += std::chrono::high_resolution_clock::now() - startTime;
    }
    sequential_time /= NUM_EVAL_RUNS;

    cout << "Evaluating Parallel Implementation..." << endl;
	std::chrono::duration<double> parallel_time(0);

    parallel_matrix_multiply(A, NUM_COLS_A, NUM_ROWS_A, B, NUM_COLS_B, NUM_ROWS_B, parallel_result); // "warm up"

    // cout << "Matrix Product Parallel:" << endl;
    // print_matrix("Par", parallel_result, NUM_ROWS_A, NUM_COLS_B);

    for (int i=0; i<NUM_EVAL_RUNS; i++) {
        auto startTime = std::chrono::high_resolution_clock::now();
        parallel_matrix_multiply(A, NUM_COLS_A, NUM_ROWS_A, B, NUM_COLS_B, NUM_ROWS_B, parallel_result);
        parallel_time += std::chrono::high_resolution_clock::now() - startTime;
    }
    parallel_time /= NUM_EVAL_RUNS;
	
    // verify sequential and parallel results
    for (size_t i=0; i<NUM_ROWS_A; i++) {
        for (size_t j=0; j<NUM_COLS_B; j++) {
            // cout << "sequential_result: " << sequential_result[i][j] << "parallel_result: " << parallel_result[i][j] << endl; 
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