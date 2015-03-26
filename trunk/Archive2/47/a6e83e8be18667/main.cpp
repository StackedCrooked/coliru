#include <iostream>

class Transformer
{
    void transform()
    {
        std::cout << "Transformer::transform()" << std::endl;
    }  
};

class Autobot : public Transformer
{
    void transform()
    {
        std::cout << "Autobot::transform()" << std::endl;
    }
};


class Decepticon : public Transformer
{
    void transform()
    {
        std::cout << "Decepticon::transform()" << std::endl;
    }
};

class OptimusPrime : public Autobot, public Decepticon
{
public:
    void transform(int)
    {
        std::cout << "OptimusPrime::transform(int)" << std::endl;
    }
};

int main()
{
    OptimusPrime op;
    op.transform(1);

}
