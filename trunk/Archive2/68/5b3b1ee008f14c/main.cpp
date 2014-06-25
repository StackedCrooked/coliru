
struct C
{
    static const void* noop1 = reinterpret_cast<const void*>(0x1);
    static constexpr const void* noop2 = static_cast<const void*>(0x1);
};

int main()
{

}