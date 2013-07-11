

/** PSEUDO PSEUDO CODE */


template<unsigned N, typename ...Args>
auto unhide(const std::tuple<Args>&& args...)
{
    return unhide(N - 1, tail(args)...);
    
}

template<typename ...Args>
auto unhide<0, Args...>(const std::tuple<Args>&& args...)
{
    return make_tuple(unhide(head(args)), args...);
    
}

template<typename T>
auto unhide(hidden<T> t)
{
    return t.get();
}

