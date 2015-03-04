#include <limits>
#include <iostream>
#include <stdint.h>
#include <cstdlib>

int solution(int N) {
// write your code in C++11

if (N<0) {
return 0;
}

int S = 1;
int newS;
int count = 0;
while(count <= N) {
newS = S;
while (newS%2 == 0) {
newS /= 2;
}
while (newS%3 == 0) {
newS /= 3;
}
if (newS == 1) {
//cout << S << endl;
count++;
}
S++;
}
return S-1;
}

int main(int argc, char** argv) {
    std::cout << solution(200) << std::endl;
}

