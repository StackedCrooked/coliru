int main()
{
    const int x = 0;
    *reinterpret_cast<int*>(x) = 3;
}