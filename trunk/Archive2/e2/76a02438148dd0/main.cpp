#include<iostream>
#include<utility>
#include<string>
using namespace std;
using namespace std::rel_ops;

int gcd(int n, int m){
    if (n % m ==0){
        return abs(m);
 } else {
     return gcd(m, n % m);
 }
}


int lcm(int n, int m ){
   return abs((n/gcd(n,m)) * m);
}

class fraction{
public:
    fraction() {num = 0; den = 1; }
    fraction(int n) {num = n; den = 1; }
    fraction(int n, int m) { num = n; den = m;
        if(m == 0){
        num = 0; den = 0;} 
    }
      int numerator() const { return num; }
	int denominator() const { return den; }

    	bool operator== (const fraction &o) const 
{	
 if (numerator() == o.numerator())
{
    		 return true;                       
}
}

	bool operator< (const fraction &o) const
{
 if (numerator() < o.numerator())
{
    		 return true;
                      }
}

	fraction &operator+= (const fraction &o)
{
    		this-> num += o.num;
this-> den += o.den;
    		return *this;
}

fraction &operator-= (const fraction &o)
{
    		this-> num -= o.num;
    		this-> den -= o.den;
    		return *this;
}

	fraction &operator*= (const fraction &o){
    this -> num *= o.num;
    this  -> den *= o.den;
    return *this;}


	fraction &operator/= (const fraction &o){
    this -> num /= o.num;
    this -> den /= o.den;
    return *this;}

private:
    int num;
    int den;
};

	fraction operator+ (fraction a, fraction b) {
    int GCD = gcd(a.denominator(),b.denominator());
       
        fraction part1 ((a.numerator() * b.denominator() + b.numerator() * a.denominator()),
            (a.denominator() * b.denominator()));
           
           
        return part1;}

	fraction operator+(int a, fraction b) {
        fraction f = (a/1);
       fraction answer(f.numerator() * b.denominator() + b.numerator() * f.denominator(),
            f.denominator() * b.denominator());
        return answer;}

	fraction operator+(fraction a, int b ) {
        fraction f = (b/1);
        fraction answer(a.numerator() * f.denominator() + f.numerator() * a.denominator(),
            a.denominator() * f.denominator());
        return answer;}

	fraction operator-(fraction a, fraction b) {
        fraction answer(a.numerator() * b.denominator() - b.numerator() * a.denominator(),
         a.denominator() * b.denominator());
      return answer;}

	fraction operator-(int a, fraction b) {
        fraction f = (a/1);
        fraction answer(f.numerator() * b.denominator() - b.numerator() * f.denominator(),
         f.denominator() * b.denominator());
      return answer;}

	fraction operator-(fraction a, int b) {
        fraction f = (b/1);
     fraction answer(a.numerator() * f.denominator() - f.numerator() * a.denominator(),
         a.denominator() * f.denominator());
      return answer;}

	fraction operator*(fraction a, fraction b) { 
        fraction answer(a.numerator() * b.numerator(), a.denominator() * b.denominator());
        return answer;}

	fraction operator*(int a, fraction b) {
       fraction f = (a/1);
       fraction answer(f.numerator() * b.numerator(), f.denominator() * b.denominator());
        return answer;}

	fraction operator*(fraction a, int b) {
        fraction f = (b/1);
        fraction answer(a.numerator() * f.numerator(), a.denominator() * f.denominator());
        return answer;}

	fraction operator/(fraction a, fraction b) {
        fraction answer(a.numerator() * b.denominator(), a.denominator() * b.numerator());
        return answer; }

	fraction operator/(int a, fraction b) {
        fraction f = (a/1);
        fraction answer( f.numerator() * b.denominator(), f.denominator() * b.numerator());
        return answer; }

	fraction operator/(fraction a, int b) {
       fraction f = (b/1);
       fraction answer( a.numerator() * f.denominator(), a.denominator() * f.numerator());
       return answer; }


ostream & operator<<(ostream &os, const fraction &f) {
    return os << '(' << f.numerator() << '/' << f.denominator() << ')';
}

istream & operator>>( istream &os, fraction &f) {
 int num = f.numerator();
 int den = f.denominator();
 char bracket1, slash1, bracket2;
 os >> bracket1 >> num >> slash1 >> den >> bracket2;
 f = fraction(num,den);
 return os;
}

int main(){

fraction f1(8,10);
fraction f6(7);
fraction f2(3,4);
fraction f3;
fraction f7;
fraction f8;
fraction f9;
fraction f10;

f7 = f6 + f1;
f3 = f1 - f6;
f8 = f1 * f6;
f9 = f1 / f6;

//operator>>(cin,f10);
//operator<< (cout, f10) << endl;
operator<< (cout, f7) << endl;
//operator<< (cout, f1) << endl;
//operator<< (cout, f2) << endl;
//operator<< (cout, f3) << endl;
//operator<< (cout, f8) << endl;
//operator<< (cout, f9) << endl;

return 0;
}

