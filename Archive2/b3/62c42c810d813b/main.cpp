// used with custom type
struct mytype
{
    ...
    mytype ( unsigned long long );
};
mytype operator"" _mytype ( unsigned long long n )
{
    return mytype(n);
}
...
mytype x = 123_mytype;