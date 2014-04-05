#include <iostream>
#include <stdexcept>
#include <sstream>

class Fraction
{
private:
    int num,den;

    int GCD(int x, int y) const{
        if(y == 0) return x;
        return GCD(y,x%y);
    }

public:
    Fraction(int x = 0,int y = 1){
        num = x;
        if(y==0) throw std::overflow_error("Divide by zero exception");
        den = y;
    }
    Fraction(int x){
        num = x;
        den = 1;
    }
    Fraction(const Fraction& x){
        num = x.getNum();
        den = x.getDen();
    }

    void normalize(){
        int factor = GCD(num,den);
        setNum(num/factor);
        setDen(den/factor);
    }

    void setNum(int x){
        num = x;
    }
    void setDen(int y){
        if(y==0) throw std::overflow_error("Divide by zero exception");
        den = y;
    }

    int getNum() const{
        return num;
    }
    int getDen() const{
        return den;
    }

    Fraction& operator=(const Fraction& rhs){
        if(this == &rhs)
               return *this;
        num = rhs.getNum();
        den = rhs.getDen();
        return *this;
    }
    Fraction operator+(const Fraction& x) const{
        Fraction ret;
        ret.setNum(getNum()*x.getDen() + x.getNum()*getDen());
        ret.setDen(getDen()*x.getDen());
        ret.normalize();
        return ret;
    }
    Fraction operator-(const Fraction& y) const{
        Fraction yCopy = y;
        yCopy.setNum(yCopy.getNum()*-1);
        return *this + yCopy;
    }
    Fraction operator*(const Fraction& y) const{
        Fraction ret;
        ret.setNum(getNum() * y.getNum());
        ret.setDen(getDen() * y.getDen());
        ret.normalize();
        return ret;
    }
    Fraction operator/(const Fraction& y) const{
        return *this * (~y);
    }
    Fraction operator~() const{
        Fraction ret(getDen(),getNum());
        ret.normalize();
        return ret;
    }


    bool operator<(Fraction y) const{
        Fraction x;
        x.setNum(getNum()*y.getDen());
        y.setNum(y.getNum()*getDen());
        if(x.getNum() < y.getNum()) return true;
        return false;
    }
    bool operator>(Fraction y) const{
        Fraction x;
        x.setNum(getNum()*y.getDen());
        y.setNum(y.getNum()*getDen());
        if(x.getNum() > y.getNum()) return true;
        return false;
    }
    bool operator==(Fraction y) const{
        Fraction x;
        x.setNum(getNum()*y.getDen());
        y.setNum(y.getNum()*getDen());
        if(x.getNum() == y.getNum()) return true;
        return false;
    }
    bool operator!=(Fraction y) const{
        return !(*this==y);
    }
    bool operator<=(Fraction y) const{
        return !(*this>y);
    }
    bool operator>=(Fraction y) const{
        return !(*this<y);
    }

    friend std::ostream& operator<<(std::ostream& os,Fraction x){
        os << x.getNum() << "/" << x.getDen();
        return os;
    }
    friend std::istream& operator>>(std::istream& is,Fraction& x){
        //Read input
        std::string input;
        is >> input;

        //Organize it
        std::stringstream numChar;
        numChar << input.substr(0,input.find('/'));
        std::stringstream denChar;
        denChar << input.substr(input.find('/')+1,input.length());

        //Put it where needs be
        int n, d;
        numChar >> n;
        denChar >> d;
        x.setNum(n);
        x.setDen(d);

        return is;
    }

    operator double() const{
        double ans = ((double)getNum())/getDen();
        return ans;
    }
};
