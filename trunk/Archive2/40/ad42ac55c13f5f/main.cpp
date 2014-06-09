#include <chrono>
#include <iostream>
#include <string>

#define OUTPUT


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

void Standard(int i1, int i2) {
    int digSum = 0;
    int proSum = 1;
    
    for (; i1 < i2; i1++) {
        
        auto str = std::to_string(i1);
        
        for (const auto& e : str) {
            digSum += e - '0';
            proSum *= e - '0';
        }
    }
}


int main() {
    std::chrono::time_point<std::chrono::system_clock> start1, end1;
    std::chrono::time_point<std::chrono::system_clock> start2, end2;
    start1 = std::chrono::system_clock::now();
    
    //for (int i = 0; i < 10000; i++) {
        Incremental(351, 362);
    //}
    end1 = std::chrono::system_clock::now();
 
    std::chrono::duration<double> elapsed_seconds1 = end1 - start1;
    
    start2 = std::chrono::system_clock::now();
    //for (int i = 0; i < 10000; i++) {
    //    Standard(351, 360);
    //}
    end2 = std::chrono::system_clock::now();
    
    std::chrono::duration<double> elapsed_seconds2 = end2 - start2;
    
    std::time_t end_time = std::chrono::system_clock::to_time_t(end2);
 
    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time(incremental): " << elapsed_seconds1.count() << "s\n"
              << "elapsed time(repeated)   : " << elapsed_seconds2.count() << "s\n";
}