template<typename T>
T implicit_()
{
    return true;
}

template<typename T>
T explicit_()
{
    return T(true);
}

int main()
{
    //implicit_<void>(); - error
    explicit_<void>();
}