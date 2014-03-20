#include <iostream>

class IVille
{
    public:
        virtual ~IVille() {}
        virtual void Foo() = 0;
};

class IVilleSpeciale
{
    public:
        virtual ~IVilleSpeciale() {}
        virtual void Bar() = 0;
        
        IVille* Ville();
        static IVilleSpeciale *FromVille(IVille *pVille);
};

class CVille : public IVille
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

IVilleSpeciale *IVilleSpeciale::FromVille(IVille *pVille)
{
    // TODO: Vérifier qu'on aie bien une ville spéciale...
    return static_cast<CVilleSpeciale*>(pVille);
}

IVille *IVilleSpeciale::Ville()
{
    return static_cast<CVilleSpeciale*>(this);
}

int main()
{
    IVilleSpeciale* pVS = new CVilleSpeciale;
    
    pVS->Ville()->Foo();
    pVS->Bar();
    
    delete pVS;
    
    return 0;   
}