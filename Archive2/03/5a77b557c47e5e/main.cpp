#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vector)
{
    long size = vector.size();
    os << "vector[" << size << "] ";
    for(size_t i = 0; i < size; ++i)
        os << vector[i] << " ";
    return os;
}

int main()
{
    std::vector<int> input;

    int line = 0;
    std::ifstream source("source.txt");
    if (source.is_open()) {
		while (source.good()) {
            source >> line;
            input.push_back(line);
		}
		source.close();
	}
	else {
		std::cout << "Unable to open file" << std::endl;
        return 1;
	}
    
    std::cout << "input: " << input << std::endl;
    
    int sum = std::accumulate(input.begin(), input.end(), 0);
    
    std::cout << "sum: " << sum << std::endl;
    
    return 0;
}
