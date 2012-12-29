template<unsigned N, bool = (N%2 == 0)>
struct select
{
};

template<unsigned N>
struct select<N, true>
{
    void break_in_half() {}
};

template<unsigned N>
struct number : select<N>
{
};


int main()
{
    number<2>().break_in_half();
    number<4>().break_in_half();
    number<5>().break_in_half(); // !
}

