#include <chrono>
#include <iostream>
#include <string>

int main() {
    std::chrono::time_point<std::chrono::system_clock> start, end, start2, end2;
    start = std::chrono::system_clock::now();
    
    std::string c = "Hallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testz";
    for (auto& e : c) {
        if (e == 'z') {
            break;    
        }
    }
    
        
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    
    const auto costWithPointers = elapsed_seconds.count();

    start2 = std::chrono::system_clock::now();
    
    const char* tekst = "Hallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testHallo daar dit is een|testz";
    for (; *tekst; ++tekst) {
        if (*tekst == 'z') {
            break;    
        }
    }
        
    end2 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds2 = end2 - start2;

    const auto costWithout = elapsed_seconds2.count();
    
    
    std::cout << "Met pointers : " << costWithPointers << " seconde" << std::endl;
    std::cout << "Leesbare code: " << costWithout << " seconde" << std::endl;

}