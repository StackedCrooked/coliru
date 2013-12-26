int main()
{
    long variable = 0;
    ((&variable) % sizeof(long)) == 0;
}