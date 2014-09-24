template<class B, int N>
class Base;

template<class B>
class Base<B, 0>
{
public:
    static constexpr B stfu{};
    constexpr auto& back() { return const_cast<B&>(stfu); }
};

template<int N>
class BitSet: public Base<unsigned long long, N> {};

template<class B>
void foo(B& /* never accessed */)
{
    // no-op    
}

int main() 
{
    BitSet<0> b;
    foo(b.back());
}
