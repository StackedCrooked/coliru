#include <iostream>
#include <vector>

using std::vector;
using std::cin;
using std::cout;
using std::endl;

int main(){
vector<int> ivec;
int i1, cnt = 0;

while (cin >> i1){ // while loop for input into ivec.
    ++cnt;
    if (cnt <= 10){ ivec.push_back(i1); } //limits the vector to 10 elements.
}

for (vector<int>::iterator a1 = ivec.begin(); a1 != ivec.end() ; ++a1){ // as long as a1 is != to ivec.end execute for loop.
    (*a1) = *a1 * 2; //multiplies varible stored in a1 by 2.
    cout << *a1 << " "; // outputs the result of muliplication.
}

cout << endl;

return 0;
}
