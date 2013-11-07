#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>
 
int main()
{
    std::vector<int> from_vector;
    for (int i = 0; i < 10; i++) {
        from_vector.push_back(i);
    }
 
    std::vector<int> to_vector;
 
    std::copy_if(from_vector.begin(), from_vector.end(), std::back_inserter(to_vector)
        , [](const int & v) { return v % 2 == 1; }
    );
 
    std::cout << "to_vector contains: ";
    std::copy(to_vector.begin(), to_vector.end(), 
              std::ostream_iterator<int>(std::cout, " "));
              
    std::cout << std::endl;
}