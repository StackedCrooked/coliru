#include <cstddef>

namespace {
    template<typename T>
    struct Foo
    {
        void bar(T*) {}
        void bar(nullptr_t) = delete;
    };
    
    template<typename T>
    void test()
    {
        T t;
        Foo<T> f;
        f.bar(&t);
        // FAILS: f.bar(0);
    }
}

#include <map>
#include <unordered_map>
#include <cassert>

namespace {

    template<typename K, typename V>
    struct OrderedMapMaker
    {
        typedef std::map<K, V> type;
    };
    
    template<typename K, typename V>
    struct UnorderedMapMaker
    {
        typedef std::unordered_map<K, V> type;
    };

    template<typename T, template<typename, typename> class MapMaker = OrderedMapMaker>
    struct Visited
    {
        typedef typename MapMaker<T*, bool>::type Map;
        Map objects;
      
        bool visit(int /* nullptr_t */) /* = delete */;
        
        void visit(T* t)
        {
            this->objects[t] = true;
        }
        
        bool visited(T* t) const
        {
            return this->objects.find(t) != this->objects.end();
        }
        
        static void test()
        {
            Visited<T> v;
            T d[2];
            v.visit(&d[0]);
            // FAILS to link: v.visit(0);
            assert(v.visited(&d[0]));
            assert(!v.visited(&d[1]));
        }
    };
}



int main()
{
    test<int>();
    Visited<double>::test();

}

