#include <algorithm>
#include <iostream>

template<class T>
bool greater(const T& lhs, const T& rhs)
{return lhs>rhs;}

int main() {
    int data[2]={0};
    std::sort(data, data+2, greater<int>);
    std::cout << "success";
}