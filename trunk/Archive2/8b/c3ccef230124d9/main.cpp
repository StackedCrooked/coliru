#include <queue>
#include <algorithm>
#include <iostream>


int main()
{
    std::queue<int> queue, stash;
    for (int i=1; i<=5; ++i)
        queue.push(i);
    
    std::cout << "Which element? ";
    int n;
    if (std::cin >> n && n > 0 && size_t(n) <= queue.size())
    {
        while (--n)
            stash.push(queue.front()), queue.pop();

        if (!stash.empty())
        {
            int select = stash.front();
            stash.pop();

            while (!stash.empty())
                queue.push(stash.front()), stash.pop();

            queue.push(select);
        }

        while (!queue.empty())
        {
            std::cout << queue.front() << " ";
            queue.pop();
        }
    } else
    {
        std::cout << "invalid input\n";
    }
        
}
