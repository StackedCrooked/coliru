#include <algorithm>
#include <iostream>
#include <vector>

/**
 * Normal partition sequence exceeds 5000 around n = 30.
 * Take upper bound n = 100 (http://oeis.org/A000041).
 * 
 * Function for prime partitions:
 *  κ(n) = (1 / n) * (sopf(n) +  ( (j = 1, n - 1)Σ( sopf(j) * κ(n - j) ) ) ) 
 * 
 * where sopf(int) is the sum of prime factors
 * 
 */

/**
 * Class that encapsulates the generation functions
 */
class PrimePartition {
public:
    //! Solves prime partitions for n
    int Solve(const int n) const;
private: 
    //! Sum of Prime Factors
    int sopf (const int n) const;
    
private:
    //! Array of prime numbers
    static const int primes[];
};

/**
 * This function is giving the wrong results
 */
int PrimePartition::Solve(const int n) const {
    //! κ(n) = (1 / n) * (sopf(n) +  ( (j = 1, n - 1)Σ( sopf(j) * κ(n - j) ) ) ) 
    
    //! (1 / n)
    const double division = 1 / n;
    
    //! sopf(n)
    const int sumN = sopf(n);
    
    //! n upper for sum over
    const int upper = n - 1;
    
    //! (j = 1, n - 1)
    //! Σ( sopf(j) * κ(n - j) )
    int sumOver = 0;
    for (int j = 1; j <= upper; j++) {
        sumOver += (sopf(j) * Solve(n - j));
    }
    
    //! Return (1 / n) * (sumN + sumOver)
    return division * (sumN + sumOver);
}

/**
 * This function is giving the right results
 */
int PrimePartition::sopf(const int n) const {
    int answer = 0;
    int i = 0;
    
    const int upper = n / 2;
    while (primes[i] <= upper){
		if (n % primes[i] == 0) {
			answer += primes[i];
		}
		i++;
	}
	return answer;
}

/**
 * Hardcoded primes
 */
const int PrimePartition::primes[] = {
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31,
    37, 41, 43, 47, 53, 59, 61, 67, 71, 73,
    79, 83, 89, 97, 101, 103, 107, 109, 113
};

int main() {
    PrimePartition p;
    
    //! Dit hoort 6 te zijn  
    std::cout << p.Solve(11);   
    
    
//    int solution = 0;
    
    
//    for (int i = 2; i < 100; i++) {
//        if (p.Solve(i) > 5000) {
//            solution = i; 
//            break;
//        }
//    }
    
//    std::cout << "Solution: " << solution << std::endl;
}




