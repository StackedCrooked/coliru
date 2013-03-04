#include <iostream>

struct date
{
    int day ;
    int year ;
    int month ;
};

int main()
{
    date* myBirthday = new date();
    myBirthday->day = 5 ; 
    myBirthday->month = 6 ;
    myBirthday->year = 1993 ;
    std::cout << "My birthday is on : " << myBirthday->day << "/" << myBirthday->month << "/" << myBirthday->year ;
    return 0 ;
}