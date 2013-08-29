#include <fstream>
#include <iostream>

int main() {
    std::ofstream fout("file.txt");
    
    fout << R"(
        1 2 3
        4 5 6
        7 8 9
        10 11 12
        13 14 15
        16 17 18
    )";
    
    fout.close();
    std::ifstream fin("file.txt");
    
    int i0, i1, i2;
    while (fin >> i0 >> i1 >> i2) {
        fin >> i0 >> i1 >> i2;
        std::cout << i0 << ' ' << i1 << ' ' << i2 << '\n';   
    }
}