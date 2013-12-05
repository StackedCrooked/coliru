
#include <iostream>
#include <string>
#include <vector>
#include <set>
       

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

std::set<unsigned> pr;
std::set<unsigned> npr;

std::vector<unsigned> counters;
std::vector<unsigned> computedPrimes;

std::vector<unsigned> allPrimes;

bool isPrime(unsigned a)
{
    if (a <= 1)
        return false;
    if (pr.count(a))
        return true;
    if (npr.count(a))
        return false;       
    unsigned x = (a/2)+1;
    while (--x > 1) {
        if ((a % x) == 0) {
            npr.insert(a);
            return false;
        }
    }
    pr.insert(a);
    return true;
}

int main()
{
    unsigned MAXPRIME = 5000;
    unsigned MAXFACTORS = 5000;
    
    std::vector<int> factors;
    for (unsigned x=0; x<MAXPRIME; x++) {
        if (isPrime(x)) {
            factors.push_back(0);
            allPrimes.push_back(x);
        }
        counters.push_back(0);
    }
   
    int MAX_FACTOR = 20;
   
    unsigned maxCounter = 0;
    unsigned maxCounterIdx = 0;   
    bool keep = true;
    while (keep)
    {
        // increment factors
        unsigned long long idx = 0;
        factors[idx]++;
        while ((factors[idx] > MAX_FACTOR) && (idx < factors.size())) {
            factors[idx] = 0;            
            idx++;
            factors[idx]++;
        }        
        if (idx >= factors.size())
            keep = false;
        
        // compute value
        unsigned long long value = 0;
        for (unsigned x=0; x<allPrimes.size(); ++x) {
            value += allPrimes[x] * factors[x];
        }
        
        while (counters.size() <= value) {
            counters.push_back(0);
        }        
        
        if (maxCounter < ++counters[value]) 
        {
            maxCounter = counters[value];
            maxCounterIdx = value;
            std::cout << "updating max counter: " << maxCounter << ", for idx: " << maxCounterIdx << std::endl;
        }
        
        if (maxCounter > MAXFACTORS)
            break;
    }
   
    std::cout << "max counter: " << maxCounter << ", for idx: " << maxCounterIdx << std::endl;   
}

