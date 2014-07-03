  #include<iostream>
  using namespace std;
  int i=20;

  void fn()
  { 
    cout<<" I am outside class"<<endl;
  }

  class a
  {
      public: 

        int x= ::i;  // error is  i cannot appear in constant expression

        void accessGlobal()
        {

           ::fn();      //fn() is being called
        }
  };

  int main()
  {
     a obj;
     obj.accessGlobal();
  }

