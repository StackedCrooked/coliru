template <int A, int B>
struct two_ints
{
    static constexpr int first = A < 100 ? A : -1;
    static constexpr int second = B < 100 ? B : -1;
};


template <typename T>
struct myPair
{
    T one;
    T two;
    template <int A, int B>
    constexpr myPair(two_ints<A, B>)
        : one(two_ints<A,B>::first), two(two_ints<A,B>::second){    }

    template <int A, int B>
    struct make_pair
    {
        static constexpr myPair<T> value = myPair<T>(two_ints<A,B>());
    };
};

int main()
{
    typedef myPair<long long int> int_pair;
    int_pair pairTwo((two_ints<67,45>()));
    int_pair pairThree(int_pair::make_pair<67,45>::value); //error here

    return 0;
}
