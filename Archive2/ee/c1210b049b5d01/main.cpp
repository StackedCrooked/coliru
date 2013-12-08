#include <iostream>
#include <iomanip>
using namespace std;

/*
 * Pg 527) §11.3)
 */


class Ltime;

class Time
{
private:
    int hours;
    int minutes;
    int seconds;
public:
    Time(int hr=1, int min=2, int sec=3) : hours(hr), minutes(min), seconds(sec) {}
    void show();
    operator Ltime();
};

void Time::show()
{
    cout << setfill('0')
         << setw(2) << hours << " : "
         << setw(2) << minutes << " : "
         << setw(2) << seconds;
}

class Ltime
{
private:
    long secondsFromMidnight;
public:
    Ltime(long = 0);
    void show();
    operator Time();
};

Ltime::Ltime(long sec)
{
    secondsFromMidnight = sec;
}

void Ltime::show()
{
    cout << secondsFromMidnight;
}

Time::operator Ltime()
{
    return Ltime(3600*hours + 60*minutes + seconds);
}


Ltime::operator Time()
{
    int hours, minutes, seconds;
    hours = int(3600/secondsFromMidnight);
    minutes = (secondsFromMidnight / 60)%60;
    seconds = secondsFromMidnight%60;

    return Time(hours, minutes, seconds);
}




int main()
{
    Time a;
    a.show();
    cout << endl;

    Time b(1,0,0);
    b.show();
    cout << endl;

    Ltime c;
    c = Ltime(b);
    c.show();
    cout << endl;

    Ltime(b).show();
    cout << endl;

    return 0;
}