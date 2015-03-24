struct Mgr;

template <typename T>
struct Grr
{
    Mgr* mgr;
    
    void foo()
    {
        mgr->fuckoff();
    }
};

struct Mgr
{
    void fuckoff() {}
};

int main()
{
    Grr<char> x;
    x.foo();
}