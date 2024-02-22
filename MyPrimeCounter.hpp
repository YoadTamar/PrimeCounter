/**
 * @file MyPrimeCounter.hpp
 * @brief this file contains the declarations for our prime counter
 * @details For implementation details, see GitHub.
 * @authors Yoad Tamar, Lior Vinman
 */


#ifndef MY_PRIME_COUNTER


    /* -------------------- DEFAULT -------------------- */
    /**
     * adding a define so this header wont be included more than once 
    */
    #define MY_PRIME_COUNTER


    /* -------------------- INCLUDES -------------------- */
    #include <iostream>     /** For input/output operations. */   
    #include <stdlib.h>     /** For standard library functions. */
    #include <cmath>        /** For mathematical functions. */


    /* -------------------- DEFINES -------------------- */
    #define PRIMES_ARRAY_LIMIT 45830 /** The limit for the prime numbers array. */


    /* -------------------- GLOBAL VARIABLES -------------------- */
    int array_size_of_primes = 0;           /** The size of the array of prime numbers. */
    int *array_of_prime_numbers = nullptr;  /** Pointer to the array of prime numbers. */
    int *how_much_threads = nullptr;        /** Pointer to the number of threads. */
    pthread_t *thread_list = nullptr;       /** Pointer to the list of threads. */

    /* -------------------- FUNCTIONS -------------------- */
    /**
     * @brief Checks if a number is prime using a naive approach.
     * @param INT The number to check.
     * @param INT The upper limit for checking.
     * @return True if the number is prime, false otherwise.
     */
    bool check_if_number_is_prime_standard(int, int);


    /**
     * @brief Collects prime numbers into an array.
     */
    void create_list_of_primes_for_threads();


    /**
     * @brief Checks if a number is prime.
     * @param INT The number to check.
     * @return True if the number is prime, false otherwise.
     */
    bool isPrime(int);


    /**
     * @brief Counts the number of prime numbers.
     * @return The count of prime numbers.
     */
    int count_how_many_primes_were();


    /**
     * @brief Worker function for counting prime numbers in parallel.
     * @param VOID Thread argument.
     * @return Void pointer.
     */
    void* thread_tast_for_find_and_cound_primes(void*);


    /**
     * @brief Counts the number of prime numbers using multiple threads.
     * @param INT The number of threads to use.
     * @return The count of prime numbers.
     */
    int task_for_threads_to_check_primes(int);


    /**
     * @brief Cleans up allocated resources.
     */
    void cleanup();

#endif  // MY_PRIME_COUNTER
