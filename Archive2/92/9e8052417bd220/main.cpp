#include <vector>
#include <iostream>
#include <algorithm>

bool comp (int i, int j) { return (i > j); }

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
    
    std::ifstream backstory ("backstory.txt");
    if (backstory.is_open()) {
		while (backstory.good())
		{
			getline(backstory,line);
            x.push_back(line);
		}
		backstory.close();
	}
	else {
		std::cout << "Unable to open file" << std::endl;
        return 1;
	}
    
    
    
    return 0;
}
