#include <iostream>

struct log
{
    static void subCalculate(double& x)
    {
        std::cout << "Doing the calculation" << std::endl; 
    }
};

struct doNothing
{
    static void subCalculate(double& x)
    {
        // Do nothing. 
    }
};

struct calculate
{
    static void subCalculate(double& x)
    {
        x = x * x; 
    }
};

struct loggedCalculation 
: 
    public log,
    public calculate
{
    void subCalculate(double& x)
    {
        log::subCalculate(x);
        calculate::subCalculate(x);  
    }
};

template<
    typename Policy
>
class EncapsulatedAlgorithm
: 
    public Policy
{
    double x = 0; 

    public: 
        using Policy::subCalculate; 

        void calculate()
        {
            Policy::subCalculate(x); 
        }

    protected:

        ~EncapsulatedAlgorithm () = default;
};

typedef EncapsulatedAlgorithm<doNothing> nothingDone; 
typedef EncapsulatedAlgorithm<calculate> calculationDone; 
typedef EncapsulatedAlgorithm<loggedCalculation>  calculationLogged; 

int main(int argc, const char *argv[])
{
    nothingDone n; 
    n.calculate(); 

    calculationDone c; 
    c.calculate();
    
    calculationLogged l; 
    l.calculate(); 

    return 0;
}
