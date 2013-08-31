

namespace A
{
    namespace B
    {
    }
    
    using namespace B;
}



namespace A
{
    namespace B
    {
        const int a = 1;
    }
}


int main()
{
    return A::a;
}