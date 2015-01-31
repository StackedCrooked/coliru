struct table
{
    struct id_tag;
    struct name_tag;
    
    template <typename...>
    struct indices;
};
    
template <>
struct table::indices<table::id_tag> {};

template <>
struct table::indices<table::name_tag> {};

int main()
{
}