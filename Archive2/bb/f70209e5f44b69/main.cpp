#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>
#include <climits>

// why we're not using <thread> is beyond me.
#include <pthread.h>

struct ThreadParams
{
    int *ar;
    size_t len;
    unsigned int concurrency;
};

// forward decl
void mergesort_mt(int ar[], size_t len, unsigned int N = 3);


// simple pthread proc
void *mergesort_proc(void *pv)
{
    ThreadParams const *params = static_cast<ThreadParams const*>(pv);
    mergesort_mt(params->ar, params->len, params->concurrency);
    return pv;
}

// implementation of mergesort algorithm
void mergesort_mt(int ar[], size_t len, unsigned int N)
{
    if (len < 2)
        return;
    
    if (N > 0)
    {
        // launch thread, then recurse, then join
        ThreadParams params = { ar, len/2, N/2 };
        pthread_t thrd;
        pthread_create(&thrd, nullptr, mergesort_proc, &params);
        mergesort_mt(ar+len/2, len-len/2, N/2);
        pthread_join(thrd, NULL);
    }
    else
    {
        // stop launching threads
        mergesort_mt(ar, len/2, N/2);
        mergesort_mt(ar+len/2, len-len/2, N/2);
    }
    
    // merge segments.
    std::inplace_merge(ar, ar+len/2, ar+len);
}


int main()
{
    using namespace std::chrono;
    
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<unsigned int> dist(0, INT_MAX);
    
    std::vector<int> v, back(10*1000000);
    
    std::cout << "Generating...\n";
    std::generate_n(back.begin(), back.size(), [&](){return dist(rng);});
    
    time_point<system_clock> t0, t1;
    
    v = back;
    std::cout << "mergesort (st): ";
    t0 = system_clock::now();
    mergesort_mt(v.data(), v.size(), 0);
    t1 = system_clock::now();
    std::cout << duration_cast<milliseconds>(t1-t0).count() << "ms\n";
    
    v = back;
    std::cout << "mergesort (mt=1): ";
    t0 = system_clock::now();
    mergesort_mt(v.data(), v.size(), 1);
    t1 = system_clock::now();
    std::cout << duration_cast<milliseconds>(t1-t0).count() << "ms\n";
    
    v = back;
    std::cout << "mergesort (mt=2): ";
    t0 = system_clock::now();
    mergesort_mt(v.data(), v.size(), 2);
    t1 = system_clock::now();
    std::cout << duration_cast<milliseconds>(t1-t0).count() << "ms\n";
    
    v = back;
    std::cout << "mergesort (mt=3): ";
    t0 = system_clock::now();
    mergesort_mt(v.data(), v.size(), 3);
    t1 = system_clock::now();
    std::cout << duration_cast<milliseconds>(t1-t0).count() << "ms\n";
    
    return 0;
}