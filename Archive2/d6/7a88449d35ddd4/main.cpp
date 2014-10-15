#include <cstdlib>
#include <iostream>
    
using namespace std;
    
int main(int argc, char *argv[])
{
    int n = 0;
    float f = 0.0f;
    
    if (argc > 1) n = atoi(argv[1]);
    if (argc > 2) f = atof(argv[2]);

    cout << n << " " << f << endl;

    return 0;
}