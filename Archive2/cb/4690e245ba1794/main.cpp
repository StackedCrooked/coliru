    #include <iostream>
    #include <string>
    #include <vector>
    using namespace std;
     
    class A {
        public :
        string name;
        int age;
        A(){ cout << "constructor is called" << endl; }
        ~A() { cout << "destructor is called"<< endl; }
    };
     
    int main()
    {
      vector<class A> vec(5);
      cout << vec.size() << endl;
    }