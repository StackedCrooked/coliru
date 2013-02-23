template<unsigned I>
struct rank : rank<I+1>{};

template<>
struct rank<900>{};

static constexpr rank<0> select_overload{};

void foo(rank<0>);
void foo(rank<1>);
void foo(rank<2>);
void foo(rank<3>);
void foo(rank<4>);
void foo(rank<5>);
void foo(rank<6>);
void foo(rank<7>);
void foo(rank<8>);
void foo(rank<9>);
void foo(rank<10>);
void foo(rank<12>);
void foo(rank<13>);
void foo(rank<14>);
void foo(rank<15>);

int main()
{
    foo(select_overload);
}