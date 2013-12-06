#include <istream>

//#define DO_COMPILE_1 1
//#define DO_COMPILE_2 1
//#define DO_COMPILE_3 1
#define DO_COMPILE_4 1

#if DO_COMPILE_1

class A {
private:
    std::istream strm;
    
public:
    A() : strm(NULL) { }
};
 
class B : public A {
public:
    B() : A() { }
};
 
#elif DO_COMPILE_2

class A : protected std::istream {
public:
    A() : std::istream(NULL) { }
};
 
class B : public A {
public:
    B() : A() { }
};
 
#elif DO_COMPILE_3

class A : private std::istream {
public:
friend class B;
    A() : std::istream(NULL) { }
};
 
class B : public A {
public:
    B() : A() { }
};

#elif DO_COMPILE_4

class A : private std::istream {
public:
    
};
 
class B : public A {
public:
    B() : A() { }
};
 
#else

class A : private std::istream {
public:
    A() : std::istream(NULL) { }
};
 
class B : public A {
public:
    B() : A() { }
};

#endif // DO[NT]_COMPILE
 
int main () {}