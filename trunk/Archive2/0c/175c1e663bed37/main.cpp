 #include <iostream>
using namespace std;

int f ();
int g();

int main () {
    cout << f() << f() << g() << endl;
}

int f () {
    static int zahl = 3;
    return ++zahl;
}

int g () {
    return f();
}