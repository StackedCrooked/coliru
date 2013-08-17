#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
int z = 0;
string name[] = {"john", "bobby", "dear", "test1", "catherine", "nomi", "shinta", "martin", "abe", "may", "zeno", "zack", "angeal", "gabby"};

sort(begin(name),end(name));

for(auto n: name){
    cout << n << endl;
}
        return 0;

}