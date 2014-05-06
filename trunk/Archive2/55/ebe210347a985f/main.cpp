template <class T>
struct Foo
{
    std::vector<T> vec;

    std::vector<T> getVector() && {
        // fill vector if empty
        // and some other work
        return std::move(vec);
    }

    std::vector<T> getVectorAndMore() &&
    {
        // do some more work
        return getVector(); // not compile
       // return std::move(*this).getVector(); // seems wrong to me
    }
};

int main()
{
    Foo<int> foo;

    auto vec = std::move(foo).getVectorAndMore();
}