#include <iostream>
#include <string>

class DayOfYear
{
 public:
    DayOfYear(int d) : day{d} {}
    void print();
    static std::string month;
    DayOfYear();
    DayOfYear(std::string m, int d);
    DayOfYear operator++(int);
    DayOfYear operator--();
    int day;
};


DayOfYear DayOfYear::operator++(int)
{
    DayOfYear temp = *this;    
    if(day == 365)
    {day = 1;}
    else
    {day ++;}
    return temp;
}

int main() {
    DayOfYear d{365};
    d++;
    std::cout << d.day;
}