template <int ...I>
struct index_sequence {};

template <int ...I, int ...J>
void foo(index_sequence<I...>, index_sequence<I..., J...>)
{}

int main()
{
    foo(index_sequence<0>{}, index_sequence<0, 1>{});
}