class MyInt
{

public:
  MyInt (int n = 0);           // first constructor
  MyInt (const char* c);

  MyInt& operator++ ();
  MyInt operator++ (int i);
  MyInt& operator-- ();
  MyInt operator-- (int i);

  ~MyInt ();
  MyInt (const MyInt& mi);
  MyInt& operator= (const MyInt& mi);

  void testShow();

private:
  int* intstring;
  int maxsize;
};

#include <iostream>
using std::cout;

MyInt::MyInt (int n)
{
   maxsize = 1;

   if (n > 0) { 
   // Divides the number by 10 to find the number of times it is divisible; that is the length
      int i = n;

      while (i > 1) {
         i = i / 10;
         maxsize++;

         cout << "\nMax Size is = " << maxsize;
      }
   }

   intstring = new int[maxsize];

   for (int j = (maxsize - 1); j >= 0; j--) {                   
   // Copies the integer into an integer array by use of the modulus operator
      intstring[j] = n % 10;
      n = n / 10;

      cout << "\nj = " << j;
     cout << "\nintstring[j] = " << intstring[j];
  }
}

MyInt::~MyInt ()                                                
// Destructor
{
   delete [] intstring;
}

void MyInt::testShow() {
   for (int i = 0; i < maxsize; i++) {
      cout << intstring[i];
   }
}

int main () {

  MyInt a(12345);

  a.testShow();
}
