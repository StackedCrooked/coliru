#include <iostream>
#include <vector>

using std::vector;

template <class T>
T vectorsum(vector<T> v) {
    T sum = 0;
    for (int i = 0; i < v.size(); i++)
        sum = sum + v[i];
    return sum;
}

int main()
{
    std::vector<int> v;
    
    for (int i = 0; i < 5; i++) v.push_back(i);
    
    std::cout << vectorsum(v);
    
}