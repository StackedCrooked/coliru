
constexpr unsigned mask(unsigned);
constexpr unsigned mask(unsigned){ return 0; }

int main()
{
    return mask(1);
}