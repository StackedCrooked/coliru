#include <iostream>

using namespace std;
float najmal (float a, float b, float c)
{
 float min;
 min=a;
 if (b<min)
  min=b;
 if (c<min)
  min=c;
 return min;
}
int main()
{
    float x, y, z, najmaliot;
    cout << "Vnesi go: "<<endl;
    cin>>x;
    cout << "Vnesi go: "<<endl;
    cin>>y;
    cout << "Vnesi go: "<<endl;
    cin>>z;
    najmaliot=najmal(x,y,z);
    cout<<"Od broevite: "<<x<<" , "<<y<<" , "<<z<<" najmaliot e: "<<najmaliot<<endl;
    return 0;
}
