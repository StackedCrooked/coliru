#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/read_dimacs.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/property_map/property_map.hpp>

namespace bmi = boost::multi_index;

namespace boost {
    template <> struct hash<default_color_type> : hash<int> {
    };
}

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> Traits;

struct VertexColor {
    Traits::vertex_descriptor vertex;
    boost::default_color_type color;
};

typedef boost::multi_index_container<
    VertexColor,
    bmi::indexed_by<
        bmi::hashed_non_unique<bmi::tag<struct by_color>,  bmi::member<VertexColor, boost::default_color_type, &VertexColor::color> >,
        bmi::ordered_unique   <bmi::tag<struct by_vertex>, bmi::member<VertexColor, Traits::vertex_descriptor, &VertexColor::vertex> >
    >
> smart_map;

struct bidi_color_map {
    typedef smart_map::index<by_vertex>::type impl_t;
    bidi_color_map(impl_t& ref) : ref_(&ref) {}
    impl_t       &get()       { return *ref_; }
    impl_t const &get() const { return *ref_; }
  private:
    impl_t* ref_;
};

namespace boost { 
    template <> struct property_traits<bidi_color_map> {
        typedef default_color_type          value_type;
        typedef default_color_type          reference;
        typedef Traits::vertex_descriptor   key_type;
        typedef read_write_property_map_tag category;
    };
}

boost::property_traits<bidi_color_map>::reference get(bidi_color_map const& idx, boost::property_traits<bidi_color_map>::key_type const& key) {
    auto it = idx.get().find(key);
    if (it != idx.get().end())
        return it->color;
    else
        throw std::range_error("key not found in index");
}

void put(bidi_color_map& idx, boost::property_traits<bidi_color_map>::key_type const& key, boost::property_traits<bidi_color_map>::value_type val) {
    auto it = idx.get().find(key);
    if (it != idx.get().end())
        idx.get().modify(it, [val](VertexColor& p) { p.color = val; });
    else
        idx.get().insert({key,val});
}

int main() {
    using namespace boost;

    typedef adjacency_list<
        listS, vecS, directedS, property<vertex_name_t, std::string>,
        property<edge_capacity_t, long,
        property<edge_residual_capacity_t, long, 
        property<edge_reverse_t, Traits::edge_descriptor> > > > Graph;

    Graph g;

    property_map<Graph, edge_capacity_t>::type capacity                   = get(edge_capacity, g);
    property_map<Graph, edge_reverse_t>::type rev                         = get(edge_reverse, g);
    property_map<Graph, edge_residual_capacity_t>::type residual_capacity = get(edge_residual_capacity, g);

    smart_map colorMap;
    bidi_color_map color_map(colorMap.get<by_vertex>());

    Traits::vertex_descriptor s, t;
    read_dimacs_max_flow(g, capacity, rev, s, t);

    std::vector<Traits::edge_descriptor> pred(num_vertices(g));
    long flow = edmonds_karp_max_flow(
            g, s, t, capacity, residual_capacity, rev,
            color_map, &pred[0]);

    std::cout << "c  The total flow:" << std::endl;
    std::cout << "s " << flow << std::endl << std::endl;

    std::cout << "c flow values:" << std::endl;
    graph_traits<Graph>::vertex_iterator u_iter, u_end;
    graph_traits<Graph>::out_edge_iterator ei, e_end;
    for (boost::tie(u_iter, u_end) = vertices(g); u_iter != u_end; ++u_iter)
        for (boost::tie(ei, e_end) = out_edges(*u_iter, g); ei != e_end; ++ei)
            if (capacity[*ei] > 0)
                std::cout << "f " << *u_iter << " " << target(*ei, g) << " " << (capacity[*ei] - residual_capacity[*ei])
                          << std::endl;

    for (auto const& e : colorMap.get<by_color>())  std::cout << "by_color:  " << e.vertex << " -> " << e.color << "\n";
    for (auto const& e : colorMap.get<by_vertex>()) std::cout << "by_vertex: " << e.vertex << " -> " << e.color << "\n";

    return EXIT_SUCCESS;
}
