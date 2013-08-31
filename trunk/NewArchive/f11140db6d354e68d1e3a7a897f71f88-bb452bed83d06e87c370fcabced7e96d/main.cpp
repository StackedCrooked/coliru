template < int i>
struct foo
{
};

template <int i> class myClass
{
  public:
    typedef int myVector_t;

    myClass();
    myVector_t myFunc();
};

template <int i>
myClass<i>::myClass()
{
  //blah
}

template <int i>
myClass<i>::myVector_t  myClass<i>::myFunc()        //<----- Line 10
{
  //blah
}

int main()
{
    myClass o;
}
