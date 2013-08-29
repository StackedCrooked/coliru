#include <string>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <unistd.h>

class Date {
private:
    std::tm* timeData;
public:
    Date() {
        auto t = std::time(0);
        timeData = std::localtime(&t);
    }
    void format(const std::string& str) {
        for(size_t i = 0; i < str.length(); ++i) {
            if(str[i] == '%') {
                if(str[i+1] == 'l') {
                    auto t = std::chrono::system_clock::now();
                    auto k = std::chrono::system_clock::from_time_t(std::mktime(timeData));
                    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t - k).count();
                }
                if(str[i+1] == 's')
                    std::cout << std::setw(2) << std::setfill('0') << timeData->tm_sec;
                if(str[i+1] == 'm')
                    std::cout << std::setw(2) << std::setfill('0') << timeData->tm_min;
                if(str[i+1] == 'h') {
                    std::cout << (timeData->tm_hour >= 1 ? timeData->tm_hour % 12 : 1);
                }
                if(str[i+1] == 'H')
                    std::cout << timeData->tm_hour;
                if(str[i+1] == 'c') {
                    if(timeData->tm_hour < 12)
                        std::cout << "AM";
                    else
                        std::cout << "PM";
                }
                if(str[i+1] == 'd')
                    std::cout << timeData->tm_mday;
                if(str[i+1] == 'M')
                    std::cout << timeData->tm_mon + 1;
                if(str[i+1] == 'y')
                    std::cout << timeData->tm_year + 1900;
                ++i;
            }
            else {
                std::cout << str[i];
            }
        }
        
    }
};

int main() {
    Date k;
    sleep(2);
    k.format("%h:%m:%s.%l %M/%d/%y");
}