unsigned product(unsigned n)
{
    return n;
}

unsigned product(unsigned head, unsigned ...tail)
{
    return head * product(tail);
}