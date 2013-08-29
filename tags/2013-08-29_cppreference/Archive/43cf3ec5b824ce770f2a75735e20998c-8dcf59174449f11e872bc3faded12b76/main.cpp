#include <locale>
#include <cstdlib>
#include <chrono>
#include <iostream>
#include <iomanip>

int main() {
    std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    std::locale::global( std::locale("en-GB") );

    std::cout << std::put_time( std::localtime( &t ), "%x" ) << std::endl;

    return 0;
}