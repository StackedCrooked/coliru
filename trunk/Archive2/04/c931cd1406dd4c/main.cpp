#include <iostream>
 using namespace std;
 
 class Fraction{
   private:
     int numerator, denominator;
 
   public:
     Fraction(int n, int d): numerator(n), denominator(d) {}
   // Note that the keyword operator combined with an actual
   // operator is used as the function name
   friend ostream& operator<<(ostream&, Fraction&);
 };
 
 ostream& operator<<(ostream& out, Fraction& f){
   out << f.numerator << '/' << f.denominator;
   return out;
 }
 
 int main(){
   Fraction f1(3, 8);
   Fraction f2(1, 2);
 
   cout << f1 << endl;
   cout << 3 << ' ' << f2 << endl;
 
   return 0;
 }