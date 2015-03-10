#include <utility>
#include <tuple>
#include <vector>
#include <string>
#include <iostream>

template<typename Type> using alias = Type;

template<typename Element, typename... Keys>
struct indexed_vector {
    template<typename Key>
    using keyed_vector = std::pair<Key, std::vector<Element>>;
    
    std::tuple<keyed_vector<Keys>...> vecs;
    
    template<typename K, typename... Es>
    void set_at(K k, Es... es)
    {
        std::get<keyed_vector<K>>(vecs).first = std::move(k);
        std::get<keyed_vector<K>>(vecs).second = { std::move(es)... };
    }
    
    template<std::size_t... Is>
    void info(std::index_sequence<Is...>) const
    {
        alias<char[]> { (vec_info(std::get<Is>(vecs)), void(), '\0')... };
    }
    
    void info() const
    { info(std::make_index_sequence<sizeof...(Keys)> {}); }
    
    template<typename K>
    static void vec_info(keyed_vector<K> const& v) 
    {
        std::cout << v.first << ":\n";
        std::cout << v.second.size() << '\n';
    }
};

int main()
{
    using namespace std::literals::string_literals;
    indexed_vector<int, std::string, int> ivecs;
    
    // put 4 elements at key "hello"
    ivecs.set_at("hello"s, 4, 8, 12, 16);
    // put 2 elements at key 5
    ivecs.set_at(5, 8, 8);
    
    // or did we?
    ivecs.info();
}
