#include <iostream>

struct {int d, m, y; } today = {22, 3, 2014};

class Date {
    int d, m, y;
public:
    Date(int dd =0, int mm =0, int yy =0);
    int Day() const { return d; }
    int Month() const { return m; }
    int Year() const { return y; }
};

Date::Date(int dd, int mm, int yy)
{
    d = dd ? dd : today .d;
    m = mm ? mm : today .m;
    y = yy ? yy : today.y;
}

int main()
{
    Date d;
    std::cout << d.Day() << '/' <<  d.Month() << '/' << d.Year() << '\n';
}