int x () { return 0; }

struct S
{
    S operator -- () {return *this;}
};

S s () { return {}; }


int main ()
{
    auto y = --x (); // does not compile
    auto t = --s (); // fine
}