    #include <iostream>
    
    int cycleList(int arg1, int arg2) { return arg1 + arg2; }
    
    struct cycleListObj
    {
        int arg1, arg2;

        // constructor stores arguments for later use
        cycleListObj(int a1, int a2): arg1(a1), arg2(a2) {}
        
        // overload function call operator()
        int operator()() { return arg1 + arg2; }
    };
    
    int main()
    {
        int result1 = cycleList(1, 1);   // stores 2 into result1
        cycleListObj fun(1, 1);          // defines a function object fun with arguments 1, 1
        int result2 = fun();             // calls the funtion object, and stores the result into result2
        std::cout << result1 << result2; // outputs 22
    }