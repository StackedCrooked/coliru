#include <iostream>
using namespace std;

class Myclass
{
    public:
    Myclass(const char *){}
    
   // Works fine
   friend ostream& operator<<( ostream& o, const Myclass& m );

   // Gives an error
   friend ostream& operator<<( ostream& o, Myclass& m );

   private:
   char * ptr;
 };

 // Assuming .cpp file created appropriately

 int main()
 {
    Myclass a("string");

    cout << a;

    return 0;
  }