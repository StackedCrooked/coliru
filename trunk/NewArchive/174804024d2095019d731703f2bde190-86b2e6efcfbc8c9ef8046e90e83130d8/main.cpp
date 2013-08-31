#include<iostream>
#include<algorithm>
#include<string>

#include <utility>

// struct data{
//     int x,y;
// };

using data = std::pair<int, int>;

bool operator <(const data &a1, const data &a2){
    // return a1.x<a2.x;
    return a1.first < a2.first;
}

bool operator <(const data &a1, const int &a2){
    return a1.first < a2;
}

bool operator <(const int &a1, const data &a2){
    return a1 < a2.first;
}

using namespace std;
int main(){
    // struct data A[1000];
    data A[1000];
    for(int i=0;i<1000;i++){
        // A[i].x = rand() % 50;
        // A[i].y = rand() % 50;
        A[i].first = rand() % 50;
        A[i].second = rand() % 50;
    }
    sort(A,A+1000);
    int B = 20;
    cout << lower_bound(A,A+1000,B) -A;
}