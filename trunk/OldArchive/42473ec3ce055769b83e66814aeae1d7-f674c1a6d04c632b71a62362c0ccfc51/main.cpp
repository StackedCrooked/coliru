#include <iostream>
#include <string>

// basisklasse
class Base {
 
public:
    virtual std::string ClassName() = 0;    // pure virtual
     Base(){ ++myCount; }
    ~Base(){ --myCount; }
    static int GetCount(){ return myCount; }
private:
    static int myCount;

};

int Base::myCount = 0; // init von myCount

// abgeleitete klasse von basisklasse
class Derived1 : public Base {
public:
    virtual ~Derived1(){} // virtual DTor, weil mit pointern gearbeitet wird
    virtual std::string ClassName() override    { return "Derived1"; }   
    void                SetLabel(std::string x) { myLabel = x;      }
    std::string         GetLabel()              { return myLabel;   }
    
private:
    std::string myLabel;
};

// abgeleitete klasse von derived1
class Derived2 : public Derived1 {
public:
    virtual ~Derived2(){} // virtual DTor, weil mit pointern gearbeitet wird
    virtual std::string ClassName() override    { return "Derived2"; }   
    void                SetLabel2(std::string x) { myLabel = x;      }
    std::string         GetLabel2()              { return myLabel;   }
    
private:
    std::string myLabel;
};


static void func(Base * base){
    std::cout << base->ClassName();
}

int main()
{
    // Base     *pBase = new Base();    => fehler da abstrakte klasse
    Derived1 derived;
    Derived1 *pDerived = new Derived1();
    Derived1 *pDerived_1_2 = new Derived2(); // funktioniert aber kein zugriff auf Derived2, nur infos von Derived1; umgekehrt nicht möglich
    
    
    derived.SetLabel("LabelDerived");
    std::cout << derived.GetLabel() << std::endl;
    std::cout << derived.GetCount() << std::endl;
    
    
    pDerived->SetLabel("LabelDerivedPointer");
    std::cout << pDerived->GetLabel() << std::endl;
    std::cout << pDerived->GetCount() << std::endl;
    func(pDerived);
    
    
    pDerived_1_2->SetLabel("Label_1_2");
    std::cout << std::endl << pDerived_1_2->GetLabel() << std::endl;
    
    // funktioniert nicht da infos über Derived2 fehlen
    // pDerived_1_2->SetLabel2("Label_1_2");
    // std::cout << pDerived_1_2->GetLabel2() << std::endl;
    
    std::cout << pDerived_1_2->GetCount() << std::endl;
    func(pDerived_1_2);
    
    delete pDerived; pDerived = 0;
    
    std::cout << std::endl << derived.GetCount() << std::endl;
    
    delete pDerived_1_2; pDerived_1_2 = 0;
    
    std::cout << derived.GetCount() << std::endl;
    std::cout << Base::GetCount()   << std::endl; // zugriff auf static GetCount
    

    return 0;
}
