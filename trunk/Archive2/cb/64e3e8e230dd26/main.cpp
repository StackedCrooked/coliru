int main()
{
    auto l = [](auto...){};
    l(1,2,3);
    l("hi", 3.14, false);
}