#include <iostream>
#include <vector>
#include <algorithm>

enum class color
{
  white, gray, black
};

using adjacence_list_t = std::vector<std::vector<size_t>>;
using marks_t = std::vector<color>;
using vertex_t = std::vector<size_t>;

bool dfs( const adjacence_list_t & graph, size_t index, marks_t & marks, vertex_t & vertex )
{
  if ( marks[index] == color::gray ) return false;
  if ( marks[index] == color::black ) return true;

  marks[index] = color::gray;
  for ( auto to : graph[index] )
    if ( !::dfs( graph, to, marks, vertex ) ) return false;

  marks[index] = color::black;

  vertex.emplace_back( index );
  return true;
}

std::pair<bool, vertex_t>
dfs( const adjacence_list_t & graph, size_t index )
{
  vertex_t vertex;
  marks_t marks( graph.size(), color::white );

  if ( index < graph.size() )
    if ( !::dfs( graph, index, marks, vertex ) )
      return { false, vertex };

  return { true, vertex };
}

std::pair<bool, vertex_t>
topological_sort( const adjacence_list_t & graph )
{
  vertex_t vertex;
  marks_t marks( graph.size(), color::white );

  for ( size_t i = 0; i < graph.size(); ++i )
    if ( !::dfs( graph, i, marks, vertex ) )
      return { false, vertex };

  std::reverse( std::begin( vertex ), std::end( vertex ) );
  return { true, vertex };
}

int main()
{
  //adjacence_list_t graph = { { 2 }, { 1, 3, 4, 5 }, { 2, 4 }, { 2, 3, 5 }, { 2, 4, 6 }, { 5 } };
  //adjacence_list_t graph = { { 2 }, { 1, 3, 5 }, { 2 }, { 5 }, { 2, 4, 6 }, { 5 }, {} };

  //adjacence_list_t graph = { { 4 }, {}, { 2 }, { 2, 3, 1 } };

  //            1
  //            ↓
  //            4 → 3
  //            ↓   ↓
  //              2


  adjacence_list_t graph = { { 4 }, {}, { 2 }, { 2, 3 } };

  for ( auto& v : graph )
    for ( auto& i : v )
      --i;
  
  {
    const size_t vi = 4;
    std::cout << "dfs from " << vi << " : ";
    auto dfs_res = dfs( graph, vi - 1 );
    if ( dfs_res.first )
    {
      for ( auto& v : dfs_res.second )
        std::cout << v + 1 << " ";
      std::cout << std::endl;
    }
    else
      std::cout << "Cycle detected!" << std::endl;
  }

  {
    std::cout << "topological_sort: ";
    auto topo_sort = topological_sort( graph );
    if ( topo_sort.first )
    {
      for ( auto& v : topo_sort.second )
        std::cout << v + 1 << " ";
      std::cout << std::endl;
    }
    else
      std::cout << "Cycle detected!" << std::endl;
  }
}