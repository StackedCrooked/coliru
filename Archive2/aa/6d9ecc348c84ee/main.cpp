#include <deque>
#include <algorithm>
#include <iostream>

int main()
{
    std::deque<int> queue { 5, 4, 3, 2, 1 };
    auto b = begin(queue);

    std::cout << "Which element? ";
    int n;
    if (std::cin >> n && n > 0 && size_t(n) <= queue.size())
    {
        std::rotate(b, b+n-1, b+n);
        for (auto i : queue)
            std::cout << i << " ";
    } else
    {
        std::cout << "invalid input\n";
    }
        
}
