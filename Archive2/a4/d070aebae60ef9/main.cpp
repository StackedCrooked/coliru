struct T
{
    ~T()
    try
    {
    }catch(...) {}
};

int main()
{
    T t;
}