#include <iostream>
#include <map>
#include <string>

using namespace std;

void fun ( map<string, map<string, int> > &m1, map<string, map<string, int> > &m2) {
    m1["abc"]["xyz"] = 1;
}

int main() {
    map<string, map<string, int> > m[10];
    fun(m[0], m[1]);
    cout << m[0]["abc"]["xyz"] << endl;
}
