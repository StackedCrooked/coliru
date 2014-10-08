#include <iostream>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>

//################### PODEJSCIE 1

// Rozwiazanie w stylu Jebaka Bezdomnych
// + prostota
// - mozesz ustawic z kazdego miejsca instancje
// ~ shared pointery
struct SharedSingleton
{
    static boost::shared_ptr<SharedSingleton>& getInstance()
    {
        static boost::shared_ptr<SharedSingleton> instance(new SharedSingleton);
        return instance;
    }
    
    virtual void PrintName(std::string prefix)
    {
        std::cout << prefix << " SharedSingleton" << std::endl;
    }
    
    virtual ~SharedSingleton(){}
    
    protected:
    SharedSingleton(){}
};

struct SharedSingletonMock : SharedSingleton
{
    virtual void PrintName(std::string prefix)
    {
        std::cout << prefix << " SharedSingletonMock" << std::endl;
    }
};

//#################### PODEJSCIE 2
// Podobne do powyzszego, ale z wrapperem na pointer
// + nie mozna latwo ustawic instancji z kodu produkcyjnego
// - bardziej skomplikowane
// - kto wie czy nie wiekszy narzut w praktyce

struct StupidSingleton;

// Pomocniczy wrapper na pointer ktory ukrywa pointer przed klientami (nie mozna ustawic instancji)
// (oczywiscie mozna jak ktos sobie odziedziczy)
struct StupidSingletonPtr
{
    StupidSingletonPtr(StupidSingleton* ptr): myPtr(ptr) {}
    
    // Tu nawet jak chcesz mozna sobie zrobic zmienna StupidSingleton* rawPtr i ja zwracac.
    inline StupidSingleton* operator->()
    {
        return myPtr.get();
    }
    
    protected:
    boost::scoped_ptr<StupidSingleton> myPtr;
    // Trick ze stack overflow. Pozwala na dostep z klas pochodnych do skladowej protected innego obiektu :D
    static boost::scoped_ptr<StupidSingleton>* getPtr(StupidSingletonPtr *obj) { return &obj->myPtr; }
};

struct StupidSingleton
{
    static StupidSingletonPtr& getInstance()
    {
        static StupidSingletonPtr instance(new StupidSingleton);
        return instance;
    }
    
    virtual void PrintName(std::string prefix)
    {
        std::cout << prefix << " StupidSingleton" << std::endl;
    }
 
    virtual ~StupidSingleton(){}
    
    protected:
    StupidSingleton(){}
};

struct StupidSingletonMock : StupidSingleton
{
    virtual void PrintName(std::string prefix)
    {
        std::cout << prefix << " StupidSingletonMock" << std::endl;
    }
};

// dziedziczy tylko po to, zeby moc uzyc statycznej getPtr, mozna tez zrobic frienda w StupidSingletonPtr, ale po hoy (powiazanie z testami)
struct StupidSingletonInstanceSetter: StupidSingletonPtr
{
    static void setInstance(StupidSingleton* instance)
    {
        getPtr(&StupidSingleton::getInstance())->reset(instance);
    }
};

//#################### PODEJSCIE 3
// + prostota
// - trzeba ustawic w 1 miejscu i miec pewnosc ze nikt nie uzyje (inicjalizacja statycznej), ale i tak global pointery ustawiamy w konkretnym miejscu wiec nie wiem co to za problem
// + nie, muteksy sa niepotrzebne w koncu zakladamy ze ustawiamy na poczatku i potem juz nie.
// Problem bylby tylko wtedy, gdy inna klasa ma pole statycznie inicjalizowane i wtedy korzysta getInstance na przyklad:
// A::jakasStatycznaSkladowa(B::getInstance()); // boom- B jeszcze nie jest zainicjalizowane
struct Singleton
{
    static boost::scoped_ptr<Singleton> instance;
    
    static Singleton& getInstance()
    {
        return *instance.get();
    }
    
    virtual void PrintName(std::string prefix)
    {
        std::cout << prefix << " Singleton" << std::endl;
    }
    
    virtual ~Singleton(){}
    
    protected:
    Singleton(){}
    static void resetInstance(Singleton* inst)
    {
        instance.reset(inst);
    }
};

// jakby wczesniej ktos chcial zrobic getInstance() to bylaby klapa
boost::scoped_ptr<Singleton> Singleton::instance(new Singleton);

struct SingletonMock : Singleton
{
    virtual void PrintName(std::string prefix)
    {
        std::cout << prefix << " SingletonMock" << std::endl;
    }
    static void setSingletonInstance(Singleton* inst)
    {
        Singleton::resetInstance(inst);
    }
};

struct SingletonUser
{
    static void UseSingletons()
    {
        SharedSingleton::getInstance()->PrintName("SingletonUser");

        StupidSingleton::getInstance()->PrintName("SingletonUser");
        
        Singleton::getInstance().PrintName("SingletonUser");
    }
};

int main()
{
    SingletonUser::UseSingletons();
    
    // USTAWIANIE MOCKOW
    SharedSingleton::getInstance().reset(new SharedSingletonMock); // Kazdy moze zmienic instancje
    
    //StupidSingleton::getInstance().reset(new StupidSingletonMock); // nie mozna zmienic instancji - jedyna zaleta tego hujowego rozwiazania
    //StupidSingleton::getInstance().getPtr(); // protected
    //StupidSingletonPtr::getPtr(&StupidSingleton::getInstance()); //protected
    StupidSingletonInstanceSetter::setInstance(new StupidSingletonMock);
    
    //Singleton::resetInstance(new SingletonMock); // nie mozna
    SingletonMock::setSingletonInstance(new SingletonMock);
    
    // PO USTAWIENIU MOCKOW
    SingletonUser::UseSingletons();
}
