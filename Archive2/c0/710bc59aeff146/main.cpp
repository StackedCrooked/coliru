#include <iostream>

using namespace std;
char nomes[]={};
int numpessoas;
int main() {
    cout << "Quantas pessoas queres registar?\n";
    pede:
    cin >> numpessoas;
    if (numpessoas < 1) {
        goto pede;
    }
    else {
        for (int i = 1; i<= numpessoas; i++){
            cout << i << "º nome\n";
            cin << nomes[i];
        }
    }
}