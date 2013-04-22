template<typename T>
struct Foo
{
    void Add( const T& Bar ) { printf(Bar); }
};

int main()
{
Foo<char*> foo;
const char* name = "FooBar"; 
foo.Add(name);                 // Causes error
}