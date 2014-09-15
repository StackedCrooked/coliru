#include <iostream>
#include <atomic>
#include <memory>
#include <tuple>

template<typename T>
struct Allocator
{
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T value_type;

    template<typename U>
    struct rebind {typedef Allocator<U> other;};

    Allocator() throw() {};
    Allocator(const Allocator& other) throw() {};

    template<typename U>
    Allocator(const Allocator<U>& other) throw() {};

    template<typename U>
    Allocator& operator = (const Allocator<U>& other) { return *this; }
    Allocator<T>& operator = (const Allocator& other) { return *this; }
    ~Allocator() {}

    pointer allocate(size_type n, const void* hint = 0)
    {
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    void deallocate(T* ptr, size_type n)
    {
        ::operator delete(ptr);
    }
};

template <typename T, typename U>
inline bool operator== (const Allocator<T>&, const Allocator<U>&)
{
    return true;
}

template <typename T, typename U>
inline bool operator!= (const Allocator<T>& a, const Allocator<U>& b)
{
    return !(a == b);
}

template <typename Key, typename Val>
class RCU_BinaryTree
{
    struct Node;

    using SharedNode = std::shared_ptr<Node>;
    using WeakNode = std::weak_ptr<Node>;

    struct Node
    {
        SharedNode l_child;
        SharedNode r_child;

        Key key;
        Val val;

        Node () = default;
        Node (Key const& k, Val const& v): key(k), val(v){}
    };

    //Allocator<Node> m_alloc;
	SharedNode m_root;

	void _insert(Key const& key, Val const& val, SharedNode& node)
	{
		using namespace std;

		if (node == nullptr)
		{
            node = make_shared<Node>(key, val);
            //node = allocate_shared<Node>(m_alloc, key, val);
		}
		else if (key < node->key)
		{
			_insert(key, val, node->l_child);
		}
		else if (key > node->key)
		{
			_insert(key, val, node->r_child);
		}
	}

	template <typename L>
    void _inorder(L&& lambda, SharedNode node)
    {
        if (node)
        {
            _inorder(lambda, node->l_child);
            lambda(node->key, node->val);
            _inorder(lambda, node->r_child);
        }
    }

    public:

    template <typename L>
    void inorder(L&& lambda)
    {
        _inorder(lambda, m_root);
    }

	void insert(Key const& key, Val const& val)
	{
		_insert(key, val, m_root);
	}
};

int main()
{
    using namespace std;

    RCU_BinaryTree<size_t, double> tree;

    cout << sizeof(RCU_BinaryTree<size_t, double>) << endl;

    auto a = [](size_t b, double c)
    {
        cout << b << ", " << c << endl;
    };

    tree.insert(1, 1.1);
    tree.insert(2, 2.2);
    tree.insert(3, 3.3);

    tree.inorder(a);
    cout << endl;

    tree.insert(3, 4.4);

    tree.inorder(a);
}
