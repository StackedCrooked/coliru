    #include<iostream>
    #include<cstring>
    
    using namespace std;
    
    class Animal {
    private:
      // copy a string
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
      // initialize an "empty" Animal
      Animal() : age(0), name(NULL) {}

      // initialize an animal by age and name
      Animal(int _age, const char* _name): age(_age), name(dstr(_name)) {}

      // initialize an animal from another animal:
      // copy the name string
      Animal(const Animal& _a): age(_a.age), name(dstr(_a.name)) {}

      // assign an animal from another animal:
      // first delete the string you have, then copy the string
      Animal& operator=(const Animal& _a) {
        delete[] name;
        age = _a.age;
        name = dstr(_a.name);
        return *this;
      }

      // if C++11
      // we have something called "move" constructor and assignment
      // these are used, for instance, in "operator>>" below
      // and they assume that _a will soon be deleted
      Animal(Animal&& _a): Animal() {
        swap(age, _a.age);
        swap(name, _a.name);
      }
      Animal& operator=(Animal&& _a) {
        swap(age, _a.age);
        swap(name, _a.name);
        return *this;
      }
      
      ~Animal() { delete[] name; }
    
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
      out<<a.name<<endl<<a.age<<endl;
      return out;
    }
    
    
    int main() {
      Animal a { 23, "bobo" };
      cout<<a;
      cin>>a;
      cout<<a;
      return 0;
    }
