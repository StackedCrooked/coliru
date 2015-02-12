#include <iostream>
using namespace std;

template<typename T> void adl(T) {   cout << "T"; }

struct S { };

template<typename T> void call_adl(T t) {   adl(S());   adl(t); }

void adl(S) {   cout << "S"; }

int main () {   call_adl(S()); }