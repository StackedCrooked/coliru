template < typename Der >
struct CRTP
{
    typedef typename Der::type type;
};

struct der : CRTP<der>
{
    typedef int type;
};

int main()
{
    der d;
}
