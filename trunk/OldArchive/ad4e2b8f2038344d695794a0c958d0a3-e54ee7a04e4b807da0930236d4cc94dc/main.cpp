
constexpr unsigned mask(unsigned n)
{
    return (1 << n);
}

constexpr unsigned mask(unsigned head, unsigned ...tail)
{
    return mask(head) | mask(tail);
}

int main()
{
    return mask(1, 2, 3);
}