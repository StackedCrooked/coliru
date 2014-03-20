#include <iostream>

class IVille
{
    public:
        virtual ~IVille() {}
        virtual void Foo() = 0;
};

class IVilleSpeciale : public virtual IVille
{
    public:
        virtual ~IVilleSpeciale() {}
        virtual void Bar() = 0;
};

class CVille : public virtual IVille
{
    public:
        CVille() {}
        virtual ~CVille() {}
        void Foo() override { std::clog << "FOO" << std::endl; }
};

class CVilleSpeciale : public IVilleSpeciale, public CVille
{
    public:
        CVilleSpeciale() {}
        virtual ~CVilleSpeciale() {}
        void Bar() override { std::clog << "BAR" << std::endl; }
};

int main()
{
    IVilleSpeciale* pVS = new CVilleSpeciale;
    
    pVS->Foo();
    pVS->Bar();
    
    delete pVS;
    
    return 0;   
}