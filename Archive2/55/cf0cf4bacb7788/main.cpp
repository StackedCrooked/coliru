#include <list>
#include <iostream>
#include <typeinfo>

using namespace std;

struct BASECLASS {  };
struct SPECIALFORMAT : BASECLASS { };
struct ANOTHERSPECIALFORMAT : BASECLASS { };

template <class T>
struct LISTFORMATTER {
  list<T> l;

  
  bool format();
};

 //Change the template here:    
template<class T>
bool LISTFORMATTER<T>::format() {
    /* Here you can call methods from elements in l*/
     std::cout << " I will call something on the list of type"  << typeid(l).name() << std::endl;  
     return true;
}
//--------------------------
int main()
{
LISTFORMATTER<BASECLASS> bcFt;
LISTFORMATTER<SPECIALFORMAT> spFt;
LISTFORMATTER<ANOTHERSPECIALFORMAT> aspFt;

bcFt.format(); // <-- ok
spFt.format(); // <-- Calling standard format(), not specialized
aspFt.format(); // <-- Calling standard format(), not specialized


return 0;
}
