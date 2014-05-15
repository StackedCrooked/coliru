#include<iostream>
#include<cstring>

using namespace std;

class Animal {
private:
  inline static char* dstr(const char* string) {
    if( !string ) return NULL;
    size_t l = strlen(string);
    if( !l ) return NULL;
    return strcpy(new char[++l], string);
  }
protected:
  int age;
  char* name;
public:
  Animal() : age(0), name(NULL) {}
  Animal(int _age, char* _name): age(_age), name(dstr(_name)) {}
  Animal(const Animal& _a): age(_a.age), name(dstr(_a.name)) {}
  Animal& operator=(const Animal& _a) { delete[] name; age = _a.age; name = dstr(_a.name); return *this; }
  // if C++11
  Animal(Animal&& _a): age(_a.age), name(_a.name) {}
  Animal& operator=(Animal&& _a) { age = _a.age; name = _a.name; return *this; }
  
  ~Animal() {
    delete[] name;
  }

  friend ostream& operator <<(ostream& out,  const Animal& a);

};

istream& operator >>(istream& in, Animal& a) {
  const size_t MAX_ANIMAL_NAME = 2048;
  int age;
  char n[MAX_ANIMAL_NAME+1];
  if( in.getline(n, MAX_ANIMAL_NAME) >> age )
    a = Animal(age, n);
  return in;
}

ostream& operator <<(ostream& out, const Animal& a) {
  out<<a.name<<endl<<a.age;
  return out;
}


int main() {
  Animal a;
  cin>>a;
  cout<<a;
  return 0;
}
