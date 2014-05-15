enum MyEnum
{
    FIRST,
    OTHER
};

template<MyEnum> struct GetArraySize;
template<> struct GetArraySize<FIRST> {static const int value=4;};
template<> struct GetArraySize<OTHER> {static const int value=10;};


template<MyEnum e> 
struct MyTemplate
{
    static const int arrSize = GetArraySize<e>::value;
    int myArr[arrSize];
};






int main() {
    MyTemplate<FIRST> a;
    MyTemplate<OTHER> b;
}