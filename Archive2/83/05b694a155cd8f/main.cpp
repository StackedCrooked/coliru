class A{ // Interface
      public:
             virtual void example(void)=0;    
             void thisWorks(void);
};

class B:public A{ // Derived From Interface, functions implemented in source file..
      public:
             void example(void){
             }
             void thisWorks(void){
             }
};

class C{ // Other Random Class

};

template <class T>
class D: public C{ // Derived From Other Random Class with Template for Interface A derived Classes
       T* Object;
       public:
              D(T * Object){ // implemented in source file
                   this->Object=Object;
              }
              void otherExample(void){
                   this->Object->thisWorks();
                   this->Object->example();
              };
};

int main() {
  D<B>* TestD=new D<B>(new B());
  TestD->otherExample(); 
}