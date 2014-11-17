#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    
    int evens = 0;
    struct not_a_lambda {
        int& evens;
        
        void operator()(int n) const
        {
            if (n % 2 == 0) {
                ++evens;
            }
        }
    };
    std::for_each(v.begin(), v.end(), not_a_lambda { evens });

    std::cout << "There are " << evens
        << " even numbers in the vector.\n";

    evens = 0;
    std::for_each(v.begin(), v.end(),
            [&evens](int n)
            {
                if (n % 2 == 0) {
                    ++evens;
                }
            }
    );

    std::cout << "There are " << evens
        << " even numbers in the vector.\n";
}
