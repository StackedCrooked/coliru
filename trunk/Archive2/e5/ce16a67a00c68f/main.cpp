struct list {
    constexpr list() = default;
};

int main()
{
    constexpr list l = list {};
}