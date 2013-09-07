#include <type_traits>
#include <iostream>

namespace Nano
{

template <typename... Type>
struct max_alignment_of;

template <typename T, typename... Type>
struct max_alignment_of<T, Type...>
{
    typedef T type;

    static constexpr std::size_t value =
        std::alignment_of<typename max_alignment_of<Type...>::type>::value >
        std::alignment_of<T>::value?
        std::alignment_of<typename max_alignment_of<Type...>::type>::value :
        std::alignment_of<T>::value;
};

template <typename T>
struct max_alignment_of<T>
{
    typedef T type;

    static constexpr std::size_t value = std::alignment_of<T>::value;
};

template <std::size_t N, typename... Type>
struct aligned_union
{
    static constexpr std::size_t value = max_alignment_of<Type...>::value;

    typedef typename std::aligned_storage
        <sizeof(typename max_alignment_of<Type...>::type), value>::type type;
};

//------------------------------------------------------------------------------

namespace detail
{

struct free_list
{
    struct Node
    {
        Node* next = nullptr;
    };

    Node* head = nullptr;

    void* popf()
    {
        if (head)
        {
            Node* retval = head;
            head = head->next;
            return reinterpret_cast<void*>(retval);
        }
        return nullptr;
    }

    template <typename T>
    void* push(T* node)
    {
        Node* temp = reinterpret_cast<Node*>(node);
        temp->next = head;
        head = temp;

        return nullptr;
    }
};

} // namespace detail ----------------------------------------------------------

template <typename T, std::size_t N> class static_chunk
{
    typename aligned_union<N, T, detail::free_list::Node>::type m_data[N];

    detail::free_list m_free;

    public:

    static_chunk () // initialize the free list
    {
        for (auto& element : m_data)
        {
            m_free.push(&element);
        }
    }
    T* create_one() // pop a node address from the free list
    {
        return static_cast<T*>(m_free.popf());
    }
    T* remove_one(T* address) // push a node address to the free list
    {
        return static_cast<T*>(m_free.push(address));
    }
};

} // namespace Nano ------------------------------------------------------------

int main()
{
    Nano::static_chunk<std::size_t, 2> test;

    auto a1 = test.create_one();
    auto a2 = test.create_one();

    a1 = test.remove_one(a1);
    a2 = test.remove_one(a2);

    std::cout << __LINE__ << std::endl;
}
