#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    int array[] = { 1,2,3,4 };
    int i = 0;
    int res = i + array[i++] + array[i++] *2  + array[i++] *4;
    cout << "res " << res;
}
