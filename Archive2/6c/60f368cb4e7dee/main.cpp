#include <iostream>
using std::cout;
using std::cin;

int main(){
    int p[10], w[10], n,i,j;
    cout << "Maximum elements: \n"; cin >> n;
    for (i = 0; i < n; i++){
        cout << "Enter " << i << "-nd element\n"; cin >> p[i];
    }
    j = 0;

    for (i = 0; i < n; i++){
        if (p[i] > 0){
            w[j] = p[i];
            j++;
        }
    }

    for (int k = 0; k < j; k++){
        cout << w[k] << '\n';
    }
}