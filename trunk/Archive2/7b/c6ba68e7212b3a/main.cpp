#include <iostream>
#include <fstream>

void copy2(){
    std::ofstream("Test1.mp3",std::ios::binary) << std::ifstream("Test.mp3",std::ios::binary);
}

int main() {
    
}