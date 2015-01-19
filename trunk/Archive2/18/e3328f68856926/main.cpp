template <typename MemberType>
struct Holder
{
    static MemberType member;
};

template <typename MemberType>
auto Holder<MemberType>::member = 55;

int main()
{
}