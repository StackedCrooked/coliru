#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

void print(std::vector<std::vector<float>> const& vec)
{
    for(auto const& row : vec) {
        for(auto const& elem : row) {
            std::cout << elem << ' ';
        }
        std::cout << '\n';
    }
}

int main()
{
    std::vector<std::vector<float>> vec{{1,2,3},
                                        {4,5,6},
                                        {7,8,9}};
                                        
    print(vec);
    
    // delete column 1
    int columnIndex = 1;
    std::for_each(vec.begin(), vec.end(), 
        [&](std::vector<float>& row) {
            row.erase(std::next(row.begin(), columnIndex));
        });
        
    print(vec);
}
