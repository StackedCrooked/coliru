template<class Tit, class Tf>
void algorithm(Tit it1, Tit it2, Tf fun)
{
    /*...*/
    fun(*it1);
    /*...*/
}

constexpr struct little_algorithm_t
{
    template <class T>
    T operator() (T t) const
    {
      return 2 * t;
    }
} little_algorithm{};

int main()
{
    int x[10];
    algorithm(x, x + 10, little_algorithm);
}