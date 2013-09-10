template <typename> using lol = int; 

int main()
{
    return lol<struct fancy_int>{42};
}
