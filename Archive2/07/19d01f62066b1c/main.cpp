//In Foo.h
class foo
{
public:
    void fooFunction(); 
} *fooObject;

//In Main.cpp
int main()
{
	// Linker error in vs 2012 
	foo->fooFunction();
}

// However this will work without issue.
// Personally I think its vs
class foo
{
public:
	void fooFunction(); 
} *fooObject;

//In Main.cpp
int main()
{
	foo fooObject* = 0;
	foo->fooFunction();
}