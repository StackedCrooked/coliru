#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <map>

typedef std::chrono::time_point<std::chrono::system_clock> SystemClock;

bool isLeapYear(int year)
{
    // Not centuries
    if(!(year%1000)) {
        // Unless divisable by 400
        if(!(year%400)) {
            return true;   
        }
        return false;
    }
    // If divisable by 4
    if(!(year%4)) {
        return true;
    }
    return false;
}

enum
{
    MONDAY = 0,
    TUESDAY = 1,
    WEDNESDAY = 2,
    THURSDAY = 3,
    FRIDAY = 4,
    SATURDAY = 5,
    SUNDAY = 6
};

int main(int argv, char* argc[])
{
    // 1  31
    // 2  28/29
    // 3  31
    // 4  30
    // 5  31
    // 6  30
    // 7  31
    // 8  31
    // 9  30
    // 10 31
    // 11 30
    // 12 31
    
    // Leap year if year is divisible by 4, but no on a century unless it is divisible by 400
    // Non-leap year  365 days
    // Leap year      366 days
    
    int leapMonths[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int months[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    
    SystemClock begin = std::chrono::system_clock::now();
    int count = 0;
    int dayOfWeek = MONDAY;
    for(int i = 1900; i < 1901; i++) {
        if(isLeapYear(i)) {
            dayOfWeek = 366%7;
        }
    }
    for(int i = 1901; i <= 2000; i++) {
        //int ndays = 0;
        if(isLeapYear(i)) {
            for(int days = 0; days < 366; days++) {
                // Check if fisrt day of the month is a sunday
                if(dayOfWeek == SUNDAY) {
                    int tmp = days;
                    int counter = 0;
                    while(tmp > -1) {
                        tmp-=leapMonths[counter++];
                    }
                    // A sunday it was!
                    if(tmp == -1) {
                        std::cout << "Day " << days << " of the year " << i << std::endl;
                        count++;                        
                    }
                }
                dayOfWeek = ((dayOfWeek + 1) % 7);
            }
        }
        else {
            for(int days = 0; days < 365; days++) {
                // Check if fisrt day of the month is a sunday
                if(dayOfWeek == SUNDAY) {
                    int tmp = days;
                    int counter = 0;
                    while(tmp > -1) {
                        tmp-=months[counter++];
                    }
                    // A sunday it was!
                    if(tmp == -1) {
                        std::cout << "Day " << days << " of the year " << i << std::endl;
                        count++;                        
                    }
                }
                dayOfWeek = ((dayOfWeek + 1) % 7);                
            }
        }
    }
    std::cout << "Count: " << count << std::endl;
    std::cout << "Time: " << ((std::chrono::duration<double, std::milli>)(std::chrono::system_clock::now() - begin)).count() << " ms" << std::endl;
}
