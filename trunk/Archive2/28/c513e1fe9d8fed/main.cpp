#include <iostream>
#include <vector>

int main() {

    std::vector<int> vector;
    std::string str = "abc";

    {unsigned i = -1; for (char & c : str) {++i;
        if (c == 'b') vector.push_back(i);
    }}
  
  	std::cout << "Value: " << vector.front() << std::endl;
}