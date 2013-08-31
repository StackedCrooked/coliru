#include <iostream>

using std::cout;
using std::endl;

class time
{
public:
time();
void settime (int, int, int);
void printuniversal ();
void printstandard ();
private:
int hour;
int minute;
int second;
};

time::time()
{
hour = minute = second = 0;
}

void time::settime (int h, int m, int s)
{
hour = (h >= 0 && h < 24) ? h : 0;
minute = (m >= 0 && m < 60) ? m : 0;
second = (s >= 0 && s < 60) ? s : 0;
}

void time::printuniversal()
{
cout << hour << ":" << minute << ":" << second << ":" << endl;
}

void time::printstandard()
{
cout << ((hour == 0 || hour == 12) ? 12 : hour % 12) << ":" << minute << ":" << second                             << (hour < 12 ? "AM" : "PM") << endl;
}

int main ()
{
time t;
cout << "Initial universal time: " << t.printuniversal();
cout << "\nInitial standard time: " << t.printstandard();
t.settime(13,27,6);
cout << "\nNew universal time: " << t.printuniversal();
cout << "\nNew standard time: " << t.printstandard();
return 0;
}
