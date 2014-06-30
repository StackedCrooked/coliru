#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <iomanip>

template<typename It>
void print_list(int it, It first, It last, int l, int r, int place)
{
    std::cout << '\n';
    int const size = std::distance(first, last);
    std::cout << "Iteration ";
    std::cout << std::setfill('0') << std::setw(2) << it;
    std::cout << std::resetiosflags(std::ios_base::basefield);
    std::cout << " ";
    for(int i = 0; i <= size; ++i)
    {
        if(i == l)
            std::cout << " --> ";
        else if(i == r)
            std::cout << " <-- ";
        else if(i == place)
            std::cout << " <*> ";
        else
            std::cout << "     ";

        if(i < size)
            std::cout << *(first + i);
    }
}

template<typename It>
void bubble_sort(It first, It last)
{
    int iter = 1;
    int n = std::distance(first, last);
    do
    {
        int new_n = 0;

        for(int i = 1; i < n; ++i)
        {
            print_list(iter++, first, last, 0, n, i);

            auto& p1 = *(first + (i - 1));
            auto& p2 = *(first + i);
            if(p1 > p2)
            {
                std::swap(p1, p2);
                new_n = i;
            }
        }
        n = new_n;
    }
    while(n != 0);

    print_list(iter, first, last, -1, -1, -1);
}

template<typename It>
void cocktail_sort(It first, It last)
{
    int iter = 1;
    int l = 1;
    int r = std::distance(first, last);
    do
    {
        {
            int new_r = l;
            for(int i = l; i < r; ++i)
            {
                print_list(iter++, first, last, l-1, r, i);

                auto& p1 = *(first + (i - 1));
                auto& p2 = *(first + i);
                if(p1 > p2)
                {
                    std::swap(p1, p2);
                    new_r = i;
                }
            }
            r = new_r;
        }

        {
            int new_l = r;
            for(int i = r - 1; i >= l; --i)
            {
                print_list(iter++, first, last, l-1, r, i);

                auto& p1 = *(first + (i - 1));
                auto& p2 = *(first + i);
                if(p1 > p2)
                {
                    std::swap(p1, p2);
                    new_l = i;
                }
            }
            l = new_l + 1;
        }
    }
    while(l < r);

    print_list(iter, first, last, -1, -1, -1);
}


int main()
{
    std::random_device rd;
    std::mt19937 g(rd());

    std::vector<int> v1(10);
    std::iota(v1.begin(), v1.end(), 0);
    std::shuffle(v1.begin(), v1.end(), g);
    std::vector<int> v2(v1);
    
    std::cout << "Bubble:\n";

    bubble_sort(v1.begin(), v1.end());

    std::cout << "\n\nCocktail:\n";

    cocktail_sort(v2.begin(), v2.end());
}
