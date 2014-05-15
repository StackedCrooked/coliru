    #include<iostream>
    #include<string>
    
    using namespace std;

    class Animal {
    protected:
      int age;
      string name;
    public:
      // initialize an "empty" Animal
      Animal() : age(0) {}

      // initialize an animal by age and name
      Animal(int _age, const string& _name): age(_age), name(_name) {}

      friend ostream& operator <<(ostream& out,  const Animal& a) {
        return out<<a.name<<endl<<a.age<<endl;
      }
    };
    
    istream& operator >>(istream& in, Animal& a) {
      string n;
      int age;
      if( getline(in, n) >> age )
        a = Animal(age, n);
      return in;
    }
    
    
    int main() {
      Animal a { 23, "bobo" };
      cout<<a;
      cin>>a;
      cout<<a;
    }
