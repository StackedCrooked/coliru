struct wat {
    const int& i;
};

int main()
{
    constexpr int i = 0;
    constexpr wat w { i };
    static_assert( w.i == 3, "" );
}