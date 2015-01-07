#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

bool checkPerm(unsigned long long x){
    vector<unsigned long long> tester;
    string strx = to_string(x);
    int sizestrx = strx.size();
    int counter = 1;
    cout << "x is " << strx << " and its permutations are ";
    while (next_permutation(strx.begin(), strx.end())){
        cout << strx << " ";
        unsigned long long stoipermstrx = stoi(strx);
        tester.push_back(stoipermstrx);
    }
    cout << endl;
    int sizetester = tester.size();
    for (int j = 2; j <= 6; j++){
        cout << "j is " << j << ' ';
        for (int k = 0; k < sizetester; k++){
            if (j*x == tester[k]){
                cout << "counter increased because x, counter " << x << " " << counter << endl;
                counter++;
                if (counter == 6){
                    cout << "Number is " << x << endl;
                    return true;
                }
                break;
            }
        }
        //cout << "Number " << x << " failed" << endl;
        return false;
    }
    return true;
}

int main(){
    unsigned long long x = 1;
    for (double i = 0; ; i++){
        cout << i << endl;
        while (x < 1.67*pow(10, i)){
            if (i == 5)
                cout << x << endl;
            if (checkPerm(x)){
                cin.get();
            }
            x++;
        }
        x = pow(10, (i + 1));
    }
}