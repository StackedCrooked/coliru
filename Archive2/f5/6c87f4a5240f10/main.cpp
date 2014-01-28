    #include <boost/function.hpp>
    #include <boost/bind.hpp>

    struct MyClass
    {
        typedef void (MyClass::* CallbackType)(int, float);
        CallbackType callback;

        void onRenderCallback(int param1, float param2) {}
        void setCallback(CallbackType c)
        {
            callback = c;
            // Calling the callback:
            (this->*callback)(42, 3.14f);
            // Note that it is possible to embed the parameters
            // but that will need to create a class, basically it means you will reimplement Boost.Bind...
        }
    };
    
    int main()
    {
        MyClass obj;
        obj.setCallback(&MyClass::onRenderCallback);
    }
    