struct X { 
    X()                    { std::cout << __PRETTY_FUNCTION__ << "\n"; } 
    ~X()                   { std::cout << __PRETTY_FUNCTION__ << "\n"; } 
    X(X const&)            { std::cout << __PRETTY_FUNCTION__ << "\n"; } 
    X(X&&)                 { std::cout << __PRETTY_FUNCTION__ << "\n"; } 
    X& operator=(X const&) { std::cout << __PRETTY_FUNCTION__ << "\n"; } 
    X& operator=(X&&)      { std::cout << __PRETTY_FUNCTION__ << "\n"; } 
};

int main()
{
    auto ptr = funky_ptr<X>(new X);

    auto b = ptr;
}
