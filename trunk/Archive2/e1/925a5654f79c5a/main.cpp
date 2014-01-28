    #include <boost/function.hpp>
    #include <boost/bind.hpp>

    struct MyClass
    {
        typedef boost::function<void (int, bool)> CallbackType;
        typedef boost::function<void (int, float, bool)> AnotherCallbackType;
        CallbackType callback;

        void onRenderCallback(int param1, float param2) {}
        void setCallback(AnotherCallbackType c, float param)
        {
            callback = boost::bind(c, _1, param, _2);
            // Calling the callback:
            callback(42, 3.14f);
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
    