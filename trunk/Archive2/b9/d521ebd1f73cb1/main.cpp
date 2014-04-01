#include <iostream>

using namespace std;

template <class T1>
T1 minelement (T1 first , T1 last)
{
    if (first > last)
    {
        return last;
    }
    else
    {
        return first;
    }
}
template <class T2>
T2 maxelement (T2 first , T2 last)
{
    if (first < last)
    {
        return last;
    }
    else
    {
        return first;
    }
}
int main ()
{
    cout <<"Smallest is : " << minelement(33, 43)<< endl;
    cout <<"Max is : " << maxelement(39, 29) << endl;
    cout <<"Smallest is : " << minelement(33.39, 43.2) << endl;
    cout <<"Max is : " << maxelement(39.2, 29.3) << endl;
}