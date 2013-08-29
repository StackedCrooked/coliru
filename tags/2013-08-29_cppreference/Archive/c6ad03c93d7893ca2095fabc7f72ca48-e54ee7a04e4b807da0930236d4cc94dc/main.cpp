
    enum MyEnum : unsigned char
    {
        i ,j, k, w
    };

    union MyUnion
    {
        signed char ma:3; //char to save memory
        unsigned char mb:3;
    };
    
    struct MyStruct
    {
        MyUnion X;
        MyUnion Y; //same type so they share space    
        MyEnum mEnum; //this can't easily share that space
    }; //this structure is three bytes
    
    #include <iostream>
    int main() {
        std::cout << sizeof(MyStruct);
    }