    #include <functional>
    
    struct MyClass
    {
        typedef std::function<void (int, bool)> CallbackType;
        typedef std::function<void (int, float, bool)> AnotherCallbackType;
        CallbackType callback;

        void setCallback(AnotherCallbackType c, float param)
        {
            callback = [&](int a, bool b) { c(a, param, b); };
            // Calling the callback:
            callback(42, false);
        }
    };
    
    #include <iostream>
    void print(int a, float b, bool c)
    {
        std::cout << std::boolalpha;
        std::cout << "print " << a << ", " << b << ", " << c << "\n";
    }
    
    int main()
    {
        MyClass obj;
        obj.setCallback(print, 123.456f);
    }
    