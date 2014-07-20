#include <iostream>

using namespace std;

const int LENGTH = 1024;

class BigDataA
{
public:
    BigDataA() : a(string())
    {
        cout << "Default constructor of BigDataA called" << endl;
        for (int i = 0; i < LENGTH; ++i)
        {
            a += 'a';
        }
    }
    
    ~BigDataA()
    {
        cout << "Destructor of BigDataA called" << endl;
    }

    BigDataA(const BigDataA & rhs) : a(rhs.a)
    {
        cout << "Copy constructor of BigDataA called" << endl;
    }
    
    BigDataA(BigDataA && rhs) : a(move(rhs.a))
    {
        cout << "Move constructor of BigDataA called" << endl;
    }
    
    BigDataA(const string & rhs) : a(rhs)
    {
        cout << "Copy semantics constructor of BigDataA called" << endl;
    }
     
    BigDataA(string && rhs) : a(move(rhs))
    {
        cout << "Copy semantics constructor of BigDataA called" << endl;
    }
    
public:
    string getA()
    {
        return a;
    }
   
private:
    string a;
};


class BigDataB
{
public:
    BigDataB() : b(string())
    {
        cout << "Default constructor of BigDataB called" << endl;
        for (int i = 0; i < LENGTH; ++i)
        {
            b += 'b';
        }
    }
    
    ~BigDataB()
    {
        cout << "Destructor of BigDataB called" << endl;
    }

    BigDataB(const BigDataB & rhs) : b(rhs.b)
    {
        cout << "Copy constructor of BigDataB called" << endl;
    }
    
    BigDataB(BigDataB && rhs) : b(move(rhs.b))
    {
        cout << "Move constructor of BigDataB called" << endl;
    }
    
    BigDataB(const string & rhs) : b(rhs)
    {
        cout << "Copy semantics constructor of BigDataB called" << endl;
    }
     
    BigDataB(string && rhs) : b(move(rhs))
    {
        cout << "Copy semantics constructor of BigDataB called" << endl;
    }
    
public:
    string getB()
    {
        return b;
    }
   
private:
    string b;
};


// template wrapper combining two data types, here BigDataA and BigDataB
template<typename T1, typename T2>
class Combiner
{
public:
    Combiner() : aData(), bData()
    {
        cout << "Default Combiner constructor called" << endl;
    }
    
    ~Combiner()
    {
        cout << "Combiner destructor called" << endl;
    }
    
    Combiner(const Combiner & rhs) 
    : aData(rhs.aData)
    , bData(rhs.bData)
    {
        cout << "Copy constructor of Combiner called" << endl;
    }
    
    Combiner(Combiner && rhs) 
    : aData(move(rhs.aData))
    , bData(move(rhs.bData))
    {
        cout << "Move constructor of Combiner called" << endl;
    }
    
    // Something missing here???
    
public:
    T1 getAdata()
    {
        return aData;
    }
    
    T2 getBdata()
    {
        return bData;
    }
    
private:
    T1 aData;
    T2 bData;
};


int main()
{
    cout << "Create comb1" << endl;
    Combiner<BigDataA, BigDataB> comb1;
    
    cout << "Create comb2" << endl;
    Combiner<BigDataA, BigDataB> comb2(comb1);
    
    cout << "Create comb3" << endl;
    Combiner<BigDataA, BigDataB> comb3(move(comb1));
    
    cout << "Create a" << endl;
    BigDataA a = comb1.getAdata();
    
    cout << "Create b" << endl;
    BigDataB b = comb1.getBdata();
    
    cout << "Now what???" << endl;
    Combiner<BigDataA, BigDataB> comb4(a, b);
    Combiner<BigDataA, BigDataB> comb5(comb3.getAdata(), comb3.getBdata());
    
    cout << "Even worse???" << endl;
    Combiner<BigDataA, BigDataB> comb6(a, comb3.getBdata());
    Combiner<BigDataA, BigDataB> comb7(comb3.getAdata(), b);   
    
    // What if Combiner combines even more types of data???
    
   cout << "Ok, destroy every thing" << endl;
   return 0;
}
