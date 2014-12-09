#include <iostream>
using namespace std;

class time
{
    private:

    int sec;
    int mins;
    int hours;


    public:

    void setSeconds(int x)
    {
        sec = x;
    }

    int getSeconds()
    {
        return sec;
    }

};

int main()
{
    class time to;
    to.setSeconds(10000000);
    cout << to.getSeconds() << endl;


    return 0;
}