    #include <iostream>
    
    
    bool test1(bool a, bool b, bool c)
    {
        return a | b | c;
    }
    
    bool test2(bool a, bool b, bool c)
    {
        return a || b || c;
    }
    
    int main()
    {
      bool a = true;
      bool b = false;
      bool c = true;
      test1(a,b,c);
      test2(a,b,c);
      return 0;
    }

