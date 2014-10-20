struct R
{
    int* begin;
    int* end;
    friend int* begin(const R& r) { return r.begin; }
    friend int* end(const R& r) { return r.end; }
};

int main()
{
    R r;
#if 1
    for (auto& x : r) ;
#else
    {
        auto && __range = (r);
        for ( auto __begin = begin(__range),
                __end = end(__range);
                __begin != __end;
                ++__begin ) {
            auto& x = *__begin;
            ;
        }
    }
#endif
}
