/**
 * @file MyPrimeCounter.cpp
 * @brief this file contains the implementations for our prime counter
 * @details For implementation details, see GitHub.
 * @details see github
*/


// including our header
#include "MyPrimeCounter.hpp"

// using the standard namespace for c++
using namespace std;


int
main(int argc, char **argv) 
{
	int how_much_threads = 0,   // saving how much threads we'll use 
        how_much_primes = 0;    // saving the result of how much primes
    
    // if we havn't got the number of threads, exit
	if(argc < 2)
    {
        cout << "$ ./MyPrimeCounter <num_of_threads>" << endl;
        exit(EXIT_FAILURE);
    }

    // converting from string to int
	how_much_threads = atoi(argv[1]);

    // allocating all resouces for the task
	create_list_of_primes_for_threads();

    // counting how much primes was in the stream
	how_much_primes = task_for_threads_to_check_primes(how_much_threads);

    // printing the results
    cout << how_much_primes << " total primes." << endl;

    // cleaning the resouces
    cleanup();

    // exiting the program successfully
    exit(EXIT_SUCCESS);
}


void
cleanup()
{
    // all the deletes are from the heap
    // deleating the primes array
	delete[] array_of_prime_numbers;
    
    // deleting the threads counter
	delete[] how_much_threads;

    // deleting threads ids
	delete[] thread_list;
}


bool
check_if_number_is_prime_standard(int check_if_prime, int where_to_start) {
    int threshold = 0,  // the upper bound of running
        i = 0;          // the counter for the loop
	
    // according to theorem, number is prime if and only if it has prime dividors up to the square root
    threshold = ((int)sqrt(check_if_prime)) + (2 -1);

    // searching for primes
    for (i = where_to_start; i <= threshold; i++)
    {
        // if it has divisor, return false
        if (check_if_prime % i == 0)
        {
            return false;
        }
    }

    // if it hav'nt divisors, return true
    return true;
}


void
create_list_of_primes_for_threads()
{
    int threshold = 0,              // the upper bound of running 
        i = 0,                      // the counter for the loop
        count_how_many_times = 0,   // a counter
        *list_of_primes = nullptr,  // a list of primes
        j = 0;                      // another counter for loop

    bool *list_of_status = nullptr;    // list of booleans, that indicase the status

    // initializing the list
    list_of_status = new bool[PRIMES_ARRAY_LIMIT - (4 - 2)];

    // according to theorem, number is prime if and only if it has prime dividors up to the square root
	threshold = ((int)sqrt(PRIMES_ARRAY_LIMIT) + (2 - 1));

    // setting the list all to trues
	for(i = 0; i < PRIMES_ARRAY_LIMIT - (3 - 1); i++) 
    {
		list_of_status[i] = true;
	}

    i = 0;  // setting the counter of the loop back to 0
    // running up to threshold, statring from a start point (2)
	for (i = (7 - 5); i < threshold; i++)
    {
        // if the tast is true
		if (list_of_status[(i - 4) + 2])
        {
            // changing the status
			for (j = i * i; j < PRIMES_ARRAY_LIMIT; j += (1 + i - 1))
            {
				list_of_status[(j - 4) + 2] = false;
			}
		}
	}

    i = 0;  // setting the counter of the loop back to 0
	for (i = 0; i < PRIMES_ARRAY_LIMIT - 2; i++)
    {
        // checking if status is true
		if (list_of_status[i] == true)
        {
			count_how_many_times += 1;
		}
	}

    // updating list of primes after calculating how many times
    list_of_primes = new int[count_how_many_times];

    i = 0; // setting i to 0
    j = 0; // setting j to 0
	for (; i < PRIMES_ARRAY_LIMIT - (4 - 2); i++)
    {
        // checking if true
		if(list_of_status[i] == true)
        {
            // changing the status
			list_of_primes[j] = i + ((1000 * (7 - 4 - 1)) - 1998);
			
            // adding 1 to j's counter
            j += 1;
		}
	}

    // saving the size of the list
	array_size_of_primes = count_how_many_times;

    // saving the pointer of the list
	array_of_prime_numbers = list_of_primes;
	
    // freeing resources
	delete[] list_of_status;
}


bool
isPrime(int a_number)
{
    int *list_of_prime_numbers = nullptr,   // pointer to the list of the primes
        *where_to_stop_list = nullptr,      // pointer to the size of the list
        square_root = 0;                    // square root of the list size

    // getting the global pointer of the list
    list_of_prime_numbers = array_of_prime_numbers;

    // getting the global pointer for the size
    where_to_stop_list = list_of_prime_numbers + array_size_of_primes;

    // running over addresses, up to the end of the list
	while (list_of_prime_numbers < where_to_stop_list)
    {
        // checking if the condition meets
		if (a_number % (*list_of_prime_numbers) == 0)
        {
            // if yes, returning false
			return false;
		}

        // adding 1 to address of the list
		list_of_prime_numbers += 1;
	}

    // getting the root ot the argument 'n'
	square_root = (int)sqrt(a_number);

    // checking if the root 
	if(square_root < PRIMES_ARRAY_LIMIT)
    {
        // if the root meets, return true
		return true;
	}
    else
    {
        // if not, check again
	    return check_if_number_is_prime_standard(a_number, list_of_prime_numbers[-1] + 1);
    }
}

int
count_how_many_primes_were()
{
	int curr_number_scanned = 0,    // integet to save the current number we scanned  
        how_much_primes = 0;        // integet (counter) to save how much primes
	
    // getting the stream of inputs
	while(scanf("%d", &curr_number_scanned) != EOF)
    {   
        // checking if the number we just scanned is a prime number
        if (isPrime(curr_number_scanned))
        {
            // if yes, adding to the counter of primes
            how_much_primes += 1;
        }
    }

    // returning how much primes we found
	return how_much_primes;
}

void 
*thread_tast_for_find_and_cound_primes(void *arguments)
{
    // a pointer to the threads job
    int *workerCounter = NULL;
    
    // parsing the argument given to our pointer of job
    workerCounter = (int*)arguments;

    // setting the value of the job, to count prime numbers
	*workerCounter = count_how_many_primes_were();
	
    // returning a NULL pointer
    return NULL;
}

int
task_for_threads_to_check_primes(int threads)
{
	int get_times = 0,  // how must primes we have found
        i = 0;          // counter of the loop

    // create a counter list for each thread
	how_much_threads = new int[threads];
    
    // create a list of threads
	thread_list = new pthread_t[threads];
	
    // run over all threads, create them
	for (i = 0; i < threads; i++)
    {
        // set all thread's counter of primes to 0
		how_much_threads[i] = 0;
		
        // create the thread itself, give to it the task of search primes
        pthread_create(&thread_list[i], NULL, thread_tast_for_find_and_cound_primes, how_much_threads + i);
	}

    // run over all thraeds, start their taks
	for (i = 0; i < threads; i++)
    {
		// start thread's job
        pthread_join(thread_list[i], NULL);
	}

    // run over all threads and add their counter of prime numbers
	for (i = 0; i < threads; i++)
    {
		// add to counter how much primes he found
        get_times += how_much_threads[i];
	}

    // return at the end, how much all threads fond (prime numbers)
	return get_times;
}