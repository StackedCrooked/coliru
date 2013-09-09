#include <vector>
#include <iostream>
#include <sstream>
#include <iterator>
#include <fstream>

std::vector<std::vector<int>> get_data(std::istream& in) {
    using i_it = std::istream_iterator<int>;
    std::vector<std::vector<int>> bigvec;    
    std::string line;
    while(std::getline(in, line)) {
        std::stringstream ss(std::move(line));
        bigvec.push_back(std::vector<int>());
        std::copy(i_it(in), i_it(), std::back_inserter(bigvec.back()));        
    }
    return bigvec;
}

int main(int argc, char* argv[])
{
    std::ifstream in(argv[1]);
    std::vector<std::vector<int>> bigvec = get_data(in);
    return 0;
}