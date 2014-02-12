#include <cstring>

const int UINT24_MAX = 1<<24;
const int UINT24_MIN = 0;

class uint24
{
protected:
    unsigned char dat[3];
public:
    uint24() {}
    uint24(unsigned val) {operator=(val);}
    uint24& operator=(unsigned val) {memcpy(dat,&val,3);return *this;}
    operator unsigned() const {unsigned val=0;memcpy(&val,&dat,3); return val;}
    uint24& operator++() {operator=(*this+1); return *this;}
    uint24 operator++(int) {uint24 t=*this;operator=(*this+1); return t;}
    uint24& operator--() {operator=(*this+1); return *this;}
    uint24 operator--(int) {uint24 t=*this;operator=(*this+1); return t;}
    uint24& operator+=(unsigned rhs) {operator=(*this+rhs); return *this;}
    uint24& operator-=(unsigned rhs) {operator=(*this-rhs); return *this;}
    uint24& operator*=(unsigned rhs) {operator=(*this*rhs); return *this;}
    uint24& operator/=(unsigned rhs) {operator=(*this/rhs); return *this;}
    uint24& operator%=(unsigned rhs) {operator=(*this%rhs); return *this;}
    uint24& operator>>=(unsigned rhs) {operator=(*this>>rhs); return *this;}
    uint24& operator<<=(unsigned rhs) {operator=(*this<<rhs); return *this;}
    uint24& operator|=(unsigned rhs) {operator=(*this|rhs); return *this;}
    uint24& operator&=(unsigned rhs) {operator=(*this&rhs); return *this;}
    uint24& operator^=(unsigned rhs) {operator=(*this^rhs); return *this;}
    uint24& operator|=(uint24 rhs) {dat[0]|=rhs.dat[0]; dat[1]|=rhs.dat[1]; dat[2]|=rhs.dat[2]; return *this;}
    uint24& operator&=(uint24 rhs) {dat[0]&=rhs.dat[0]; dat[1]&=rhs.dat[1]; dat[2]&=rhs.dat[2]; return *this;}
    uint24& operator^=(uint24 rhs) {dat[0]^=rhs.dat[0]; dat[1]^=rhs.dat[1]; dat[2]^=rhs.dat[2]; return *this;}
};

int main() {
    uint24 a;
	uint24 b = 4u;
	uint24 c = a;
	unsigned i = 3u;
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