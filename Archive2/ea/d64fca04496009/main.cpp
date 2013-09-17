struct A
{
    explicit A(){}
};

void f(A){}

const struct default_t
{
     template<typename T>
     operator T() const {   return T{}; }
}default_{};

int main()
{
    //f({}); does NOT work
      f(default_);
}