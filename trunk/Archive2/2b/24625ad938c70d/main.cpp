#include<bits/stdc++.h>
using namespace std;

int main(){

    int arr[3];
    for(int i=0;i<3;++i){
        int x;  
        cin >> x;
        arr[x]; 
    }
    sort(arr, arr + 3, greater<int>());

    cout << arr[0] << endl;
}