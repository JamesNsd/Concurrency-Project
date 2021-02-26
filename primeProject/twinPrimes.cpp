/*! 
  \file twinPrimes.cpp 
  \author James Nolan
  \date 26/02/2021
  \copyright License: GNU Affero General Public License v3.0.
*/

#include <iostream>
#include <stdio.h>
#include <omp.h>
#include <math.h>
using namespace std;

/*!
  \brief Using Sieve of Erastothene, counts the number of primes up to n. 
  \param n is the number to calculate the primes up to
  \return Number of primes
*/
long countp(long long n)
  {
    bool *arr = new bool[n]; // dynamically allocates an array of booleans.
    int count = 0;
    // all value true
    for(long long i = 0L; i < n; i ++){ // L is a primitive long
        arr[i] = true;
    }
    // mark false values
    for(long long i = 2; i * i <= n; i++){
        if(arr[i]){// if true
            for(long long j =i*2; j <= n; j += i){ // start at first multiple of i
                arr[j] = false;
            }
        } 
    }
    for(long long i = 2L; i < n; i ++){
        if(arr[i]) count ++;
    }

    delete[] arr;
    return count;
  }

/*!
  \brief Concurrent program to calculate the number of twin primes 
  \param n is the number to calculate the primes up to
  \return Number of twins
  */
long concurrent(long long n)
{
    bool *arr = new bool[n];
    int count = 0;


    omp_set_num_threads(128); //set number of threads
    
    const long long lastNumSquared = sqrt(n);

    #pragma omp parallel for  // divide loop iterations for each thread
    
    for(long long i = 0L; i < n; i ++){
        arr[i] = true;
    }
    
    #pragma omp parallel for schedule(dynamic) // dynamically distribute loop iterations between threads
    for(long long i = 2; i <= lastNumSquared; i++){
        if(arr[i]){
            for(long long j =i*2; j <= n; j += i){
                arr[j] = false;
            }
        } 
    }
    #pragma omp parallel for  // divide loop iterations for each thread
    for(long long i = 3; i < n-2; i += 2){ 
        if(arr[i] && arr[i+2])
        {
            #pragma omp critical  // stop race condition from occuring
            count ++;
	    cout << "(" << i << "," << i+2 << ")" << endl;
        } 
    }
    delete[] arr;
    return count;
}



int main(){

  long long n = 200000000;

  cout << " The number of twin primes : " << concurrent(n) << endl;

  return 0;
}
