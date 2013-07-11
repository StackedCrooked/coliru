struct whatever {};

template < template <typename, typename, typename> class FOX, typename bat>
struct wulf {};

template <typename A, typename B, typename C = whatever>
struct box;

template <typename A, typename B>
struct box<A, B, whatever> {};

template <typename A, typename B, typename C>
struct box : wulf<box, C> {};

int main(void)
{
return 0;
}