template<class ptr_to_t>
void f(ptr_to_t x) {
    typedef ptr_to_t t; // does not compile
    t elem = *x;
}

int main()
{
    int five = 5;
    f<int*>(&five);
    return 0;
}