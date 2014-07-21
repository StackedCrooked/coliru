template <typename T>
struct identity
{
    typedef T type;
};

struct S { 
    
    operator typename identity<int(&)[10]>::type();
};

int main()
{
}