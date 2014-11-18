#include <iostream>

using namespace std;

int a,b,j,i;
int main()
{
    cin>>a>>b;
    for(i=0; i<a; i++)
    {
        for(j=0; j<b; j++)
        {
            cout<<"X";
        }
        cout<<endl;
    }
    return 0;
}
