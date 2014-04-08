class A {

 public:

  A() : b(0) 
  {
    b = new B;
  }
  
  A(const A& rhs) //copy constructor
  : b(new B(*rhs.b))
  {
  }

  A& operator=(const A& rhs)  //deep copy
  {         
      B* b1 = new B(*rhs.b);
      delete b;
      b = b1; 
      return *this;
  }
  
  A& operator=(const A& rhs)  //copy on write
  {         
      delete b;
      b = rhs.b;
      return *this;
  }
  
  A& operator=(A rhs) //copy and swap
  {
      std::swap(b, rhs.b);
      return *this;
  }

 private:

  B* b;

};