#include <iostream>

class Type
{
public:
    Type() {}
    Type(int val) {}
    virtual ~Type(){}
    int getValue() { return myvalue; }
    void setValue(int val) { myvalue = val; }
private:
    int myvalue;
};

class TypeZero : public Type
{
public:
    TypeZero() : Type() {}
    ~TypeZero() {}
};

class TypeOne : public Type
{
public:
    TypeOne(int val) : Type(val) { setValue(val); }
    virtual ~TypeOne() {}
};

void test(Type t)
{
    std::cout << t.getValue() << std::endl;
}

int main() {
    int value = 99;
    test(TypeZero());
    test(TypeOne(value));
	return 0;
}