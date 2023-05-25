#include <iostream>
#include <omp.h>
#include <ctime>

using namespace std;

const int a = 1;
const int b = 2000000;

int is_prime_number(int n) {
    int limit = sqrt(n) + 1;
    for (int i = 2; i <= limit; i++) {
        if (n % i == 0)
            return 0;
    }
    return (n > 1) ? 1 : 0;
}

int count_prime_numbers(int a, int b)
{
    int nprimes = 0;
    if (a <= 2) {
        nprimes = 1;
        a = 2;
    }

    if (a % 2 == 0)
        a++;

    for (int i = a; i <= b; i += 2) {
        if (is_prime_number(i))
            nprimes++;
    }
    return nprimes;
}

int count_prime_numbers_omp(int a, int b) {
    int nprimes = 0;
    if (a <= 2) {
        nprimes = 1;
        a = 2;
    }
    if (a % 2 == 0) a++;
#pragma omp parallel for schedule(dynamic, 100) reduction(+:nprimes)
    for (int i = a; i <= b; i += 2) {
        if (is_prime_number(i))
            nprimes++;
    }
    return nprimes;
}



int main()
{   
    int result;

    int start;
    int end;
    int t;
        
    start = clock();

    result = count_prime_numbers(a, b);

    end = clock(); 
    t = (end - start) / (CLOCKS_PER_SEC/1000);

    cout << "find " << result << " prime numbers in " << t << "milliseconds";

    int result_omp;

    start = clock();

    result_omp = count_prime_numbers_omp(a, b);

    end = clock();
    t = (end - start) / (CLOCKS_PER_SEC/1000);

    cout << "find " << result << " prime numbers in " << t << "milliseconds with omp";
    return 0;
}