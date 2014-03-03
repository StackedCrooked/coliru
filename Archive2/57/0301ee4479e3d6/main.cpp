#include <iostream>
#include <cmath>
#include <limits>
#include <cstdint>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>

int main()
{
   std::size_t n = 1000000 ; // number of primes to be summed up
   // std::cin >> n ; // n * ( logn + std::log(logn) ) < max value size_t can hold

   // use the prime number theorem to get an upper bound on the nth prime
   // http://en.wikipedia.org/wiki/Prime_number_theorem
   const auto logn = std::log(n) ;
   const std::size_t SZ = n * ( logn + std::log(logn) ) + 1 ;

   // generate a prime number sieve upto the upper_bound
   // http://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
   std::vector<bool> sieve( SZ, true ) ;
   const std::size_t ub_root = std::sqrt(SZ) + 2 ;
   for( std::size_t i = 2 ; i < ub_root ; ++i ) if( sieve[i] )
       for( std::size_t j = i+i ; j < SZ ; j += i ) sieve[j] = false ;

   // count and sum up till the nth prime number
   std::size_t cnt = 0 ;
   boost::multiprecision::cpp_int sum = 0 ;

   for( std::size_t i = 2 ; i < SZ && cnt < n ; ++i ) if( sieve[i] )
   {
      ++cnt ;
      sum += i ;
      // printing out of i elided
   }

   std::cout << "sum of the first " << n << " prime numbers: " << sum << '\n' ;
}
