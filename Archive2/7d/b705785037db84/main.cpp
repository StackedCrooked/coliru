#include <fstream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    std::fstream fin("input.txt");
    
    std::vector<std::string> lines;
    std::string line;
    while(getline(fin, line)) {
        lines.push_back(line);
    }
    
    return 0;
}
