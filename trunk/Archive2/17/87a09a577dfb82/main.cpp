#include <iostream>
#include <sstream>
#include <locale>
#include <iomanip>
#include <ctime>

int main() {
    std::tm t;
    std::istringstream ss("1:01:01");
    ss >> std::get_time(&t, "%H:%M:%S");
    std::cout << "Total seconds: " 
              << t.tm_hour * 3600 + t.tm_min * 60 + t.tm_sec 
              << std::endl;
}