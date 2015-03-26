#include    <iostream>
#include    <vector>

using namespace std;

int foo(vector<float> &lines){
    lines[1] = 2.5;
    lines[2] = 1.2;
    return 0;
}

int main(){
    vector<float> lines(3);
    lines[0] = 5.4;
    foo(lines);
    cout << lines[0] << " " << lines[1] << " " << lines[2] << endl;
    return 0;
}