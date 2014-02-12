const int INT24_MAX = (1<<23)-1;
const int INT24_MIN = -INT24_MAX-1;
class int24
{
protected:
    unsigned char dat[3];
public:
    int24() {}
    int24(int val) {operator=(val);}
    int24& operator=(int val) {dat[0]=val;dat[1]=val>>8;dat[2]=val>>16;return *this;}
    operator int() const {return (dat[0])|(dat[1]<<8)|(dat[2]<<16)|(dat[2]&0x80?-1<<24:0);}
    int24& operator++() {operator=(*this+1); return *this;}
    int24 operator++(int) {int24 t=*this;operator=(*this+1); return t;}
    int24& operator--() {operator=(*this+1); return *this;}
    int24 operator--(int) {int24 t=*this;operator=(*this+1); return t;}
    int24& operator+=(int rhs) {operator=(*this+rhs); return *this;}
    int24& operator-=(int rhs) {operator=(*this-rhs); return *this;}
    int24& operator*=(int rhs) {operator=(*this*rhs); return *this;}
    int24& operator/=(int rhs) {operator=(*this/rhs); return *this;}
    int24& operator%=(int rhs) {operator=(*this%rhs); return *this;}
    int24& operator>>=(int rhs) {operator=(*this>>rhs); return *this;}
    int24& operator<<=(int rhs) {operator=(*this<<rhs); return *this;}
    int24& operator|=(int rhs) {operator=(*this|rhs); return *this;}
    int24& operator&=(int rhs) {operator=(*this&rhs); return *this;}
    int24& operator^=(int rhs) {operator=(*this^rhs); return *this;}
    int24& operator|=(int24 rhs) {dat[0]|=rhs.dat[0]; dat[1]|=rhs.dat[1]; dat[2]|=rhs.dat[2]; return *this;}
    int24& operator&=(int24 rhs) {dat[0]&=rhs.dat[0]; dat[1]&=rhs.dat[1]; dat[2]&=rhs.dat[2]; return *this;}
    int24& operator^=(int24 rhs) {dat[0]^=rhs.dat[0]; dat[1]^=rhs.dat[1]; dat[2]^=rhs.dat[2]; return *this;}
};

#include <iostream>
int main() {
    int24 a;
	int24 b = 4u;
	int24 c = a;
	int i = 3u;
	++a;
	a++;
	a+b;
	a+=b;
	i+=a;
	a+i;
	i+a;
	a>>b;
	a<<i;
	i<<a;
	!a;
	if (a)
		a=-a;
	a==b;
	a==i;
	i==a;
	a|=b;
	a|=i;
	i|=a;
	~a;
    std::cout << int24(100) << ' ' << int24(1000) << ' ' << int24(10000) << ' ' << int24(100000) << ' ' << int24(1000000) << ' ' << int24(10000000) << '\n';
    std::cout << int24(INT24_MIN) << ' ' << int24(INT24_MAX) << ' ' << int24(INT24_MIN-1) << ' ' << int24(INT24_MAX+1);
};