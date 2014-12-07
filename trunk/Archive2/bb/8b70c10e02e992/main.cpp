#include <iostream>
using namespace std;

int main()
{
    int answer[5];
    int guess[5];
    
    for (int i=0; i<5; i++){
        guess[i]=0;
        answer[i]=-1;
    }//for
    cout << guess[0] << answer[0];
    return 0;
}