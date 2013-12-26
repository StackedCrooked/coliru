#include <iostream>

using namespace std;

int main(){
    char h[8] = {'a', 'b', 'c', 'd','e','f', 'g', 'h'};
    int  pessimistic[8] = {8, 9, 10, 11, 12, 13, 14, 15};
    int restless[8] = {16, 17, 18, 19, 20, 21, 22, 23};
    
    for(int a=0; a < 8; a++)
        cout << h[a] << endl;

    for(int b=0; b < 8; b++)
        cout << pessimistic[b] << endl;

    for(int c=0; c < 8; c++)
        cout << restless[c] << endl;
}