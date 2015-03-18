#include <iostream>
#include <chrono>
#include <vector>
#include <numeric>

using namespace std;
using namespace std::chrono;



int main()
{
    const int N = 10000000;
    vector<int> v(N);
    for (int i = 0; i<N; ++i)
        v[i] = i;
        
            //using std::accumulate
    {
        high_resolution_clock::time_point t1 = high_resolution_clock::now();

        long long int sum = accumulate(v.begin(), v.end(), static_cast<long long int>(0));

        high_resolution_clock::time_point t2 = high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

        cout << duration << "microseconds  output = " << sum << " (std::accumulate)\n";
    }

    //looping with iterators
    {
        high_resolution_clock::time_point t1 = high_resolution_clock::now();

        long long int sum = 0;
        for (auto it = v.begin(); it != v.end(); ++it)
            sum+=*it;

        high_resolution_clock::time_point t2 = high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

        cout << duration << "microseconds  output = " << sum << " (Iterators)\n";
    }

    //looping with integers
    {
        high_resolution_clock::time_point t1 = high_resolution_clock::now();

        long long int sum = 0;
        for (int i = 0; i<N; ++i)
            sum+=v[i];

        high_resolution_clock::time_point t2 = high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

        cout << duration << "microseconds  output = " << sum << " (integer index)\n";
    }

    //looping with integers (UNROLL 2)
    {
        high_resolution_clock::time_point t1 = high_resolution_clock::now();

        long long int sum = 0;
        for (int i = 0; i<N; i+=2)
            sum+=v[i]+v[i+1];

        high_resolution_clock::time_point t2 = high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

        cout << duration << "microseconds  output = " << sum << " (integer index, UNROLL 2)\n";
    }

    //looping with integers (UNROLL 4)
    {
        high_resolution_clock::time_point t1 = high_resolution_clock::now();

        long long int sum = 0;
        for (int i = 0; i<N; i+=4)
            sum+=v[i]+v[i+1]+v[i+2]+v[i+3];

        high_resolution_clock::time_point t2 = high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

        cout << duration << "microseconds  output = " << sum << " (integer index, UNROLL 4)\n";
    }


    return 0;
}