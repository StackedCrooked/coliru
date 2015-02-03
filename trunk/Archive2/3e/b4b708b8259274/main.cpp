#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>

int main()
{
    std::vector<int> exercise;
    exercise.push_back(1);
    exercise.push_back(2);
    exercise.push_back(3);
    exercise.push_back(2);
    exercise.push_back(1);
    exercise.push_back(4);
    exercise.push_back(5);
    
    std::copy(exercise.begin(), exercise.end(), std::ostream_iterator<int>(std::cout, " "));
    
    for(auto const& val : exercise)
    {
        std::cout << val << " ";
    }
}
