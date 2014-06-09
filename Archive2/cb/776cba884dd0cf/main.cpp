
struct Type
{
    Type() {};
    explicit Type(Type const&) {};
};

struct Type1 : Type
{};

int main()
{
    Type a;
    Type t1 = a;
    
    Type1 b;
    Type t2 = b;
}
