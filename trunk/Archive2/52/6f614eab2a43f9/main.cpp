#include <iostream>

using namespace std;

template <bool condition, class Then, class Else>
struct IF
{
    typedef Then RET;
};

template <class Then, class Else>
struct IF<false, Then, Else>
{
    typedef Else RET;
};


int main()
{
    // if sizeof(int) < sizeof(long) then use long else use int
    IF<( sizeof(int)>sizeof(float) ), float, int >::RET  i = 3.2;

    cout << i << endl;

    return 0;
}