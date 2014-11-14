template<int B1, int B2>
class MyClass
{
    const double B = (B2 == 0) ? 0.0 : (double) B1 / (double) B2;
    // ...
};

MyClass<0, 0> myobj;