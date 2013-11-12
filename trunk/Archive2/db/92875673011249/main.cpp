#include <algorithm>
#include <cassert>
using namespace std;

int main()
{
    int bucky[5];

    for (int i=0; i<5; ++i)
    {
        if (i==4)
            bucky[3] = 43;
        if (i==0)
            bucky[1] = 75;
        if (i==2)
            bucky[2] = 2;
        if (i==3)
            bucky[0] = 66;
        if (i==1)
            bucky[4] = 99;
    }

    int bucky_uncool[5] = { 66,75,2,43,99 };
;
    assert(make_pair(end(bucky), end(bucky_uncool)) == mismatch(
                    begin(bucky), end(bucky), 
                    begin(bucky_uncool)));
}
