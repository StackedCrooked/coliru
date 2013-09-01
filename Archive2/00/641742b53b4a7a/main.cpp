#include <array>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const unsigned int N = 10000; //look for amicable numbers smaller than N
vector<unsigned int> list_of_primes;

typedef array<unsigned int,2> PrimeAndExponent;
typedef vector< PrimeAndExponent > PrimeFactorization;

PrimeFactorization prime_factorize(unsigned int);

int main(int argc, char **argv)
{
    //import a list of primes
    #if 0
    ifstream ifs ("primes_10000.txt");
    for (unsigned int index = 0; index < N; index++) {
        string prime_number;
        getline(ifs, prime_number);
        list_of_primes.push_back(stoi(prime_number));
    }
    ifs.close();
    #else
    list_of_primes.push_back( 13 );
    #endif
    
    
    //test prime factorization function by prime factorizing 12
    auto prime_factorization = prime_factorize(12);
    for( auto const &prime_and_exponent : prime_factorization) { // <-- the line previous version create the internal compiler error
        cout << prime_and_exponent[0] << ", " << prime_and_exponent[1] << endl;
    }

    return 0;
}

PrimeFactorization prime_factorize(unsigned int number)
{
    PrimeFactorization prime_factorization;
    for(unsigned int index = 1; index < list_of_primes.size(); index++) {
        if(number % list_of_primes[index] == 0) {
            PrimeAndExponent prime_and_exponent { list_of_primes[index], 1 };
            prime_factorization.push_back(prime_and_exponent);
            number /= list_of_primes[index];

            while(number % list_of_primes[index] == 0) {
                prime_factorization.back()[1]++;
                number /= list_of_primes[index];
            }
        }
        if(number == 1) {
            break;
        }
    }
    return prime_factorization;
}