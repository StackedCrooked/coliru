#include <boost/graph/graphviz.hpp>
#include <boost/graph/random.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <string>
#include <tuple>
#include <iostream>
#include <iomanip>
#include <map>
#include <random>
#include <cmath>
#include <fstream>
#include <utility>
#include <boost/graph/iteration_macros.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/random.hpp>

namespace b = boost;

namespace {
    b::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<int> uniform_dist(1, 100);
}

struct vert {
    std::string name;
};

struct edge {
    int capacity = uniform_dist(rng);
    int weight   = uniform_dist(rng);
};

template <class WeightMap, class CapacityMap> class edge_writer {
  public:
    edge_writer(WeightMap w, CapacityMap c) : wm(w), cm(c) {}
    template <class Edge> void operator()(std::ostream &out, const Edge &e) const {
        out << "[label=\"" << wm[e] << "\", taillabel=\"" << cm[e] << "\"]";
    }

  private:
    WeightMap wm;
    CapacityMap cm;
};

template <class WeightMap, class CapacityMap>
inline edge_writer<WeightMap, CapacityMap> make_edge_writer(WeightMap w, CapacityMap c) {
    return edge_writer<WeightMap, CapacityMap>(w, c);
}

int main() {
    typedef b::adjacency_list<b::listS, b::vecS, b::undirectedS, vert, edge> Graph;
    Graph g;

    b::generate_random_graph(g, 10 /*100*/, 5 /*20*/, rng);

    write_graphviz(std::cout, g, boost::make_label_writer(boost::get(&vert::name, g)),
                   make_edge_writer(boost::get(&edge::weight, g), boost::get(&edge::capacity, g)));
}
