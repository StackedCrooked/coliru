enum MyEnum
{
    FIRST = 4,
    OTHER = 10
};


template<MyEnum e> 
struct MyTemplate
{
    int myArr[e];
};






int main() {
    MyTemplate<FIRST> a;
    MyTemplate<OTHER> b;
}