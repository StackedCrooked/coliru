#include <vector>
#include <iterator>
#include <iostream>

using namespace std;
int main()
{
    std::vector<int> vector1{1,2,3,4,5,6,7,8};
    std::vector<int> vector2;
    
    for(auto it = std::next(vector1.begin()); it != std::prev(vector1.end()); ++it) {
        vector2.push_back((*std::prev(it) + *it + *std::next(it)) / 3);
    }
    for(int i : vector2){
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}
