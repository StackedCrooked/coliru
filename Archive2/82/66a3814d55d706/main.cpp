#include <iostream>
#include <string>
#include <vector>
#include <list>

template <typename Iter>
void printElems(Iter begin, Iter end)
{
    while (begin != end)
        std::cout << *begin++ << ' ';
    std::cout << '\n';
}

int main()
{
    int arr[4] = {1,2,3,4};
    std::string str = "Hello world!";
    
    std::vector<int> vec;
    for (int i = 0; i < 5; ++i)
        vec.push_back(i);
    
    std::list<double> list;
    list.push_front(3.14159265358979);
    list.push_front(2.718281828459);
    
    printElems(arr, arr + 4);
    printElems(str.begin(), str.end());
    printElems(vec.begin(), vec.end());
    printElems(list.begin(), list.end());
}
