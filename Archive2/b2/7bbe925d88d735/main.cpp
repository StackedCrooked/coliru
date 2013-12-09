void f(int&, char**&){}

int main()
{
    int argc = 2;
    char* argv[] = { "", "", nullptr };
    f(argc, argv); 
    //@VS2013 error: cannot convert argument 2 from 'char *[3]' to 'char **&'
    //@GCC error: invalid initialization of non-const reference of type 'char**&' from an rvalue of type 'char**'
    return 0;
}