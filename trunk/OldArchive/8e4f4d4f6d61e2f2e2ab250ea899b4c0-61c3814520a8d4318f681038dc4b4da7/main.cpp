template<typename T> void print();

int main()
{
    print<decltype(new int[1])>();
}