#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    int A[10] = {0};
    A[10] = 99;
    
    for (int i = 0; i <15; i++){
    A[i] = i;
    cout << A[i] << endl;
    }
    
}
