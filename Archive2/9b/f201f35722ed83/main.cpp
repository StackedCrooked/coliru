#include <boost/graph/adjacency_list.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace boost;

/*********************************************/
// vertex
struct VertexProperties {
    int id;
    int label;
    VertexProperties(unsigned i=0, unsigned l=0) : id(i), label(l) {}
};

// edge
struct EdgeProperties {
    unsigned id;
    unsigned label;
    EdgeProperties(unsigned i=0, unsigned l=0) : id(i), label(l) {}
};

// Graph
struct GraphProperties {
    unsigned id;
    unsigned label;
    GraphProperties(unsigned i=0, unsigned l=0) : id(i), label(l) {}
};

// adjency list
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, 
        VertexProperties, 
        EdgeProperties,
        GraphProperties> Graph;

// descriptors
typedef boost::graph_traits<Graph>::vertex_descriptor vertex_descriptor;
typedef std::pair<boost::graph_traits<Graph>::edge_descriptor, bool> edge_t;
// iterators
typedef graph_traits<Graph>::vertex_iterator vertex_iter;
typedef graph_traits<Graph>::edge_iterator edge_iter;

int main() {
    std::vector<Graph> dataG;

    std::ifstream file_reader("5.txt"); // flux d'entrée pour opérer sur les fichiers.

    std::string line;
    while (std::getline(file_reader, line)) { // getline reads characters from an input stream and places them into a string

        char lineType;
        
        std::stringstream ss(line);  // use a string buffer that contains a sequence of characters.
        if (ss >> lineType) switch (lineType) {
            case 't':
                {
                    char diez;
                    unsigned gid;
                    if (ss >> diez >> gid) {
                        dataG.emplace_back(GraphProperties { gid, gid });
                    }
                    else throw std::runtime_error("Error parsing '" + line + "'");
                }
            case 'v':
                {
                    assert(!dataG.empty());

                    int vId, vLabel;
                    if (ss >> vId >> vLabel) {
                        boost::add_vertex(VertexProperties(vId, vLabel), dataG.back());
                    }
                    else throw std::runtime_error("Error parsing '" + line + "'");
                }
            case 'e':
                {
                    assert(!dataG.empty());

                    int fromId, toId, vLabel;
                    if (ss >> fromId >> toId >> vLabel) {
                        // Note that the EdgeProperty.id doesn't make sense with your input data
                        // as it only contains [vertexFrom vertexTo edgeData]
                        boost::add_edge(fromId, toId, EdgeProperties(vLabel, vLabel), dataG.back());
                    }
                    else throw std::runtime_error("Error parsing '" + line + "'");
                }
        } else
        {
            // ignoring empty line
        }
    }

    if (!dataG.empty()) {
        auto const& gr = dataG.front(); // no copy
        Graph testg;

        for (auto ep = edges(gr); ep.first != ep.second; ++ep.first) // ep edge number
        {
            vertex_descriptor from = source(*ep.first, gr);
            vertex_descriptor to   = target(*ep.first, gr);

            boost::add_edge(from, to, testg);
        }
    }
    std::cout << "fin." << std::endl; // fin du programme.
}
