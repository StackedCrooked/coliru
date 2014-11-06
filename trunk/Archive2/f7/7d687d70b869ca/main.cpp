int leapYear(int year)
{
if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
    return 1;
else
    return 0;
}
long yearsToDays(int year)
{
int i;
long sum = 0;
for(i = 1900; i < year; ++i) {
    if(leapYear(i)) {
        sum += 366;
    } else
        sum += 365;
}
return sum;
}

#include <iostream>
int main() {
    for(int i=1900; i<1950; ++i) {
        std::cout << i << " - " << yearsToDays(i) << '\n';
    }
    return 0;
}