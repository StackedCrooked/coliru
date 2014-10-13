#include <iostream>
#include <vector>
using namespace std;

int main() {
    const int ARRAYSIZE = 20;
    bool number = false;
    char array3[ARRAYSIZE] = {'1','2','3','4','5','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0',};
//    char array3[ARRAYSIZE] = {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0',};
    int sum = 0;
    int i = 1;//0;
    do {
        if(array3[ARRAYSIZE-i] != '0')      // heeeeeeeeeeeeeeeeelp
            number = false;
        else
            number = true;
        sum = i++;
       // cout << "array3[ARRAYSIZE-i] == " << array3[ARRAYSIZE-i] << ", sum = " << sum << endl;
    } while(number == true && i <= ARRAYSIZE);

   // cout << sum << endl;
    for(sum; sum <= ARRAYSIZE; sum++){          // Outputs all the terms
        cout << array3[ARRAYSIZE-sum];
    }
}