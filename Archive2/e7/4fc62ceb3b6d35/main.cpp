#include <forward_list>
#include <type_traits>
#include <atomic>
#include <memory>
#include <mutex>

namespace Nano
{

// Somehow std::aligned_union is still missing from type_traits
// This implementation is not quite right... but works :D

template <typename... Type> struct max_alignment_of;

template <typename T, typename... Type> struct max_alignment_of<T, Type...>
{
    typedef T type;

    static constexpr std::size_t value =
        std::alignment_of<typename max_alignment_of<Type...>::type>::value >
        std::alignment_of<T>::value ?
        std::alignment_of<typename max_alignment_of<Type...>::type>::value :
        std::alignment_of<T>::value;
};
template <typename T> struct max_alignment_of<T>
{
    typedef T type;

    static constexpr std::size_t value = std::alignment_of<T>::value;
};
template <std::size_t N, typename... Type> struct aligned_union
{
    static constexpr std::size_t value = max_alignment_of<Type...>::value;

    typedef typename std::aligned_storage
        <sizeof(typename max_alignment_of<Type...>::type), value>::type type;
};

//------------------------------------------------------------------------------

template <typename T> class Singleton
{
    protected:

    Singleton() = default;
    Singleton(Singleton const&) = default;
    Singleton& operator= (Singleton const&) = default;

    public:

    static T& get()
    {
        static T s;
        return s;
    }
};

//------------------------------------------------------------------------------

template <typename T, std::size_t N = 8192>
class Pool_Allocator
{
    class Free_List : public Singleton<Free_List>
    {
        struct Node { Node* next = nullptr; };
        
        struct Pool
        {
            typename aligned_union<0, T, Node>::type data[N];
            
            Pool ()
            {
                for (auto& node : data)
                {
                    Free_List::get().push(std::addressof(node));
                }
            }
        };
        
        //----------------------------------------------------------------------
        
        std::forward_list<std::unique_ptr<Pool>> m_data;
        //std::atomic<Node*> m_head = ATOMIC_VAR_INIT(0);
        std::atomic<Node*> m_head = { nullptr };
        std::mutex m_mutex;
        
        // Out of memory, allocate and add a whole new pool
        // Depending on N this shouldn't be called too often
        void* next_pool_allocation()
        {
            if (std::unique_lock<std::mutex> lock { m_mutex, std::try_to_lock })
            {
                m_data.emplace_front(new Pool);
            }
            return next();
        }
        
        public:
        
        //----------------------------------------------------------------------
        
        void* next()
        {
            if (Node* node = m_head.load(std::memory_order_consume))
            {
                while (!m_head.compare_exchange_weak(node, node->next,
                    std::memory_order_release, std::memory_order_relaxed));
                    
                return reinterpret_cast<void*>(node);
            }
            return next_pool_allocation();
        }
        void push(void* temp)
        {
            Node* node = reinterpret_cast<Node*>(temp);
            node->next = m_head.load(std::memory_order_consume);
            
            while (!m_head.compare_exchange_weak(node->next, node,
                std::memory_order_release, std::memory_order_relaxed));
        }
    };

    //--------------------------------------------------------------------------

    struct Deleter
    {
        inline void operator()(T* instance)
        {
            instance->T::~T();
            Free_List::get().push(instance);
        }
    };

    public:

    typedef std::unique_ptr<T, Deleter> unique_ptr_t;
    typedef std::shared_ptr<T> shared_ptr_t;

    // Use placement new
    template <typename... Args>
    unique_ptr_t create_unique (Args&&... args)
    {
        return { new(Free_List::get().next())
           T(std::forward<Args>(args)...), Deleter() };
    }
    template <typename... Args>
    shared_ptr_t create_shared (Args&&... args)
    {
        return { new(Free_List::get().next())
           T(std::forward<Args>(args)...), Deleter() };
    }
};

} // namespace Nano ------------------------------------------------------------

struct Foo
{
    std::size_t data[4];
};

int main()
{
    Nano::Pool_Allocator<size_t> allocator;

    auto a = allocator.create_unique();
    auto b = allocator.create_shared();
}
