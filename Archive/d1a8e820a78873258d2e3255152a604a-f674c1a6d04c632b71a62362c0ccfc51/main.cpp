
void foo(int&) {}


int main()
{
    int n;
    foo(n); // ok
    
    short s;
    foo(s); // error
}