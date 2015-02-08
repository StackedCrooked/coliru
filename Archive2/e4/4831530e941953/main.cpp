struct table
{
    struct id_tag;
    struct name_tag;
    
    template <typename...>
    struct indices{};
    
    static void foo()
    {
        indices<id_tag> i;
        
        (void)i;
    }
};

template <>
struct table::indices<table::id_tag> {};

template <>
struct table::indices<table::name_tag> {};

int main()
{
}