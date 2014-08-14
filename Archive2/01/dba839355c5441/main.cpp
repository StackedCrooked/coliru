#include <iostream>

//http://stackoverflow.com/questions/4772219/empty-base-class-optimization
class empty
{
};

class empty_one : public empty {};
class empty_two : public empty {};

class non_empty
    : public empty_one
    , public empty_two
{
};

//http://stackoverflow.com/questions/12701469/why-empty-base-class-optimization-is-not-working
struct T1 { };
struct T2 { };
struct T3 { };
struct T4 { };
struct T5 { };
struct T6 { };

struct Test : T1, T2, T3, T4, T5, T6 { };


int main()
{
    std::cout << "sizeof(empty): " << sizeof(empty) << std::endl;
    std::cout << "sizeof(empty_one): " << sizeof(empty_one) << std::endl;
    std::cout << "sizeof(empty_two): " << sizeof(empty_two) << std::endl;
    std::cout << "sizeof(non_empty): " << sizeof(non_empty) << std::endl;

    std::cout << std::endl;

    non_empty a[2];

    void* peo1 = static_cast<empty_one*>(&a[0]);
    void* pet1 = static_cast<empty_two*>(&a[0]);
    void* pe10 = static_cast<empty*>(peo1);
    void* pe20 = static_cast<empty*>(pet1);
    std::cout << "address of non_empty[0]: " << &a[0] << std::endl;
    std::cout << "address of empty_one: " << peo1 << std::endl;
    std::cout << "address of empty_two: " << pet1 << std::endl;
    std::cout << "address of empty of empty_one: " << pe10 << std::endl;
    std::cout << "address of empty of empty_two: " << pe20 << std::endl;

    std::cout << std::endl;

    void* peo2 = static_cast<empty_one*>(&a[1]);
    void* pet2 = static_cast<empty_two*>(&a[1]);
    void* pe11 = static_cast<empty*>(peo2);
    void* pe21 = static_cast<empty*>(pet2);
    std::cout << "address of non_empty[1]: " << &a[1] << std::endl;
    std::cout << "address of empty_one: " << peo2 << std::endl;
    std::cout << "address of empty_two: " << pet2 << std::endl;
    std::cout << "address of empty of empty_one: " << pe11 << std::endl;
    std::cout << "address of empty of empty_two: " << pe21 << std::endl;
    
    
    std::cout << std::endl << sizeof(Test) << std::endl;
}