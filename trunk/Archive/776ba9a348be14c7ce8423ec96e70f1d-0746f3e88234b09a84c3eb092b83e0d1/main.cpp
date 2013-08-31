namespace Eigen {
    template <typename, int, int>
    class Matrix {};
}

template <int i> class myClass
{
  public:
    typedef Eigen::Matrix<double, i, 1> myVector_t;

    myClass();
    int myFunc();
};

template <int i>
myClass<i>::myClass()
{
  //blah
}

template <int i>
int myClass<i>::myFunc()        //<----- Line 10
{
  //blah
}
