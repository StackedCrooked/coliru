    #include <utility>

    struct X
    {
        explicit X (std::size_t) { }
    };

    int main()
    {
        X test { 0x34 };
    }