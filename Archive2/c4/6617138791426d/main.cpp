#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main()
{
    std::stringstream file("\
17 24 1 8 15\n\
23 5 7 14 16\n\
4 6 13 20 22\n\
10 12 19 21 3\n\
11 18 25 2 9\n");

    std::string line;
    getline(file, line);
    file.seekg(0, file.beg);
    
    auto n = std::count(line.begin(), line.end(), ' ');
    std::vector< std::vector<int> > grid(n+1, std::vector<int>(n+1));
    for(auto i = 0; i < n+1; i++) {
        for(auto j = 0; j < n+1; j++) {
            file >> grid[i][j];
            std::cout << grid[i][j] << " ";
        }
        std::cout << "\n";
    }
    
    return 0;
}
