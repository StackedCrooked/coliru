#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace eco
{
    int x = 5;    
}

class Alumno
{
public:
    int id;
    string name;
};

struct Ficha
{
    int t1;
    float t2;
};

void func(int *ar)
{
    cout << ar[1] << endl;
}

char* func2(char *ar)
{
    ar[0] = 't';
    return ar;
}

int main()
{
   Alumno al1; 
   vector<Alumno> al(5);
   al[0].id = 1;
   al[1].id = 2;
   
   Alumno *alu;
   alu = new Alumno[5];
   alu->id = 3;
   alu->name = "hola";
   
   struct Ficha fich;
   fich.t1 = 5;
   
   string trama = "caracola";
   
   bool var = true;
   var = ~true;
   
   int array[3] = {2,5,6};
   char name[] = "hola";
   
   cout << *array << endl;
   func(array);
   cout << func2(name) << endl;
   
   cout << eco::x << endl;
   
   int t;
   cout << sizeof(t) << endl;
   return 0;
}
