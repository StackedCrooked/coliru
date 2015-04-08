#include <iostream>
#include <iomanip>
 
// Forward declaration
template <typename T> class MyComplex;
 
template <typename T>
std::ostream & operator<< (std::ostream & out, const MyComplex<T> & c);
template <typename T>
std::istream & operator>> (std::istream & in, MyComplex<T> & c);
 
// MyComplex template class declaration
template <typename T>
class MyComplex {
private:
   T real, imag;
 
public:
   // Constructor
   explicit MyComplex<T> (T real = 0, T imag = 0)
         : real(real), imag(imag) { }
 
   // Overload += operator for c1 += c2
   MyComplex<T> & operator+= (const MyComplex<T> & rhs) {
      real += rhs.real;
      imag += rhs.imag;
      return *this;
   }
 
   // Overload += operator for c1 += value
   MyComplex<T> & operator+= (T value) {
      real += value;
      return *this;
   }
 
   // Overload comparison == operator for c1 == c2
   bool operator== (const MyComplex<T> & rhs) const {
      return (real == rhs.real && imag == rhs.imag);
   }
 
   // Overload comparison != operator for c1 != c2
   bool operator!= (const MyComplex<T> & rhs) const {
      return !(*this == rhs);
   }
 
   // Overload prefix increment operator ++c
   // (Separate implementation for illustration)
   MyComplex<T> & operator++ ();
 
   // Overload postfix increment operator c++
   const MyComplex<T> operator++ (int dummy);
 
   /* friends */
 
   // (Separate implementation for illustration)
   friend std::ostream & operator<< <>(std::ostream & out, const MyComplex<T> & c); // out << c
   friend std::istream & operator>> <>(std::istream & in, MyComplex<T> & c);        // in >> c
 
   // Overloading + operator for c1 + c2
   // (inline implementation for illustration)
   friend const MyComplex<T> operator+ (const MyComplex<T> & lhs, const MyComplex<T> & rhs) {
      MyComplex<T> result(lhs);
      result += rhs;  // uses overload +=
      return result;
   }
 
   // Overloading + operator for c + double
   friend const MyComplex<T> operator+ (const MyComplex<T> & lhs, T value) {
      MyComplex<T> result(lhs);
      result += value;  // uses overload +=
      return result;
   }
 
   // Overloading + operator for double + c
   friend const MyComplex<T> operator+ (T value, const MyComplex<T> & rhs) {
      return rhs + value;   // swap and use above function
   }
};
 
// Overload prefix increment operator ++c
template <typename T>
MyComplex<T> & MyComplex<T>::operator++ () {
  ++real;   // increment real part only
  return *this;
}
 
// Overload postfix increment operator c++
template <typename T>
const MyComplex<T> MyComplex<T>::operator++ (int dummy) {
   MyComplex<T> saved(*this);
   ++real;  // increment real part only
   return saved;
}
 
/* Definition of friend functions */
 
// Overload stream insertion operator out << c (friend)
template <typename T>
std::ostream & operator<< (std::ostream & out, const MyComplex<T> & c) {
   out << '(' << c.real << ',' << c.imag << ')';
   return out;
}
 
// Overload stream extraction operator in >> c (friend)
template <typename T>
std::istream & operator>> (std::istream & in, MyComplex<T> & c) {
   T inReal, inImag;
   char inChar;
   bool validInput = false;
   // Input shall be in the format "(real,imag)"
   in >> inChar;
   if (inChar == '(') {
      in >> inReal >> inChar;
      if (inChar == ',') {
         in >> inImag >> inChar;
         if (inChar == ')') {
            c = MyComplex<T>(inReal, inImag);
            validInput = true;
         }
      }
   }
   if (!validInput) in.setstate(std::ios_base::failbit);
   return in;
}


 
int main() {
   std::cout << std::fixed << std::setprecision(2);
 
   MyComplex<double> c1(3.1, 4.2);
   std::cout << c1 << std::endl;  // (3.10,4.20)
   MyComplex<double> c2(3.1);
   std::cout << c2 << std::endl;  // (3.10,0.00)
 
   MyComplex<double> c3 = c1 + c2;
   std::cout << c3 << std::endl;  // (6.20,4.20)
   c3 = c1 + 2.1;
   std::cout << c3 << std::endl;  // (5.20,4.20)
   c3 = 2.2 + c1;
   std::cout << c3 << std::endl;  // (5.30,4.20)
 
   c3 += c1;
   std::cout << c3 << std::endl;  // (8.40,8.40)
   c3 += 2.3;
   std::cout << c3 << std::endl;  // (10.70,8.40)
 
   std::cout << ++c3 << std::endl; // (11.70,8.40)
   std::cout << c3++ << std::endl; // (11.70,8.40)
   std::cout << c3   << std::endl; // (12.70,8.40)
 
// c1+c2 = c3;  // error: c1+c2 returns a const
// c1++++;      // error: c1++ returns a const
 
// MyComplex<int> c4 = 5;  // error: implicit conversion disabled
   MyComplex<int> c4 = (MyComplex<int>)5;  // explicit type casting allowed
   std::cout << c4 << std::endl; // (5,0)
 
   MyComplex<int> c5;
   std::cout << "Enter a complex number in (real,imag): ";
   std::cin >> c5;
   if (std::cin.good()) {
      std::cout << c5 << std::endl;
   } else {
      std::cerr << "Invalid input" << std::endl;
   }
   return 0;
}