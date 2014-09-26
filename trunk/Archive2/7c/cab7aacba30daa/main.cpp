#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
    int last = 0;
    int current = 1;
    std::vector<int> fibs;
    fibs.push_back(last);
    int sum = 0;
    
    while(current < 4000000) {
        if (current %2 == 0 )
        {
            sum += current;
        }
        fibs.push_back(current);
        int next = current+last;
        last = current;
        current = next;
    }
    
    std::cout << fibs << std::endl;
    std::cout << sum << std::endl;
}
