#include <boost/graph/adjacency_list.hpp>
#include <boost/array.hpp>

using namespace boost;


const int N = 10;
std::vector<double> Dem(N), ServTime;
std::vector<boost::array<double, 2>> TimeWin(N);
std::vector<int> num(N);
std::vector<std::vector<double> > edge_cost(N, {N}), Dist(N, {N});

const int MAX_VAL = 999999;

struct ESPPRC_Graph_Vert_Prop {
    ESPPRC_Graph_Vert_Prop(int=0, double=0, double=0, double=0, double=0) { }
};

struct ESPPRC_Graph_Arc_Prop {
    ESPPRC_Graph_Arc_Prop(int=0, double=0, double=0) { }
};

typedef adjacency_list<vecS, vecS, directedS, ESPPRC_Graph_Vert_Prop, ESPPRC_Graph_Arc_Prop> Graph;

Graph Grph;

int add_vertices(const int &source_node, const std::vector<bool> &add) {
    Grph.clear();
    int v = 0;
    for (int i = 0; i < N; i++) {
        if (add[i]) {
            add_vertex(ESPPRC_Graph_Vert_Prop(v, Dem[i], TimeWin[i][0], TimeWin[i][1], ServTime[i]), Grph);
            v++;
        }
    }

    return v;
}

int main()
{
    std::vector< std::vector< bool > > is_removed( N );
    std::vector< std::vector< bool > > in_out( N );

    int source_node = 0;

    for (int i = 0; i < N; ++i)
    {
       is_removed[i].resize( N, false ); // whether arc(i,j) is removed
       in_out[i].resize( 2, false ); // whether node(i) has an arc: 0 is in, 1 is out
    }

    int say = 0;
    std::vector<bool> add(N, true); // when i update this, it gives incorrect results
    for (int i = 0; i < N; i++) {
        if (!in_out[i][0] && !in_out[i][1]) {
            add[i] = false;
        } else {
            num[i] = say;
            say++;
        }
    }

    int v_last = add_vertices(source_node, add);

    int a = 0;

    for (int i = 0; i < N; i++) {
        if (add[i]) {
            for (int j = 0; j < N; j++) {
                if (i != j && !is_removed[i][j] && add[j]) {
                    add_edge(num[i], num[j], ESPPRC_Graph_Arc_Prop(a, edge_cost[i][j], Dist[i][j]), Grph);
                    a++;
                } else // When I remove this else it gives incorrect results
                {
                    add_edge(num[i], num[j], ESPPRC_Graph_Arc_Prop(a, edge_cost[i][j], MAX_VAL), Grph);
                    a++;
                }
            }
        }
    }

}
