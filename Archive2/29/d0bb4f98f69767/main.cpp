template <typename T>
class Vector {
public:
    explicit Vector(const int n);
    explicit Vector(const int n, const T& val);
    T& operator[](const int i);
    inline int const length();
    inline void fill(const T& val);
    T sum() const;
private:
    T* arr;
    int len;
};

//#include "vector.h"
#include <iostream>
#include <algorithm>

using namespace std;

template <typename T>
inline void Vector<T>::fill(const T& val)
{
    for (int i = 0; i < len; ++i) {
        arr[i] = val;
    }
}

template <typename T>
//inline T& Vector<T>::sum() // !!
inline T Vector<T>::sum() const 
{
    T total = 0;
    for (int i = 0; i < len; ++i) {
        total += arr[i];
    }
    return total;
}

template <typename T>
Vector<T>::Vector(const int n) : arr(new T[n]()), len(n)
{
    //cout << "Vector(n)" <<'\n';
}

template <typename T>
Vector<T>::Vector(const int n, const T& val) : arr(new T[n]), len(n)
{
    //cout << "Vector(n, val)" <<'\n';
    for (int i = 0; i < len; ++i) {
        arr[i] = val;
    }
}

template <typename T>
T& Vector<T>::operator[](const int i)
{
    return arr[i];
}

template <typename T>
int const Vector<T>::length()
{
    return len;
}

template class Vector<int>;
template class Vector<float>;

#include <chrono>
#include <vector>

using namespace std;

int main() 
{
    const int n = 20000000;
    float sum = 0;
    Vector<float> vec(n, 1);
    chrono::steady_clock::time_point start = chrono::steady_clock::now();   
    sum = vec.sum();
    chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    cout << "my vec sum = " << sum << '\n';
    cout << "my vec impl took " << chrono::duration_cast<chrono::microseconds>(end - start).count()
              << "us.\n";

    sum = 0;
    vector<float> vec2(n, 1);
    start = chrono::steady_clock::now();
    for (int i = 0; i < n; ++i) {
        sum += vec2[i];
    }
    end = std::chrono::steady_clock::now();
    cout << "std::vec sum = " << sum << '\n';
    cout << "stl::vec impl took " << chrono::duration_cast<chrono::microseconds>(end - start).count()
              << "us.\n";
              
              
    sum = 0;
   // sum = std::accumulate(vec3.cbegin(), vec3.cend(), 0.0f);
    start = chrono::steady_clock::now();
    const float* ptr = &vec2[0];
    const float* const  endd = ptr + vec2.size(); //vec3.cend();
    while ( ptr < endd )
        sum += *ptr++;
    end = std::chrono::steady_clock::now();
    cout << "std::vec sum with pointers = " << sum << '\n';
    cout << "stl::vec impl took " << chrono::duration_cast<chrono::microseconds>(end - start).count()
              << "us.\n";
              
    sum = 0;
    start = chrono::steady_clock::now();
    sum = std::accumulate(vec2.cbegin(), vec2.cend(), 0.0f);
    end = std::chrono::steady_clock::now();
    cout << "std::vec sum with accumulate = " << sum << '\n';
    cout << "stl::vec impl took " << chrono::duration_cast<chrono::microseconds>(end - start).count()
              << "us.\n";
}