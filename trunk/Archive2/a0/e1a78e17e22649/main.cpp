#include<math.h>
using namespace std;

int main(){
double dist(double array1[4], double array2[4]);
{
    double Sum;
    double distance;

    for(int i=0;i<4;i++)
    {
        cout<<"Enter value of first coordinate";
        cin >> array1[i];
        cout<<"Enter value of second coordinate";
        cin >> array2[i];

        Sum = Sum + pow((array1[i]-array2[i]),2.0);
        distance = sqrt(Sum);
    }
        cout << "DISTANCE: " << distance;
    return distance;
}
}