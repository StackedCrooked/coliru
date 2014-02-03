#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <stdlib.h>

using namespace std;


#define AngleToRadian(Angle) {Angle*(3.14/180)}


vector<float> Position;

std::vector<int> i{5,2,3,4,2,1,7,8,0,-5};

int main()
{
    for(auto p=i.begin(); p!=i.end(); p++)
    {        
        cout<<*p<<endl;
    }
    for(auto &j : {"merhaba","dünya"})
    {
        cout<<j<<endl;
    }
    float A=AngleToRadian(90);
    cout<<A;
    
}