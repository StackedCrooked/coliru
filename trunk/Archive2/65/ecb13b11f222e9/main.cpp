#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/iteration_macros.hpp>

#include <boost/lexical_cast.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/filtered_graph.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/graph/mcgregor_common_subgraphs.hpp>
#include <boost/property_map/shared_array_property_map.hpp>

#include <sstream>
#include <iterator>
#include <list>
#include <iostream>

typedef boost::adjacency_list<boost::setS, boost::vecS, boost::bidirectionalS,
                              boost::property<boost::vertex_name_t, std::string> > graph_type;

template <typename GraphFirst, typename GraphSecond>
struct print_callback {

  print_callback(const GraphFirst& graph1, const GraphSecond& graph2) :
      m_graph1(graph1), m_graph2(graph2) { }

  template <typename CorrespondenceMapFirstToSecond, typename CorrespondenceMapSecondToFirst>
  bool operator()(CorrespondenceMapFirstToSecond correspondence_map_1_to_2,
                  CorrespondenceMapSecondToFirst correspondence_map_2_to_1,
                  typename boost::graph_traits<GraphFirst>::vertices_size_type subgraph_size) 
  {
#if 0
      auto name1 = boost::get(boost::vertex_name_t(), m_graph1);
      auto name2 = boost::get(boost::vertex_name_t(), m_graph2);

      BGL_FORALL_VERTICES_T(it, m_graph1, GraphFirst) { std::cout << name1[it] << "; "; }
      std::cout << "\n";
      print_edges(m_graph1, name1);

      BGL_FORALL_VERTICES_T(it, m_graph2, GraphFirst) { std::cout << name2[it] << "; "; }
      std::cout << "\n";
      print_edges(m_graph2, name2);
#endif

      // Print out correspondences between vertices
      BGL_FORALL_VERTICES_T(vertex1, m_graph1, GraphFirst) {

          // Skip unmapped vertices
          if (get(correspondence_map_1_to_2, vertex1) != boost::graph_traits<GraphSecond>::null_vertex()) {
              std::cout << vertex1 << " <-> " << get(correspondence_map_1_to_2, vertex1) << std::endl;
          }
      }

      std::cout << "---" << std::endl;

      return (true);
  }

  private:
    const GraphFirst& m_graph1;
    const GraphSecond& m_graph2;
};

graph_type dataset1() {
    graph_type g;
    auto node0 = add_vertex(std::string(""),                                g);
    auto node1 = add_vertex(std::string("PlayerMoveStop::Create"),          g);
    auto node2 = add_vertex(std::string(""),                                g);
    auto node3 = add_vertex(std::string(""),                                g);
    auto node4 = add_vertex(std::string("PlayerMoveStartBackward::Create"), g);
    auto node5 = add_vertex(std::string(""),                                g);
    auto node6 = add_vertex(std::string(""),                                g);
    auto node7 = add_vertex(std::string(""),                                g);

    add_edge(node0, node6, g);
    add_edge(node0, node7, g);
    add_edge(node1, node5, g);
    add_edge(node1, node7, g);
    add_edge(node2, node4, g);
    add_edge(node2, node5, g);
    add_edge(node2, node6, g);
    add_edge(node3, node4, g);
    return g;
}

graph_type dataset2() {
    graph_type g;
    auto node0 = add_vertex(std::string("PlayerMoveStop::Create"),           g);
    auto node1 = add_vertex(std::string("PlayerMoveStop::Create"),           g);
    auto node2 = add_vertex(std::string("MoveFallLand_Destruct"),            g);
    auto node3 = add_vertex(std::string("PlayerMoveStop::Destroy"),          g);
    auto node4 = add_vertex(std::string("PlayerMoveStartBackward::Destroy"), g);
    auto node5 = add_vertex(std::string("PlayerMoveStartBackward::Create"),  g);
    auto node6 = add_vertex(std::string("PlayerMoveHeartbeat::Destroy"),     g);
    auto node7 = add_vertex(std::string("PlayerMoveFallLand::CliPut"),       g);
    auto node8 = add_vertex(std::string("PlayerMoveStartForward::CliPut"),   g);

    add_edge(node0, node6, g);
    add_edge(node0, node8, g);
    add_edge(node1, node5, g);
    add_edge(node1, node7, g);
    add_edge(node2, node4, g);
    add_edge(node2, node7, g);
    add_edge(node2, node8, g);
    add_edge(node3, node4, g);
    add_edge(node3, node5, g);
    add_edge(node3, node6, g);
    return g;
}

graph_type dataset3() {
    graph_type g;
    auto node2 = add_vertex(std::string("zzzzz"),                           g);
    auto node3 = add_vertex(std::string(""),                                g);
    auto node4 = add_vertex(std::string("PlayerMoveStartBackward::Create"), g);
    auto node5 = add_vertex(std::string(""),                                g);
    auto node6 = add_vertex(std::string("eeeee"),                           g);
    auto node7 = add_vertex(std::string("fffff"),                           g);

    auto node0 = add_vertex(std::string(""),                                g);
    auto node1 = add_vertex(std::string("PlayerMoveStop::Create"),          g);

    add_edge(node0, node6, g);
    add_edge(node0, node7, g);
    add_edge(node1, node5, g);
    add_edge(node1, node7, g);
    add_edge(node2, node4, g);
    add_edge(node2, node5, g);
    add_edge(node2, node6, g);
    add_edge(node3, node4, g);
    return g;
}

int main() {
    using namespace boost;

    // Create two graphs and put into them some vertex with property:
    graph_type 
        g1 = dataset1(),
        g2 = dataset3(); // dataset2();

    // Create property_map:
    typedef property_map<graph_type, vertex_name_t>::type NameMap;
    NameMap name1 = boost::get(vertex_name_t(), g1);
    NameMap name2 = boost::get(vertex_name_t(), g2);

    print_callback<graph_type, graph_type> callback(g1, g2);

    // And call algorithm:
    mcgregor_common_subgraphs_unique(
            g1, g2,
            true, 
            callback,
            vertices_equivalent(make_property_map_equivalent(name1, name2)));
}
