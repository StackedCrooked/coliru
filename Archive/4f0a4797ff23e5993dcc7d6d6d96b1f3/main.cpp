#include <iostream>

using namespace std;

enum DAY
{
    monday = 0,
    tuesday,
    wednesday,
    thursday,
    friday,
    saturday,
    sunday
};

bool isLeapYear(int year)
{
    if (year % 400 == 0)
        return true;
    else if (year % 100 == 0)
        return false;
    else if (year % 4 == 0)
        return true;
    else
        return false;
}

int main()
{
    int sunday_count = 0;
    bool isLeap = false;

    DAY day = tuesday;

    for (int y = 1901; y < 2000; y++)
    {
        isLeap = isLeapYear(y);

        for (int d = 0; d < (isLeapYear ? 366 : 365); d++)
        {
            if (d == 0 && day == sunday)
                sunday_count++;

            if (day == sunday)
            {
                day = monday;
            }
            else
            {
                day = static_cast<DAY>(day+1);
            }
        }
    }

    cout << sunday_count;
}
