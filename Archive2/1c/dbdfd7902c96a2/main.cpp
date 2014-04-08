class A {

 public:

  A() : b(0) 
  {
    b = new B;
  }

  A& operator=(const A& rhs)  //first
  {         
      B* b1 = new B(*rhs.b);
      delete b;
      b = b1; 
      return *this;
  }
  
  A& operator=(const A& rhs)  //second
  {         
      delete b;
      b = NULL;
      b = rhs.b;
      return *this;
  }

 private:

  B* b;

};