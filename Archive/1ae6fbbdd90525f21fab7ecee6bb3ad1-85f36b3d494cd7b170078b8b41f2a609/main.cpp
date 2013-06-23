#include <iostream>

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
}

void time::printstandard()
{
}

int main ()
{
time t;
t.settime(13,27,6);

return 0;
}
