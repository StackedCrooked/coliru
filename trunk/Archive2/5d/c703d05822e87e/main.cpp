
struct foo_t{
    //using decl_type = int;
    };
    
struct bar_t
    {
    template <typename value_type> 
    typename value_type::decl_type operator()( value_type && rref ) 
        { 
        using decl_type = typename value_type::decl_type;
        return decl_type();
        }
    };

int main()
{
bar_t b;
b( foo_t() ); 
}
