#include <list>
#include <utility>
template<class K, class V>
struct test {
    typedef std::pair<const K, V> value_type;
    typedef std::list<value_type> list_type;
    typedef typename list_type::iterator iterator;
    typedef typename list_type::const_iterator const_iterator;
  
    iterator begin() noexcept { return m_l.begin(); }
    const_iterator begin() const noexcept { return m_l.begin(); }
    iterator end() noexcept { return m_l.end(); }
    const_iterator end() const noexcept { return m_l.end(); }
    
    list_type m_l;
};

int main() {
    test<int, int> t;
    t.m_l.emplace_back(10, 10);
    t.m_l.emplace_back(10, 20);
    for(auto it = t.begin(); it != t.end(); it++){
        it->second = 15;
        //it->first = 10;
    }
}