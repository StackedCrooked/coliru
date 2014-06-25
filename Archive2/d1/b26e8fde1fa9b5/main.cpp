    template< typename Func>
    class Base;
    
    template< typename R, typename... Args >
    class Base < R(Args...) >
    {
     public: 
       virtual R user_defined_function(Args...) = 0;
    };


    class Derived : private Base< int(float, int, double) >
    {
      public:
      int user_defined_function(float, int, double) override;
    };

    class Derived2 : private Base< int(float, int, int) >
    {
       public:
       int user_defined_function(float, int, double);
    };
    
    int main()
    {
        Derived d;
        Derived2 d2;
    }