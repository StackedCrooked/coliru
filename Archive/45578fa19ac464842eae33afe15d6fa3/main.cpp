template<unsigned N, bool = (N%2 == 0)>
struct select
{
};

template<unsigned N>
struct select<N, true>
{
    select<N/2> break_in_half() { return select<N/2>(); }
};

template<unsigned N>
struct number : select<N>
{
};


int main()
{
    number<1> n1 = number<2>().break_in_half();
    n1.break_in_half();
}

