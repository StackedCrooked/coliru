struct B{};
struct A
{
    
    B b;
    operator B(){return b;}
};

int main()
{
    A a;
    const B& bob = a;
}