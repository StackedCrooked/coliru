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


template <typename T, typename U>
struct Members {
  T t;
  U u;
};

template <typename T, typename U>
struct InhMember : T {
  U u;  
};

template <typename T, typename U>
struct InhMember2 : U {
  T t;  
};

template <typename T, typename U>
struct Inherit : T, U {};


template <typename T, typename U>
struct Tree : T, U {};


int main()
{
    std::cout << "Members1: " << sizeof(Members<empty_one, empty_one>) << std::endl; //2
    std::cout << "Members2: " << sizeof(Members<empty_one, empty_two>) << std::endl; //2
    std::cout << "Members3: " << sizeof(Members<empty_one, int>) << std::endl; //8
    std::cout << "Members4: " << sizeof(Members<int, empty_one>) << std::endl; //8
    
    std::cout << "InhMember1: " << sizeof(InhMember<empty_one, empty_one>) << std::endl; //2
    std::cout << "InhMember2: " << sizeof(InhMember<empty_one, empty_two>) << std::endl; //2
	std::cout << "InhMember3: " << sizeof(InhMember<empty_one, int>) << std::endl; //4
    std::cout << "InhMember4: " << sizeof(InhMember2<int, empty_one>) << std::endl; //4

    //std::cout << "Inherit1: " << sizeof(Inherit<empty_one, empty_one>) << std::endl; //error
    std::cout << "Inherit2: " << sizeof(Inherit<empty_one, empty_two>) << std::endl; //2
    
    std::cout << std::endl;
    
    
    //std::cout << "sizeof(Tree1): " << sizeof(Tree<Tree<empty_one, empty_two>, empty_two>) << std::endl; //3
    //std::cout << "sizeof(Tree2): " << sizeof(Tree<non_empty, empty_two>) << std::endl; //3
        
    
    std::cout << std::endl;
    
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
    
    
    std::cout << std::endl;
    
    std::cout << "sizeof(Test): " << sizeof(Test) << std::endl;
    
    std::cout << std::endl;
    
    Test t;
    void* t1 = static_cast<T1*>(&t);
    void* t2 = static_cast<T2*>(&t);
    void* t3 = static_cast<T3*>(&t);
    void* t4 = static_cast<T4*>(&t);
    void* t5 = static_cast<T5*>(&t);
    void* t6 = static_cast<T6*>(&t);
    
    std::cout << "Test: " << &t << std::endl;
    std::cout << "T1: " << t1 << std::endl;
    std::cout << "T2: " << t2 << std::endl;
    std::cout << "T3: " << t3 << std::endl;
    std::cout << "T4: " << t4 << std::endl;
    std::cout << "T5: " << t5 << std::endl;
    std::cout << "T6: " << t6 << std::endl;
}