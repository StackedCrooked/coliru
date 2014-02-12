struct s { int i; };

template<const s* _arr>
class struct_array
{
public:
    static constexpr auto arr = _arr[0]; // works
    template<int >
    struct inner // line 9, without this struct, it works
    {    
    };
};

extern const s s_objs[] = {{ 42 }};

struct data
{
    static const s sobjs[1];
};

extern const s data::sobjs[1] = {{ 42 }};

int main()
{
    struct_array<s_objs> t_obj;
    struct_array<data::sobjs> t_obj2;
    return 0;
}