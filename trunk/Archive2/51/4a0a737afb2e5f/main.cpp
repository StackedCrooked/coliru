#include <cstring>

const int INT24_MAX = 1<<24;
const int INT24_MIN = 0;

class int24
{
protected:
    unsigned char dat[3];
public:
    int24() {}
    int24(int val) {operator=(val);}
    int24& operator=(int val) {memcpy(dat,&val,3);return *this;}
    operator int() const {int val=0;memcpy(&val,&dat,3); return val;}
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
};