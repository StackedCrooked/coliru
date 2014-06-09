#include <chrono>
#include <iostream>
#include <string>

#define OUTPUTN


void Incremental(int t1, int t2) {
    //Digit computing    
    int digSum = 0;
    int proSum = 1;
    
    auto str = std::to_string(t1);
    
    for (const auto& e : str) {
        digSum += e - '0';
        proSum *= e - '0';
    }
#ifdef OUTPUT
    std::cout << "Found for number: " << t1 << std::endl 
        << "  Sum = " << (digSum) << std::endl
        << "  Pro = " << (proSum) << std::endl;

    
    int oldT = t1;
#endif
    for (; t1 < t2;) {
        t1++;
        
#ifdef OUTPUT        
        
       
        std::cout << "Found for number: " << t1 << std::endl 
            << "  Sum = " << (digSum + (t1 - oldT)) << std::endl
            << "  Pro = " << (proSum * (t1 - oldT + 1)) << std::endl;
#endif
    }
}


int main() {
    std::chrono::time_point<std::chrono::system_clock> start1, end1;
    start1 = std::chrono::system_clock::now();
    
    Incremental(351, 362);
    
    end1 = std::chrono::system_clock::now();
 
    std::chrono::duration<double> elapsed_seconds1 = end1 - start1;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end1);
 
    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time(incremental): " << elapsed_seconds1.count() << "s\n";
}