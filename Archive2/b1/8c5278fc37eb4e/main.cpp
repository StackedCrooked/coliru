int main()
{
    auto f = [](auto a){ return a; };
    auto ptm = &decltype(f)::operator();
}