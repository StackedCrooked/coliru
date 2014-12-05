struct M
{
    virtual ~M() = default;
};

//struct M1 : M
struct M1 : private M
{
    static M1* foo() { return nullptr; }
};

struct A
{
    struct register_type_base
    {
        virtual ~register_type_base() {}
        virtual M* foo() const = 0;
    };
    
    template <typename Mn>
    struct register_type : register_type_base
    {
        Mn* foo() const
        {
            return Mn::foo();
        }
    };
};

const A::register_type<M1> REG;

int main() {}
