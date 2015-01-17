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
11 18 25 2 9\n\
1 2 3\n\
4 5 6\n\
7 8 9\n");
    
    std::string line;
    while(file) {
        auto filePosition = file.tellg();
        getline(file, line);
        file.seekg(filePosition, file.beg);
        
        auto n = std::count(line.begin(), line.end(), ' ');
        if(n > 0) {
            std::cout << "Square Size: " << n << "*" << n << "\n";
            std::vector< std::vector<int> > grid(n+1, std::vector<int>(n+1));
            for(auto i = 0; i < n+1; i++) {
                for(auto j = 0; j < n+1; j++) {
                    file >> grid[i][j];
                    std::cout << grid[i][j] << " ";
                }
                std::cout << "\n";
            }
        }
        std::cout << "\n";
        file.ignore(2, '\n');
    }
    
    return 0;
}
