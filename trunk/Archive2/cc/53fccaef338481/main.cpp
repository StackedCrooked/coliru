#include <iostream>

namespace colby
{


template <typename T1, typename T2>
struct pair
{
    T1 first;
    T2 second;

    pair() {}

    template <typename C1, typename C2>
    pair(C1 f, C2 s) :
        first( f ),
        second(s)
    {}

    template <typename O1, typename O2>
    pair( const pair<O1, O2>& other ) :
        first(other.first),
        second(other.second)
    {}

    template <typename O1, typename O2>
    pair& operator=( const pair<O1, O2>& other )
    {
        first = other.first;
        second = other.second;
        return *this;
    }
};


template <typename T1, typename T2>
pair<T1, T2> make_pair( T1 first, T2 second )
{
    return pair<T1, T2>( first, second );
}


struct LessThan
{
    template <typename T1, typename T2>
    int operator()( const T1& left, const T2& right )
    {
        if ( left == right ) return 0;
        if ( left > right ) return -1;
        return 1;
    }
};


template <typename Key, typename Value, typename Comparator = LessThan>
class Map
{
public:
    typedef pair<const Key, Value> value_type;
    typedef value_type& reference_type;
    typedef value_type* pointer_type;

private:
    struct Node
    {
        pointer_type data = nullptr;
        Node* left = nullptr;
        Node* right = nullptr;

        ~Node() { if (data) delete data; }
    };

    Node* _root = nullptr;
    Comparator _comp;

    pair<int, Node*> _find_key( const Key& key )
    {
        if ( _root == nullptr ) return make_pair(2, nullptr);
        Node* to_check = _root;
        while ( 1 )
        {
            int compare_res = _comp( key, to_check->data->first );
            if ( compare_res == 0 ) return make_pair( 0, to_check );
            if ( compare_res == 1 )
            {
                if ( to_check->left == nullptr ) return make_pair(-1, to_check);
                to_check = to_check->left;
                continue;
            }
            if ( compare_res == -1 )
            {
                if ( to_check->right == nullptr ) return make_pair(1, to_check);
                to_check = to_check->left;
                continue;
            }
        }
    }

    pair<int, Node*> _find_value( const value_type& val )
    {
        return _find_key( val.first );
    }

    void _insert_node( Node*& ptr, const value_type& val )
    {
        ptr = new Node;
        ptr->data = new value_type( val );
    }

public:
    Map() {}

    bool insert( const value_type& val )
    {
        auto pair = _find_value( val );
        if ( pair.second == nullptr ) _insert_node( _root, val );
        if ( pair.first == -1 ) _insert_node( pair.second->left, val );
        if ( pair.first == 1 ) _insert_node( pair.second->right, val );
        if ( pair.first == 0 ) return false;
        return true;
    }

    bool insert( const Key& key, const Value& value )
    {
        return insert( colby::make_pair( key, value ) );
    }

    pointer_type find(const Key& k)
    {
        auto res = _find_key( k );
        if ( res.first == 0 ) return res.second->data;
        return nullptr;
    }
};

}

using std::cout;
using std::endl;

int main()
{
    colby::Map<std::string, int> map;
    auto b = map.insert( "Hai", 121 );
    cout << b << endl;
    b = map.insert( "Hai", 11 );
    auto found = map.find( "Hai" );
    cout << found->second << endl;
    return 0;
}

