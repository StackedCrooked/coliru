template<unsigned ...positions>
struct MakeBitmask;

template<>
struct MakeBitmask<unsigned pos>
{
    enum { value = (1 << pos) };
};

template<>
struct MakeBitmask<unsigned head, unsigned ...tail>
{
    enum { value = MakeBitmask<head>::value | MakeBitmask<tail>::value };
};

int main()
{
        return MakeBitmask<0, 1, 2>::value;
}