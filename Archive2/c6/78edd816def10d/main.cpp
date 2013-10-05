#include <iostream>

template<std::size_t N>
class index
{
    public:

        index() = default;
        index(const index<N>& other) = default;
        index(index<N>&& other) = default;

        template<typename... Indices>
        index(Indices... indices)
        {
            static_assert(sizeof...(Indices) == N,
                          "Wrong number of arguments to construct the index.");
            _build(indices...);
        }

        auto operator=(const index<N>& other)
            -> index<N>& = default;
        auto operator=(index<N>&& other)
            -> index<N>& = default;

        auto operator[](std::size_t ind) const
            -> std::size_t
        {
            return _indices[ind];
        }

    private:

        template<typename... Args>
        auto _build(std::size_t head, Args... tail)
            -> void
        {
            _indices[N-sizeof...(Args)-1] = head;
            _build(tail...);
        }
        auto _build(std::size_t head)
            -> void
        {
            _indices[N-1] = head;
        }

        // Member indices
        std::size_t _indices[N];
};

template<std::size_t N>
auto operator==(const index<N>& lhs, const index<N>& rhs)
    -> bool
{
    for (std::size_t i = 0 ; i < N ; ++i)
    {
        if (lhs[i] != rhs[i])
        {
            return false;
        }
    }
    return true;
}

template<std::size_t N>
auto operator!=(const index<N>& lhs, const index<N>& rhs)
    -> bool
{
    return !(lhs == rhs);
}


int main()
{
    index<3> id = { 2, 5, 6 };
}
