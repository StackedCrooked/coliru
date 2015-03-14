#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/vf2_sub_graph_iso.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <queue> // std::queue
// for mmap:
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;
using namespace boost;

//==========STRUCTURES==========
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
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, VertexProperties, EdgeProperties,
                              GraphProperties> Graph;

// descriptors

typedef boost::graph_traits<Graph>::vertex_descriptor vertex_t;
typedef std::pair<boost::graph_traits<Graph>::edge_descriptor, bool> edge_t;
// iterators
typedef graph_traits<Graph>::vertex_iterator vertex_iter;
typedef graph_traits<Graph>::edge_iterator edge_iter;
typedef std::pair<edge_iter, edge_iter> edge_pair;

//==========READ ALL THE FILE AND RETURN A STRING==========
void handle_error(const char *msg) {
    perror(msg);
    exit(255);
}
//===============================
const char *readfromfile2(const char *fname, size_t &length) {
    int fd = open(fname, O_RDONLY);
    if (fd == -1)
        handle_error("open");

    // obtain file size
    struct stat sb;
    if (fstat(fd, &sb) == -1)
        handle_error("fstat");

    length = sb.st_size;

    const char *addr = static_cast<const char *>(mmap(NULL, length, PROT_READ, MAP_PRIVATE, fd, 0u));
    if (addr == MAP_FAILED)
        handle_error("mmap");

    // TODO close fd at some point in time, call munmap(...)
    return addr;
}

//==========SPLIT THE STRING BY NEWLINE (\n) ==========
vector<string> splitstringtolines(string const &str) {
    vector<string> split_vector;
    split(split_vector, str, is_any_of("\n"));

    return split_vector;
}

//==============================================================
string getpos(int pos, string yy) {
    size_t i = pos;
    string str;
    for (; yy[i] != ' ' && i < yy.length(); i++)
        str += yy[i];
    return str;
}
//==============================================================
std::vector<Graph> creategraphs(std::vector<string> const &fichlines) {
    std::vector<Graph> dataG;
    int compide = 0; // compteur de id edge
    for (string yy : fichlines) {
        switch (yy[0]) {
        case 't': {
            string str2 = getpos(4, yy);
            unsigned gid = atoi(str2.c_str());
            dataG.emplace_back(GraphProperties(gid, gid));
            compide = 0;
        } break;
        case 'v': {
            assert(!dataG.empty()); // assert will terminate the program  if its argument turns out to be false
            // cout<<yy<<endl;
            int vId, vLabel;
            string vvv = getpos(2, yy);
            vId = atoi(vvv.c_str());
            string vvvv = getpos((int)vvv.length() + 3, yy);
            // cout<<vvvv<<endl;
            vLabel = atoi(vvvv.c_str());
            boost::add_vertex(VertexProperties(vId, vLabel), dataG.back());
        }

        break;

        case 'e': { // cout<<yy<<endl;
            assert(!dataG.empty()); // assert will terminate the program  if its argument turns out to be false

            int fromId, toId, eLabel;
            string eee = getpos(2, yy);
            // cout<<eee<<endl;
            fromId = atoi(eee.c_str());
            string eee2 = getpos((int)eee.length() + 3, yy);
            // cout<<eee2<<endl;
            toId = atoi(eee2.c_str());
            int c = (int)eee.length() + (int)eee2.length() + 4;
            //    cout<<c<<endl;
            string eee3 = getpos(c, yy);
            //  cout<<eee3<<endl;
            eLabel = atoi(eee3.c_str());
            boost::add_edge(fromId, toId, EdgeProperties(compide, eLabel), dataG.back());
            compide++;
        } break;
        }
    }

    return dataG;
}
//==================================================================================
bool graphconnexe(Graph const &g) { return num_edges(g) >= num_vertices(g) - 1; }
//============================================================================
void printgraph(Graph const &gr) {
    typedef std::pair<edge_iter, edge_iter> edge_pair;

    std::cout << " contains " << num_vertices(gr) << " vertices, and " << num_edges(gr) << " edges " << std::endl;
    if (graphconnexe(gr)) {

        // Vertex list
        if (num_vertices(gr) != 0) {
            std::cout << "  Vertex list: " << std::endl;
            for (size_t i = 0; i < num_vertices(gr); ++i) // size_t vertice number in the graph
            {
                std::cout << "   v[" << i << "]   ID: " << gr[i].id << ", Label: " << gr[i].label << std::endl;
            }
        }
        // Edge list
        if (num_edges(gr) != 0) {
            std::cout << "  Edge list: " << std::endl;
            edge_pair ep;
            for (ep = edges(gr); ep.first != ep.second; ++ep.first) // ep edge number
            {
                vertex_t from = source(*ep.first, gr);
                vertex_t to = target(*ep.first, gr);
                edge_t edg = edge(from, to, gr);
                std::cout << "   e(" << gr[from].id << "," << gr[to].id << ")   ID: " << gr[edg.first].id
                          << " ,  Label: " << gr[edg.first].label << std::endl;
            }
        }
        std::cout << "\n\n" << std::endl;
    } else {
        cout << "Please check this graph connectivity." << endl;
    }
}
//==================================================================================
struct my_callback {
    template <typename CorrespondenceMap1To2, typename CorrespondenceMap2To1>
    bool operator()(CorrespondenceMap1To2 f, CorrespondenceMap2To1 g) const {
        return false;
    }
};
//==================================================================================
/*bool graphexistance( std::vector<Graph> const& v, Graph item)
{
   return std::find(v.begin(), v.end(), item)!=v.end();
}*/

