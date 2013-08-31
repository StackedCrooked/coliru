struct A { friend void operator<<(A,A){} };

int main()
{
    A hand, deck;
    int x = (A()<<A(), 42);
    1 ? hand<<deck : void();
    return 0 ? throw 1 : hand<<deck, 42;
}