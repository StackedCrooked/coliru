#include<iostream>
using namespace std;

 template<typename S, typename T> auto produkt(const S a, const T b)->decltype(S*T)
 {
decltype(a*b) res;
res=a*b;
return res;
}
int main() {
const double pi = 3.141592;
auto e = pi;
e = 2.718281;
const auto res = produkt(pi,e);
cout << res << endl;
return 0;
}