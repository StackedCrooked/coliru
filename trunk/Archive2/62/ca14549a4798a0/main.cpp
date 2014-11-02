#include <boost/foreach.hpp>
#include <boost/bimap.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/bimap/list_of.hpp>
#include <boost/bimap/set_of.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/read_dimacs.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/unordered_map.hpp>

int main() {
    using namespace boost;

    typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
    typedef adjacency_list<
        listS, vecS, directedS, property<vertex_name_t, std::string>,
        property<edge_capacity_t, long,
        property<edge_residual_capacity_t, long, 
        property<edge_reverse_t, Traits::edge_descriptor> > > > Graph;

    Graph g;

    property_map<Graph, edge_capacity_t>::type capacity                   = get(edge_capacity, g);
    property_map<Graph, edge_reverse_t>::type rev                         = get(edge_reverse, g);
    property_map<Graph, edge_residual_capacity_t>::type residual_capacity = get(edge_residual_capacity, g);

    typedef boost::bimap<bimaps::list_of<default_color_type>, bimaps::set_of<Traits::vertex_descriptor> > smart_map;
    smart_map colorMap;
    boost::associative_property_map<smart_map::right_map> color_map(colorMap.right);

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

    for (auto const& e : colorMap.left)  std::cout << "ltr: " << e.first << " -> " << e.second << "\n";
    for (auto const& e : colorMap.right) std::cout << "rtl: " << e.first << " -> " << e.second << "\n";

    return EXIT_SUCCESS;
}
