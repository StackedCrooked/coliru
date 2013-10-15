#include <list>
#include <algorithm>
using namespace std;

class isprime {
    public:
        // declares the constructor and the operator() overloading
        isprime(){ number = 0, primes.push_back(2);};
        bool operator()(int);

    private:
        // various private functions and variables
        int number;
        list<int> primes;     // creats a list via the stl library
        void morePrimes(int); // function to generate more prime numbers
        bool it;              // Iterator for the morePrimes list
        bool primeCheck;      // Bool used in the morePrimes function
};

bool isprime::operator()(int number)
{
    if(number == 1)              // returns false for 1
        return false;

    if(number > primes.back()){ // Tests to see if the list of primes range would include the number, if not it runs the morePrimes function
        morePrimes(number);
    }

    it = binary_search(primes.begin(),primes.end(),number); // uses stl find to see if the number is in the list of primes.

    if(it)                      // if the returned iterator points to a value = to number then number is prim.
        return true;

    return false;               // returns false if the number wasnt found
}

void isprime::morePrimes(int) {}

#include <random>
#include <functional>
#include <iostream>
#include <iterator>

int main()
{
    auto gen = bind(uniform_int_distribution<>(), mt19937());
    list<int> random_list;

    for (int i=0; i<5; i++) random_list.push_back(gen());

    list<int> isprime_list(random_list.size());
    
    isprime test;
    transform(random_list.begin(), random_list.end(), isprime_list.begin(), test);
}
