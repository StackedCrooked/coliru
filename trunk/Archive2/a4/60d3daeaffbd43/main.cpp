void myfunc(bool (f)(const float &, const float &) )
{
    f(1,2);
}
typedef bool (f)(const float &, const float &) mytype;
