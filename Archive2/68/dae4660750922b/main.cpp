#include <unordered_set>
#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>

struct NodeProperty {
    std::string FirstName;
    std::string LastName;
};

namespace std {
    template <> struct hash<NodeProperty> {
        std::hash<std::string> hasher;
        size_t operator()(const NodeProperty &key) const { return hasher(key.FirstName) ^ hasher(key.LastName); }
    };
}

namespace std {
    template <typename V> struct hash<boost::detail::stored_edge<V> > {
        std::size_t operator()(const boost::detail::stored_edge<V> &e) const { return hash<V>()(e.m_target); }
    };

    template <typename V, typename P> struct hash<boost::detail::stored_edge_property<V, P> > {
        std::size_t operator()(const boost::detail::stored_edge_property<V, P> &e) const { return hash<V>()(e.m_target); }
    };

    template <typename V, typename I, typename P> struct hash<boost::detail::stored_edge_iter<V, I, P> > {
        std::size_t operator()(const boost::detail::stored_edge_iter<V, I, P> &e) const { return hash<V>()(e.m_target); }
    };
}

namespace boost {
    struct std_unordered_setS {};

    template <class ValueType> struct container_gen<std_unordered_setS, ValueType> {
        typedef std::unordered_set<ValueType> type;
    };

    template <> struct parallel_edge_traits<std_unordered_setS> { typedef disallow_parallel_edge_tag type; };
}

using namespace boost;

int main() {
#ifdef USE_STD
    typedef adjacency_list<std_unordered_setS, std_unordered_setS, bidirectionalS, NodeProperty> Graph;
#else
    typedef adjacency_list<hash_setS, hash_setS, bidirectionalS, NodeProperty> Graph;
#endif

    // typedef graph_traits<Graph>::vertex_descriptor Vertex;
}
