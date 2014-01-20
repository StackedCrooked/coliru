template<int Index, typename Tag, typename Value>
struct tagged_tuple_item {
    Value value;
};

template<typename Tags, typename Values>
struct tagged_tuple
: tagged_tuple_item<0, Tags, Values> {
    explicit tagged_tuple(Values values)
        : tagged_tuple_item<0, Tags, Values> { values }
    {}

    template<int Index, typename Tag, typename Value>
    static tagged_tuple_item<Index, Tag, Value> const& upcast_by_index(tagged_tuple_item<Index, Tag, Value> const& item)
    { return item; }

    template<int Index, typename T, typename V>
    friend auto get(tagged_tuple<T, V> const& tuple)
    -> decltype( tagged_tuple<T, V>::template upcast_by_index<Index>(tuple).value )
    { return tagged_tuple<T, V>::template upcast_by_index<Index>(tuple).value; }
};

template<typename Tags, typename Values>
tagged_tuple<Tags, Values> tagged(Values values)
{ return tagged_tuple<Tags, Values> { values }; }

int main()
{
    auto t = tagged<double*>(4);
    &get<0>(t);
}