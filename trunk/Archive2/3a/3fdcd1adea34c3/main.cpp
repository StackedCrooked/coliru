#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <queue>
#include <chrono>
#include <cassert>

using namespace std;

double time_slower_sort(vector<int>& a) 
{
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    for(size_t i=0 ; i < a.size() ; ++i)  
    {

        vector<int>::iterator it = max_element( a.begin() + i ,a.end() ) ;
        int max_value = *it; 
        *it = a[i];
        a[i] = max_value;    

    }
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    return duration;
}



double time_faster_sort(vector<int>& a) // passing by constant reference, to avoid copies.
{
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();


    // Push into the priority queue. Logarithmic cost per insertion = > O (n log(n)) total insertion cost
    priority_queue<int> pq;
    for(size_t i=0 ; i<a.size() ; ++i)
    {
        pq.push(a[i]);
    }

    // Read of the elements from the priority queue in order of priority
    // Constant reading cost per read => O(n) reading cost for entire vector
    for(size_t i=0 ; i<a.size() ; ++i)
    {
        a[i] = pq.top();
        pq.pop();
    }
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    return duration;

}




int main(int argc, char** argv)
{
    // Iterate over vectors of different sizes and try out the two different variants
    for(size_t N=1000; N<=10000 ; N += 100 ) 
    {

        // initialize two vectors with identical random elements
        vector<int> a(N),b(N);

        // initialize with random elements
        for(size_t i=0 ; i<N ; ++i) 
        {
            a[i] = rand() % 1000; 
            b[i] = a[i];
        }

        // Sort the two different variants and time them  
        cout << N << "  " 
             << time_slower_sort(a) << "\t\t" 
             << time_faster_sort(b) << endl;

        // Sanity check
        for(size_t i=0 ; i<=N-2 ; ++i) 
        {
            assert(a[i] == b[i]); // both should return the same answer
            assert(a[i] >= a[i+1]); // else not sorted
        }

    }
    return 0;
}