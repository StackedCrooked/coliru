

template<bool>
struct select_impl
{
};


template<>
struct select_impl<true>
{
    void break_in_half() {}
}


template<unsigned N>
struct select : select_impl<N%2 == 0>
{
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

