#include <fstream>
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
template<typename...T>
inline void Writes(ostream& s, T...t);
template<>
inline void Writes<>(ostream& s){}
template<typename First, typename...Rest>
inline void Writes(ostream& s, First fr, Rest...r) {
    s<<(fr);
    Writes(s, r...);
}

int main() {
    f(cout, 1, 1.1f, 2.2, 'a');
std::fstream s("file.dat");
s.clear();
s.exceptions(std::fstream::failbit);
s<<"h w";

}
