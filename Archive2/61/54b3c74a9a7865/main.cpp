#include <iostream>
using namespace std;
int gcd(int a, int b)
{
    int c;
	if ( a > b )
	{
		// swap and b to ensure a <= b
		c = a;
		a = b;
		b = c;
	}
	c = b % a; // c is the remainder of b divided by a
	while (c != 0)
	{
		// new dividend becomes the previous divisor
		// new divisor becomes the remainder
		b = a;
		a = c;
		c= b % a;
	}
	return a; // a is the gcd
}

int lcm(int a, int b)
{
	int g, l;
	g = gcd(a,b);
	l = g * (a/g) * (b/g);
	return l;
}

class Fraction
{
	private:		
		int num;	
		int denom;	
	public:	
		Fraction(int = 0, int = 1);	// constructor 
		Fraction(const Fraction &);	// copy constructor 
		~Fraction();			// destructor
		Fraction operator + (Fraction); // + operator
		Fraction operator = (Fraction); // = operator
};

Fraction :: Fraction (const Fraction & AnotherFraction)
{
	this->num = AnotherFraction.num;
	this->denom = AnotherFraction.denom;
	cout<< "Fraction object (" << this->num 
		<<"/" << this->denom << ") created(copy)" << endl;
}

Fraction :: Fraction(int a, int b)
{
	this->num = a; 
	this->denom = b;
	cout<< "Fraction object (" << this->num 
		<<"/" << this->denom << ") created" << endl;
}

Fraction :: ~Fraction()
{
	cout<< "Fraction object (" << this->num 
		<<"/" << this->denom << ") destroyed" << endl;
}

Fraction Fraction :: operator + (Fraction operand2)
{
	Fraction tmp;
	int g, l;
	l = lcm(this->denom, operand2.denom);
	tmp.num =	this->num * (l/this->denom) + 
				operand2.num * (l/operand2.denom);
	tmp.denom = l;
	g = gcd(tmp.num, tmp.denom);
	tmp.num /= g;
	tmp.denom /= g;
	cout<< "Within overloaded Fraction::operator + : (" 
		<< this->num << "/" << this->denom << ") + ("
		<< operand2.num << "/" << operand2.denom << ") = ("
		<< tmp.num << "/" << tmp.denom << ")" << endl;
	return tmp;
}

Fraction Fraction :: operator = (Fraction rval)
{
	this->num = rval.num;
	this->denom = rval.denom;
	cout<< "Within overloaded Fraction::operator = : (" 
		<< rval.num <<"/" << rval.denom << ") -> (" 
		<< this->num <<"/" << this->denom << ")" << endl;
	return *this;
}

int main()
{
	int n, d;
	cout << "Please enter values of numerator, denominator : ";
	cin >> n >> d;
	Fraction f1(n,d); // automatic call to constructor

	cout << "Please enter another set of numerator, denominator : ";
	cin >> n >> d;
	Fraction f2(n,d); 

	Fraction f3;
	
	f3 = f1 + f2;

	return 0;
}
