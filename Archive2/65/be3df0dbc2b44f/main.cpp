template <typename typeA>
class Parent{
public:
    template <typename typeB>
    void foo(){}

};

template <typename typeA>
class Child : public Parent<typeA>{
public:
    void bar(){
        this->foo<double>();
    }
};

int main(){
    Child<int> c;
    c.bar();
}