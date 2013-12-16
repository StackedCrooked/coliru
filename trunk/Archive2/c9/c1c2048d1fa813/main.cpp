#include <iostream>
#include <vector>

int main() {
    int dim;
    std::cout << "Dimension: ";
    std::cin >> dim;
    
    std::cout << std::endl;
    
    //aka ein dim-elemtiger Container von Containern für dim ints initialisiert mit 1
    std::vector<std::vector<int>> matrix(dim, std::vector<int>(dim, 1));
    
    for(const auto & row : matrix) {
        for(const auto & elem : row)
            std::cout << elem << " ";
        std::cout << std::endl;
    }
    
    std::cout << std::endl;
    
    //das kann man so sogar direkt nach WA kopieren:
    //http://www.wolframalpha.com/input/?i=%7B%7B1%2C2%2C3%2C4%2C5%7D%2C%7B5%2C4%2C3%2C2%2C1%7D%2C%7B1%2C2%2C3%2C4%2C5%7D%7D
    std::vector<std::vector<int>> matrix2 = {
         {1,2,3,4,5}
        ,{5,4,3,2,1}
        ,{1,2,3,4,5}
    };
    
    for(const auto & row : matrix2) {
        for(const auto & elem : row)
            std::cout << elem << " ";
        std::cout << std::endl;
    }
}
