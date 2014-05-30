#include <iostream>
#include <chrono>
#include <string>



int main() {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    for (int i = 0; i < 10000000; i++) {
        int num = 1120390318;
        //int res = 0;
        int sum = 0;
        while(num != 0) {
            //int rem = ;
            num = num / 10;
            sum = sum + (num % 10);
        }
    }
    
    end = std::chrono::system_clock::now();
 
    std::chrono::duration<double> elapsed_seconds1 = end - start;
    start = std::chrono::system_clock::now();
    
    for (int i = 0; i < 10000000; i++) {
        int num = 1120390318;
        int sum = 0;
        for (auto c : std::to_string(num)) {
            sum += c - '0';
        }
    }
    
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds2 = end - start;
    
    std::cout << "Modulo: " << elapsed_seconds1.count() << " seconds" << std::endl;
    std::cout << "String: " << elapsed_seconds2.count() << " seconds" << std::endl;
        


    
    
}
