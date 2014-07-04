
#include <iostream>

using namespace std;

struct NonNegative
{
  int i;
  int const& get() const {
      cout << "const" << endl;
      return i; 
      }
  int& get() { 
      cout << "non-const" << endl;
      return i; 
      }
};

// усли убрать const в функции, то строчке (*) кидает ошибку
void foo(NonNegative const& tada) {
    tada.get();
}

int main(int argc, const char* argv[])
{   
    NonNegative{2}.get(); // non-const
    
    /*
    const, хотя вроде бы тоже временный объект создаётся, но при передаче в функцию по ссылке
    происходит добавляется спецификатор const
    */
    foo(NonNegative{2}); // (*)
    
    return 0;
}

