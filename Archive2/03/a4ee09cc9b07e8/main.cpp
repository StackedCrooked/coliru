#include <iostream>
#include <forward_list>

int main()
{
    std::forward_list<int> p;
    std::cout << "num = ";
    int n;
    while(std::cin >> n)
    {   
        p.push_front(n);
        std::cout << "n = ";
    }

    for(int n: p)
        std::cout<< n << " ";
    std::cout << '\n';
}
