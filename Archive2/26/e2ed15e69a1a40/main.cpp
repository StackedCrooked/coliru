struct M;

template <typename Mgr>
struct Grr
{
    Mgr* mgr;
    
    void foo()
    {
        mgr->fuckoff();
    }
};

struct M
{
    void fuckoff() {}
};

int main()
{
    Grr<M> x;
    x.foo();
}