#include <iostream>
using namespace std;

template<typename...T>
void f(ostream& s, T...t);
template<>
void f<>(ostream& s) {
s<<"end"<<endl;
}
template<typename F, typename...R>
void f(ostream& s, F fr, R...r) {
s<<fr<<endl;
f(s, r...);
}

int main() {
    f(cout, 1, 1.1f, 2.2, 'a');

}
