
    enum MyEnum : unsigned char
    {
        i ,j, k, w
    };

    union MyUnion
    {
        signed char mXa:3; //char to save memory
        unsigned char mXb:3;
    };
    
    struct MyStruct
    {
        MyUnion a;
        MyUnion b; //same type so they share space    
        MyEnum mEnum; //this can't easily share that space
    }; //this structure is three bytes
    
    #include <iostream>
    int main() {
        std::cout << sizeof(MyStruct);
    }