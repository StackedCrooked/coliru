#include <array>
#include <vector>
#include <iostream>
#include <algorithm>


int main()
{
    std::array<int, 3> arr = {{ 1, 2, 3 }};
    std::vector<int> vecint;
    vecint.push_back(1);
    vecint.push_back(2);

    std::for_each
    (
        vecint.begin(), vecint.end(),
        [&arr](int vecvalue)
        {
            if (std::find_if(arr.begin(), arr.end(),
                             [=](int arrval) { return vecvalue == arrval; })
                != arr.end())
            {
                std::cout << "found!!! " << vecvalue << "\n";
            }
        }
    );
}