#include <iostream>

#include <boost/type_traits/is_empty.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/assert.hpp>

//http://stackoverflow.com/questions/4772219/empty-base-class-optimization
class empty {};

class empty_one : public empty {};
class empty_two : public empty {};

class non_empty : public empty_one, public empty_two {};

//http://stackoverflow.com/questions/12701469/why-empty-base-class-optimization-is-not-working
struct T1 {};
struct T2 {};
struct T3 {};
struct T4 {};
struct T5 {};
struct T6 {};

struct Test : T1, T2, T3, T4, T5, T6 {};

struct Test2 {T1 t1; T2 t2; T3 t3; T4 t4; T5 t5; T6 t6;};


template <typename T, typename U>
struct Members {T t; U u;};

template <typename T, typename U>
struct InhMember : T {U u;};

template <typename T, typename U>
struct Inherit : T, U {};

template <typename T>
struct InheritOne : T {};


int main() {
    BOOST_MPL_ASSERT_NOT((boost::is_empty<Test2>));
    BOOST_MPL_ASSERT((boost::is_empty<Test>));
    
    std::cout << "Members1: " << sizeof(Members<empty_one, empty_one>) << std::endl; //2
    std::cout << "Members2: " << sizeof(Members<empty_one, empty_two>) << std::endl; //2
    std::cout << "Members3: " << sizeof(Members<empty_one, int>) << std::endl; //8
    std::cout << "Members4: " << sizeof(Members<int, empty_one>) << std::endl; //8
    
    std::cout << "InhMember1: " << sizeof(InhMember<empty_one, empty_one>) << std::endl; //2
    std::cout << "InhMember2: " << sizeof(InhMember<empty_one, empty_two>) << std::endl; //2
	std::cout << "InhMember3: " << sizeof(InhMember<empty_one, int>) << std::endl; //4

    std::cout << "Inherit1: " << sizeof(Inherit<empty_one, empty_two>) << std::endl; //2
    
    std::cout << "Members Tree: " << sizeof(Members<Members<empty_one, int>, empty_one>) << std::endl; //12
	std::cout << "Members Tree2: " << sizeof(Members<Members<empty_one, empty_one>, empty_one>) << std::endl; //3

	std::cout << "InhMember Tree: " << sizeof(InhMember<InhMember<empty_one, int>, empty_one>) << std::endl; //8
	std::cout << "InhMember Tree2: " << sizeof(InhMember<InhMember<empty_one, empty_one>, empty_one>) << std::endl; //3
    std::cout << "InhMember Tree3: " << sizeof(InhMember<empty_one, InhMember<empty_one, empty_one>>) << std::endl; //3

    std::cout << "Inherit Tree: " << sizeof(Inherit<Inherit<T1, T2>, T3>) << std::endl; //1
    
    
    std::cout << std::endl;
    
    std::cout << "sizeof(empty): " << sizeof(empty) << std::endl; //1
    std::cout << "sizeof(empty_one): " << sizeof(empty_one) << std::endl; //1
    std::cout << "sizeof(empty_two): " << sizeof(empty_two) << std::endl; //1
    std::cout << "sizeof(non_empty): " << sizeof(non_empty) << std::endl; //2

    std::cout << std::endl;

    non_empty a[2];

    void* peo1 = static_cast<empty_one*>(&a[0]);
    void* pet1 = static_cast<empty_two*>(&a[0]);
    void* pe10 = static_cast<empty*>(peo1);
    void* pe20 = static_cast<empty*>(pet1);
    
    //all three are equal
    std::cout << "address of non_empty[0]: " << &a[0] << std::endl;
    std::cout << "address of empty_one: " << peo1 << std::endl;
    std::cout << "address of empty of empty_one: " << pe10 << std::endl;
    
    //both are equal
    std::cout << "address of empty_two: " << pet1 << std::endl;
    std::cout << "address of empty of empty_two: " << pe20 << std::endl;

    std::cout << std::endl;

    void* peo2 = static_cast<empty_one*>(&a[1]);
    void* pet2 = static_cast<empty_two*>(&a[1]);
    void* pe11 = static_cast<empty*>(peo2);
    void* pe21 = static_cast<empty*>(pet2);
    
    //all three are equal
    std::cout << "address of non_empty[1]: " << &a[1] << std::endl;
    std::cout << "address of empty_one: " << peo2 << std::endl;
    std::cout << "address of empty of empty_one: " << pe11 << std::endl;
    
    //both are equal
    std::cout << "address of empty_two: " << pet2 << std::endl;
    std::cout << "address of empty of empty_two: " << pe21 << std::endl;
    
    
    std::cout << std::endl;
    
    std::cout << "sizeof(Test): " << sizeof(Test) << std::endl; //1
    std::cout << "sizeof(Test2): " << sizeof(Test2) << std::endl; //6
}