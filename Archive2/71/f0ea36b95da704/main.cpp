#include <iostream>  // for std::cout
#include <boost/graph/adjacency_list.hpp>

#include <boost/graph/graphviz.hpp>
#include <boost/graph/topological_sort.hpp>
#include <boost/function_output_iterator.hpp>

using namespace boost;

int main()
{
    srand(time(0));

    typedef adjacency_list<vecS, vecS, bidirectionalS> Graph;
    const int num_vertices = 10;
    Graph g(num_vertices);

    // add random edges to the graph object
    for (size_t i = 0; i < 10; ++i)
    {
        auto f = rand()%num_vertices,
             s = rand()%num_vertices;

        add_edge(f, s, g);
        try {
            topological_sort(g, boost::make_function_output_iterator([](int){}));
        } catch(not_a_dag const& e)
        {
            remove_edge(f, s, g);
            std::cerr << "dropped edge: " << e.what() << "\n";
        }
    }

    write_graphviz(std::cout, g);
}
