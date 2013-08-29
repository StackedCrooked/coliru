Class A{
  public:  
  int variable;
  A(): variable(4) {}
};

class B : public A{

  void  function(){

    A test = new A()
  }
};