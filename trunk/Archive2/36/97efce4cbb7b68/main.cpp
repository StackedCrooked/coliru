#include <boost/graph/adjacency_list.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>

/*********************************************/
// vertex
struct VertexProperties {
    int id;
    int label;
    VertexProperties(unsigned i = 0, unsigned l = 0) : id(i), label(l) {}
};

// edge
struct EdgeProperties {
    unsigned id;
    unsigned label;
    EdgeProperties(unsigned i = 0, unsigned l = 0) : id(i), label(l) {}
};

// Graph
struct GraphProperties {
    unsigned id;
    unsigned label;
    GraphProperties(unsigned i = 0, unsigned l = 0) : id(i), label(l) {}
};

// adjency list
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, VertexProperties, EdgeProperties, GraphProperties>
    Graph;

// descriptors

typedef boost::graph_traits<Graph>::vertex_descriptor vertex_t;
typedef std::pair<boost::graph_traits<Graph>::edge_descriptor, bool> edge_t;
// iterators
typedef boost::graph_traits<Graph>::vertex_iterator vertex_iter;
typedef boost::graph_traits<Graph>::edge_iterator edge_iter;

int main()
{
    clock_t start = std::clock();
    std::vector<Graph> dataG;

    std::ifstream file_reader("5.txt"); // flux d'entrée pour opérer sur les fichiers.
    // ifstream * file_reader= new ifstream("60.txt" ); //flux d'entrée pour opérer sur les fichiers.

    std::string line;
    while (std::getline(file_reader, line)) { // getline reads characters from an input stream and places them into a string

        char lineType;

        std::stringstream ss(line); // use a string buffer that contains a sequence of characters.
        if (ss >> lineType)
            switch (lineType) {
                case 't': {
                    char diez;
                    unsigned gid;
                    if (ss >> diez >> gid) {
                        dataG.emplace_back(GraphProperties(gid, gid));
                    } else
                        throw std::runtime_error("Error parsing '" + line + "'");
                } break;
                case 'v': {
                    assert(!dataG.empty());

                    int vId, vLabel;
                    if (ss >> vId >> vLabel) {
                        boost::add_vertex(VertexProperties(vId, vLabel), dataG.back());
                    } else
                        throw std::runtime_error("Error parsing '" + line + "'");
                } break;
                case 'e': {
                    assert(!dataG.empty());

                    int fromId, toId, vLabel;
                    if (ss >> fromId >> toId >> vLabel) {
                        // Note that the EdgeProperty.id doesn't make sense with your input data
                        // as it only contains [vertexFrom vertexTo edgeData]
                        boost::add_edge(fromId, toId, EdgeProperties(vLabel, vLabel), dataG.back());
                    } else
                        throw std::runtime_error("Error parsing '" + line + "'");
                } break;
            }
        else {
            // ignoring empty line
        }
    }

    Graph testg;
    if (!dataG.empty()) {
        auto const& gr = dataG.front(); // firslt graph in G_list
        auto ep = edges(gr).first; // first edge in gr

        vertex_t from = source(*ep, gr);
        vertex_t to = target(*ep, gr);

        Graph::edge_descriptor copied_edge = boost::add_edge(from, to, gr[*ep], testg).first;

        testg[source(copied_edge, testg)] = gr[from];
        testg[target(copied_edge, testg)] = gr[to];
    }

    typedef std::pair<edge_iter, edge_iter> edge_pair;

    // int c = 0; //compteur de dataG

    //++c;
    std::cout << "Graph  contains " << num_vertices(testg) << " vertices, and " << num_edges(testg) << " edges" << std::endl;
    // Vertex list
    std::cout << "  Vertex list: " << std::endl;
    for (size_t i = 0; i < num_vertices(testg); ++i) // size_t vertice number in the graph
    {
        std::cout << "   v[" << i << "]   ID: " << testg[i].id << ", Label: " << testg[i].label << std::endl;
    }
    // Edge list
    std::cout << "  Edge list: " << std::endl;
    edge_pair ep;
    for (ep = edges(testg); ep.first != ep.second; ++ep.first) // ep edge number
    {
        vertex_t from = source(*ep.first, testg);
        vertex_t to = target(*ep.first, testg);
        edge_t edg = edge(from, to, testg);
        std::cout << "   e[" << testg[from].id << "," << testg[to].id << "]   ID: " << testg[edg.first].id
                  << " ,  Label: " << testg[edg.first].label << std::endl;
    }
    std::cout << std::endl;

    std::cout << "TIME: " << (std::clock() - start) / (double)CLOCKS_PER_SEC << "s" << std::endl; // fin du programme.
}
