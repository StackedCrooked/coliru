#include <iostream>
#include <boost/rational.hpp>
#include <boost/multiprecision/cpp_int.hpp>

template < typename INTEGER_TYPE = int > using rational = boost::rational<INTEGER_TYPE> ;
using namespace boost::multiprecision;
using namespace std;

uint512_t mul_inv(uint512_t a, uint512_t b)
{
    uint512_t b0 = b, t, q;
	uint512_t x0 = 0, x1 = 1;
	if (b == 1) return 1;
	while (a > 1) {
		q = a / b;
		t = b, b = a % b, a = t;
		t = x0, x0 = x1 - q * x0, x1 = t;
	}
	if (x1 < 0) x1 += b0;
	return x1;
}


int main()
{
    uint512_t gx1("55066263022277343669578718895168534326250603453777594175500187360389116729240");
    uint512_t gy1("32670510020758816978083085130507043184471273380659243275938904335757337482424");
    uint512_t gx2("89565891926547004231252920425935692360644145829622209833684329913297188986597");
    uint512_t gy2("12158399299693830322967808612713398636155367887041628176798871954788371653930");
    uint512_t p("115792089237316195423570985008687907853269984665640564039457584007908834671663");
    uint512_t x2("1");
    uint512_t ph1("1");
    ph1 = (gy1 - gy2) * (mul_inv((gx1-gx2), p));
    ph1 %= p;
    x2 = (((ph1 ^ 2)) - ((gx1 + gx2))%p);
    		cout << "next is x2" << endl;
			cout << x2 << endl;
            cout << endl;
    cout << "Supposed to be 112711660439710606056748659173929673102114977341539408544630613555209775888121" << endl;
    return 0;
}
