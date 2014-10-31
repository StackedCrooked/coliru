#include <vector>
using std::vector;

bool TestSwitch()
{
    vector<double> V1;
    for (double i = 0; i < 10; ++i) V1.push_back(i);
    //Switch(V1, 0, 9);
    //Switch(V1, 1, 8);
    //Switch(V1, 2, 7);
    //Switch(V1, 3, 6);
    //Switch(V1, 4, 5);
    //Switch(V1, 5, 4);
    vector<double> V2 = { 9.0, 8.0, 7.0, 6.0, 4.0, 5.0, 3.0, 2.0, 1.0, 0.0 };
    if (V1 == V2) return true;
    else return false;
}