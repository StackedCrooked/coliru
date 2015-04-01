#include <boost/graph/adjacency_list.hpp>
#include <iostream>

struct Vertex {
    int id;
    const char* name;

    Vertex(int i = -1, const char* name = "default") : id(i), name(name) {}
};

template <typename It> boost::iterator_range<It> mir(std::pair<It, It> const& p) {
    return boost::make_iterator_range(p.first, p.second);
}
template <typename It> boost::iterator_range<It> mir(It b, It e) {
    return boost::make_iterator_range(b, e);
}

typedef typename boost::adjacency_list<
        boost::vecS, boost::vecS,
        boost::undirectedS,
        Vertex,                                      // bundled properties (id, name)
        boost::property<boost::edge_weight_t, float> // interior property
    > Graph;

void boostSampleGraph() {
    Graph graph;

    auto Jeanie   = add_vertex(Vertex { 0, "Jeanie" },   graph);
    auto Debbie   = add_vertex(Vertex { 1, "Debbie" },   graph);
    auto Rick     = add_vertex(Vertex { 2, "Rick" },     graph);
    auto John     = add_vertex(Vertex { 3, "John" },     graph);
    auto Amanda   = add_vertex(Vertex { 4, "Amanda" },   graph);
    auto Margaret = add_vertex(Vertex { 5, "Margaret" }, graph);
    auto Benjamin = add_vertex(Vertex { 6, "Benjamin" }, graph);

    add_edge(Jeanie, Debbie,   0.5f, graph);
    add_edge(Jeanie, Rick,     0.2f, graph);
    add_edge(Jeanie, John,     0.1f, graph);
    add_edge(Debbie, Amanda,   0.3f, graph);
    add_edge(Rick,   Margaret, 0.4f, graph);
    add_edge(John,   Benjamin, 0.6f, graph);

    /* vertex iterator */
    using vertex_descriptor = boost::graph_traits<Graph>::vertex_descriptor;

    std::cout << "# of vertices: " << num_vertices(graph) << "\n";
    std::cout << "# of edges:    " << num_edges(graph)    << "\n";

    std::set<vertex_descriptor> to_remove;

    /* iterator throught the graph  */
    for (auto self : mir(vertices(graph)))
    {
        std::cout << graph[self].name << (boost::empty(mir(out_edges(self, graph)))? " has no children " : " is the parent of ");

        for(auto edge : mir(out_edges(self, graph))) {
            auto weight    = boost::get(boost::edge_weight, graph, edge);
            auto mid_point = target(edge, graph);

            if (to_remove.count(mid_point)) // already elided
                break;

            if (weight > 0.3f) {
                std::set<vertex_descriptor> traversed;
                for (auto hop : mir(out_edges(mid_point, graph))) {
                    auto hop_target = target(hop, graph);

                    if (hop_target != self)
                        add_edge(self, hop_target, graph);
                    std::cout << "\n DEBUG: " << graph[self].name << "  " << graph[mid_point].name << "  " << graph[hop_target].name << " ";
                }
                std::cout << "\n";

                clear_vertex(mid_point, graph);
                to_remove.insert(mid_point);
            }

            std::cout << graph[mid_point].name;
        }

        std::cout << "\n\n";
    }

    for(auto vd : to_remove)
    {
        clear_vertex(vd, graph);
        remove_vertex(vd, graph);
    }

    std::cout << "# of vertices: " << num_vertices(graph) << "\n";
    std::cout << "# of edges:    " << num_edges(graph)    << "\n";
}

int main() {
    boostSampleGraph();
}
