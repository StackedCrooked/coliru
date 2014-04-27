//=======================================================================
// Copyright 2001 Jeremy G. Siek, Andrew Lumsdaine, Lie-Quan Lee,
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
#include <boost/config.hpp>
#include <iostream>
#include <fstream>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

#include <boost/fusion/adapted.hpp>
#include <boost/spirit/include/qi.hpp>
#include <map>

using namespace boost;

typedef int VertexId;
struct Position { double x, y, z; };
BOOST_FUSION_ADAPT_STRUCT(Position, (double,x)(double,y)(double,z))

typedef std::pair<VertexId, VertexId> Edge;

size_t read_graph_data(std::vector<Edge>& edges, std::vector<double>& weights)
{
    //std::ifstream ifs("M10000_P_toro.graph");
    std::ifstream ifs("reduced.graph");
    ifs >> std::noskipws;
    boost::spirit::istream_iterator f(ifs), l;

    using namespace boost::spirit::qi;

    std::map<VertexId, Position> vertex_map;
    edges.clear();

    bool ok = phrase_parse(f, l,
            ("VERTEX2" >> int_ >> (double_ > double_ > double_)) % eol > eol >>
            ("EDGE2" >> int_ >> int_ >> omit [ *(char_ - eol) ]) % eol,
            boost::spirit::qi::blank,
            vertex_map, edges);

    assert(ok);

    weights.resize(edges.size());
    std::transform(edges.begin(), edges.end(), weights.begin(),
            [&](Edge const& e) { 
                auto& a = vertex_map.at(e.first);
                auto& b = vertex_map.at(e.second);
                auto dx = (a.x - b.x), dy = (a.y - b.y), dz = (a.z - b.z);
                return sqrt(dx*dx + dy*dy + dz*dz);
            });

    std::cout << "vertices: " << vertex_map.size() << ", edges: " << edges.size() << "\n";

    // find highest verted id
    return std::max_element(vertex_map.begin(), vertex_map.end(),
            [](std::pair<VertexId const, Position> const& a, 
               std::pair<VertexId const, Position> const& b) { return a.first < b.first; })->first;
}

int main()
{
    typedef adjacency_list <listS, vecS, directedS,
            no_property, property <edge_weight_t, double> > graph_t;
    typedef graph_traits <graph_t>::vertex_descriptor vertex_descriptor;

    std::vector<Edge> edge_array;
    std::vector<double> weights;
    const size_t num_nodes = read_graph_data(edge_array, weights);

    graph_t g(edge_array.begin(), edge_array.end(), weights.data(), num_nodes);
    property_map<graph_t, edge_weight_t>::type weightmap = get(edge_weight, g);

    std::vector<vertex_descriptor> p(num_vertices(g));
    std::vector<double>            d(num_vertices(g));
    vertex_descriptor s = vertex(4578, g);

    dijkstra_shortest_paths(g, s, predecessor_map(&p[0]).distance_map(&d[0]));

    std::cout << "distances and parents:" << std::endl;
    graph_traits<graph_t>::vertex_iterator vi, vend;
    for(tie(vi, vend) = vertices(g); vi != vend; ++vi)
    {
        std::cout << "distance(" << *vi << ") = " << d[*vi] << ", ";
        std::cout << "parent("   << *vi << ") = " << p[*vi] << std::endl;
    }
    std::cout << std::endl;

    std::ofstream dot_file("figs/dijkstra-eg.dot");

    dot_file << "digraph D {\n"
             << "  rankdir=LR\n"
             << "  size=\"4,3\"\n"
             << "  ratio=\"fill\"\n"
             << "  edge[style=\"bold\"]\n" << "  node[shape=\"circle\"]\n";

    graph_traits<graph_t>::edge_iterator ei, ei_end;
    for(tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
    {
        graph_traits<graph_t>::edge_descriptor e = *ei;
        graph_traits<graph_t>::vertex_descriptor
        u = source(e, g), v = target(e, g);
        if(p[v] == u)
        {
            dot_file << u << " -> " << v
                << "[label=\"" << get(weightmap, e) << "\"";
            dot_file << ", color=\"black\"";
            dot_file << "]";
        }
    }
    dot_file << "}";
}
