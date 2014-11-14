#include <iostream>
using namespace std;

int main() {

bool x;
int y;

x = 0;
y = true;

while (y != 6) {

x = ! x;
y = y + 1;

if (x) {
cout << (y) ;
}
else { 
cout << (x);
}
}

system ("pause");
return(0);
}
