#include <cstdio>
using std::printf;

// Parent class:

class CLassA
{
public:
    typedef void  (CLassA::*Method_t)(int x, int y);
    int ForAll(Method_t action, int y);
    virtual void MethodA(int x);
    virtual void MethodA(int x, int y);
};

int CLassA::ForAll(Method_t action, int x)
{
    (this->*action)(x, x);
    return x;
}

void CLassA::MethodA(int x)
{
    printf("CLassA::MethodA: %d\n", x);
    ForAll(&CLassA::MethodA, x);
}

void CLassA::MethodA(int x, int y)
{
    printf("\tCLassA::MethodA: %d %d\n", x, y);
}

// My first override:

class CLassB : public CLassA
{
public:
    void MethodA(int x, int y) override;
};

void CLassB::MethodA(int x, int y)
{
    printf("\tCLassB::MethodA: %d %d\n", x, y);
}

// My second override:

class CLassC : public CLassB
{
public:
    void MethodA(int x) override;
};

void CLassC::MethodA(int x)
{
    printf("CLassC::MethodA: %d\n", x);
    ForAll(&CLassC::CLassA::MethodA, x);
}

// The calling routine:

int main(int argc, char** argv)
{
    CLassA A;
    A.MethodA(1);

    CLassB B;
    B.CLassA::MethodA(2);

    CLassC C;
    C.MethodA(3);
    return 0;
}
