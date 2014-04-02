template <typename Type, typename Class>
class MemberPredicate{
public:
    MemberPredicate(Type (Class::*method)(), bool (*operation)(Type,Type), Type data) : method(method), operation(operation), data(data){};
    bool operator()(Class * other){ return (*this->operation)((other->(*this->method))(), this->data); }
private:
    Type (Class::*method)();
    bool (*operation)(Type,Type);
    Type data;
};

bool equal(int a, int b){
    return a == b;
}

struct IntClass
{
    int m;
    IntClass(int p) : m(p) {}
    int getInt() { return m; }
};

int main()
{
    MemberPredicate<int, IntClass> pred(&IntClass::getInt, &equal, 4);
    IntClass * i = new IntClass(5); // stores 5 in IntClass and returns this value when i->getInt() is called
    pred(i);
}