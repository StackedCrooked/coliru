//============================================================================
// Name        : wer.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
 
#include <iostream>
using namespace std;
 
int main()
{
    int a, b, c, punkty = 0;
    cin >> a >> b >> c;
    for (int i = 0; i < c; ++i)
    {
        int r;
        cin >> r;
        if (r >=a && r <= b)
        {
            punkty = 0;
        }
        else
        {
            if (r < a)
            {
                punkty = punkty + a - r;
            }
            else 
                if (r > b) 
                {
                    punkty = punkty + r - b;
            }
        }
    }
 
return 0;
}