class A;        
class B;

class Base
{
};    

template <class T>    
class Derived : public Base
{   
    public:
        Derived(T2 startVal):var(startVal){}
    private:
        T2 var;    
};

template <typename T>
Derived<T> MakeDerived(T initValue)
{
    return Derived<T>(initValue);
}

int main()
{
    return 0;
}