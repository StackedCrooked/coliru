constexpr int sqrt(int param)
{
    if(param < 0) throw "moo!";
    
    return param;
}

int main()
{
    constexpr auto x = sqrt(1);
    constexpr auto y = sqrt(-1);
}