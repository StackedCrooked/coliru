#include <iostream>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>
#include <ctime>

int main()
{
    enum {Primes = 168};
    const int prime[] = {3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,
    79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,
    191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,
    307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,
    431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541,547,557,
    563,569,571,577,587,593,599,601,607,613,617,619,631,641,643,647,653,659,661,673,
    677,683,691,701,709,719,727,733,739,743,751,757,761,769,773,787,797,809,811,821,
    823,827,829,839,853,857,859,863,877,881,883,887,907,911,919,929,937,941,947,953,
    961,967,971,977,983,991,997};//primes (2,1000]
    //we ignored 2 because half the numbers in a range from
    //1->n will be even and half will be odd
    
    const int max = 100000;
    int sum = max;
    //we will find the sum of the primes given above
    //for the values of i^2+1
    //so every odd will become even and even will become odd
    //which means we can skip 1 in our for loop
    //since 1 * 1 == 1 + 1 == 2 and 2 we already added
    
    std::clock_t start = std::clock();
    std::cout << "Method 1:" << std::endl;
    
    using boost::multiprecision::cpp_int;
    for(cpp_int i = 2; i <= max; ++i)
    {
        for(int j = 0; j < Primes; ++j)
        {
            if((i*i+1) % prime[j] == 0)
            {
                sum += prime[j];
            }
        }
    }
    
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "This method took: " << (std::clock() - start) / static_cast<double>(CLOCKS_PER_SEC) << " seconds" << std::endl;
    
    start = std::clock();
    sum = max;
    std::cout << "Method 2:" << std::endl;
    
    for(cpp_int i = 2; i <= max; ++i)
    {
        cpp_int temp = i * i + 1;
        
        while(temp&1==0)
        {
            temp >>= 1;
        }
        for(int j = 0; temp != 1 && j < Primes; ++j)
        {
            if(temp%prime[j]==0)
            {
                sum += prime[j];
                while(temp%prime[j]==0)
                {
                    temp /= prime[j];
                }
            }
        }
    }
    
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "This method took: " << (std::clock() - start) / static_cast<double>(CLOCKS_PER_SEC) << " seconds" << std::endl; 
}