//=========================================================
bool gUe(Graph &g, edge_iter ep, Graph t) {

    vertex_t from = source(*ep, t);
    vertex_t to = target(*ep, t);

    Graph::edge_descriptor copied_edge = boost::add_edge(from, to, t[*ep], g).first;

    g[source(copied_edge, g)] = t[from];
    g[target(copied_edge, g)] = t[to];

    if (graphconnexe(g) && graphconnexe(t)) {
        return vf2_subgraph_iso(g, t, my_callback());
    } else {
        return false;
    }
}
//==========================================
bool verticeexist(Graph &g, int vId, int vlabel) {
    int cpt = 0;
    if (num_edges(g) != 0) {
        for (size_t i = 0; i < num_vertices(g); ++i) // size_t vertice number in the graph
        {
            if ((g[i].id == vId) && (g[i].label == vlabel)) {
                cpt++;
            }
        }
    }
    return cpt != 0;
}
//========================================
bool edgeexist(Graph g, int fromid, int toid, unsigned elabel) {
    int bn = 0;
    if (graphconnexe(g)) {
        if (num_edges(g) != 0) {
            edge_pair ep;
            for (ep = edges(g); ep.first != ep.second; ++ep.first) // ep edge number
            {
                vertex_t from = source(*ep.first, g);
                vertex_t to = target(*ep.first, g);
                edge_t edg = edge(from, to, g);

                if ((g[from].id == fromid) && (g[to].id == toid) && (g[edg.first].label == elabel)) {
                    bn++;
                }
            }
        }
    }

    return (bn != 0);
}

// =========================================

bool vareneighbors(Graph g, int a, int b) {
    int bn = 0;
    if (graphconnexe(g)) {

        if (num_edges(g) != 0) {
            edge_pair ep;
            for (ep = edges(g); ep.first != ep.second; ++ep.first) // ep edge number
            {
                vertex_t from = source(*ep.first, g);
                vertex_t to = target(*ep.first, g);

                if (((g[from].id == a) || (g[to].id == a)) && ((g[from].id == b) || (g[to].id == b))) {
                    bn++;
                }
            }
        }
    }

    return (bn != 0);
}
//==========================================
    template <typename Graph, typename E = typename boost::graph_traits<Graph>::edge_descriptor>
    bool edgesneighbors(Graph const& g, E e1, E e2) {

        std::set<vertex_t> vertex_set { 
            source(e1, g), target(e1, g),
            source(e2, g), target(e2, g),
        };

        return graphconnexe(g) && vertex_set.size() < 4;
    }
//==========================================
void emptygraphaddedge(Graph &g, int fromId, int toId, int eLabel) {
    if (num_edges(g) == 0) {
        boost::add_edge(fromId, toId, EdgeProperties(num_edges(g) + 1, eLabel), g);
    }
}

//==========================================
int main() {
    clock_t start = std::clock();
    size_t length;

    std::vector<Graph> dataG = creategraphs(splitstringtolines(readfromfile2("testgUe.txt", length)));

    typedef std::pair<edge_iter, edge_iter> edge_pair;

    if (!dataG.empty()) {
        edge_pair ep = edges(dataG[0]);

        if (size(ep) >= 2) {
             Graph::edge_descriptor e1 = *ep.first++;
             Graph::edge_descriptor e2 = *ep.first++;

             cout << "edgesneighbors" << edgesneighbors(dataG[0], e1, e2) << endl;
        }
    }

    // end and time
    cout << "FILE Contains " << dataG.size() << " graphs.\nTIME: " << (std::clock() - start) / (double)CLOCKS_PER_SEC
         << "s" << endl; // fin du programme.
}
