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

class alg
{
public:
    template<class T>
    static void reGroupArray(std::vector<T>& data)
    {
        int temp;
        size_t i = 0;
        size_t size = data.size();
        while (i < size) {
            if (data[i] > 0) {
                if (data[i]<data[i-1]) {
                    temp = data[i];
                    data[i] = data[i-1];
                    data[i-1] = temp;
                    if (i>1) {
                        i-=2;
                    }
                }
            }
            i++;
        }
    }
    
};

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
    
    auto reGroupArrayCopy(input);
    alg::reGroupArray(reGroupArrayCopy);
    
    std::cout << "Re group array: " << reGroupArrayCopy << std::endl;
    
    return 0;
}
