#include <cstddef>
#include <list>
#include <algorithm>
#include <iostream>

int main()
{
    std::list<int> l{1, 2, 3, 4};
    auto it = std::next(l.begin(), 2);
    std::for_each(it, l.end(), [](int i)
        {
            std::cout << i << " ";
        }
                  );
    return 0;
}
