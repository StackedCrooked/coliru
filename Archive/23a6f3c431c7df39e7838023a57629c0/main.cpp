#include <iostream>

class A{ 
  friend class B;
  int a;
  
public:
  void seta(int in){a=in;}   //function assigning a value to a
  int geta(){return a;}
};

class B{
  public: 
    A someA;
    B(int ina){someA.seta(ina);}
    void printa(){std::cout<<someA.geta();}
};


int main(){

   B someB(2);
   someB.printa();
}