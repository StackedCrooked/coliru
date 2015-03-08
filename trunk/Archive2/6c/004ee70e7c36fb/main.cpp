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
 
    std::vector<int> to_vector(10);
 
    std::copy(from_vector.begin(), from_vector.end(), to_vector.begin());
 
    std::cout << "to_vector содержит: ";
    std::copy(to_vector.begin(), to_vector.end(),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}