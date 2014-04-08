#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <iostream>

namespace tree_ops {

/// @brief Walk a Boost.PropertyTree tree, invoking the binary function with
///        the full path and the current node.
template <typename Tree, typename Function>
void for_each(
    const Tree& tree, 
    Function fn,
    const typename Tree::path_type& parent_path = typename Tree::path_type())
{ 
  using path_type = typename Tree::path_type;
  for (auto&& value_pair: tree) {
    auto current_path = parent_path / path_type(value_pair.first);
    fn(current_path, value_pair.second);
    for_each(value_pair.second, fn, current_path);
  }
}

/// @brief Return tree with elements in @ref s but not in @ref t.
template <typename Tree>
Tree tree_difference(const Tree& s, const Tree& t)
{
  using data_type = typename Tree::data_type;
  Tree result;
  // Iterate 's', adding to the result when either a node in
  // 't' is not present in 's' or the node's values differ.
  for_each(s, 
    [&](const typename Tree::path_type& path, const Tree& node)
    {
      auto value = t.template get_optional<data_type>(path);
      if (!value || (value.get() != node.data()))
        result.add(path, node.data());
    });
  return result;
}

/// @brief Return tree with elements from both @ref s and @ref t.
template <typename Tree>
Tree tree_union(const Tree& s, const Tree& t)
{
  // The result will always contain all values in @ref s.
  Tree result = s;
  // Iterate 't', add values to the result only if the node is
  // either not in 's' or the values are different.
  for_each(t, 
    [&](const typename Tree::path_type& path, const Tree& node)
    {
      auto child = s.get_child_optional(path);
      if (!child || (child->data() != node.data()))
        result.add(path, node.data());
    });
  return result;
}

/// @brief Return tree with elements common to @ref s and @ref t.
template <typename Tree>
Tree tree_intersection(const Tree& s, const Tree& t)
{
  using data_type = typename Tree::data_type;
  Tree result;
  // Iterate 's', adding common elements found in 't' that have the same
  // value.
  for_each(s,
    [&](const typename Tree::path_type& path, const Tree& node)
    {
      auto value = t.template get_optional<data_type>(path);
      if (value && (value.get() == node.data()))
        result.add(path, node.data());
    });
  return result;
}

/// @brief Return tree with elements in either @ref s or @ref t, but not
///        both.
template <typename Tree>
Tree tree_symmetric_difference(const Tree& s, const Tree& t)
{
  return tree_union(s, t) - tree_intersection(s, t);
}

} // namespace tree_ops

// Expose mathematical tree operations with operators.

/// @brief Return tree with elements in @ref lhs but not in @ref rhs.
boost::property_tree::ptree operator-(
    const boost::property_tree::ptree& lhs,
    const boost::property_tree::ptree& rhs)
{
  return tree_ops::tree_difference(lhs, rhs);
}

/// @brief Return tree with elements in both @ref lhs and @ref rhs.
boost::property_tree::ptree operator|(
    const boost::property_tree::ptree& lhs,
    const boost::property_tree::ptree& rhs)
{
  return tree_ops::tree_union(lhs, rhs);
}

/// @brief Return tree with elements common to @ref lhs and @ref rhs.
boost::property_tree::ptree operator&(
    const boost::property_tree::ptree& lhs,
    const boost::property_tree::ptree& rhs)
{
  return tree_ops::tree_intersection(lhs, rhs);
}

/// @brief Return tree with elements in either @ref lhs or @ref rhs, but not
///        both.
boost::property_tree::ptree operator^(
    const boost::property_tree::ptree& lhs,
    const boost::property_tree::ptree& rhs)
{
  return tree_ops::tree_symmetric_difference(lhs, rhs);
}

int main()
{
  std::istringstream json1_stream(
      "{"
      "  \"node1\" : 1,"
      "  \"node_that_only_appears_in_this_one\" : 2,"
      "  \"node3\" :"
      "  {"
      "    \"nested1\" : 3,"
      "    \"nested2\" :"
      "    {"
      "      \"double_nested1\" : 5,"
      "      \"double_nested2\" : \"foo\""
      "    }"
      "  }"
      "}");
  
  std::istringstream json2_stream(
      "{"
      "  \"node1\" : 1,"
      "  \"node3\" :"
      "  {"
      "    \"nested1\" : 3,"
      "    \"nested_that_only_appears_in_this_one\" : 5,"
      "    \"nested2\" :"
      "    {"
      "      \"double_nested1\" : 5,"
      "      \"double_nested2\" : \"bar\""
      "    }"
      "  }"
      "}");
  
  boost::property_tree::ptree tree1, tree2;
  read_json(json1_stream, tree1);
  read_json(json2_stream, tree2);
  
  std::cout << "difference in tree2 and tree1\n";
  write_json(std::cout, tree2 - tree1);
  
  std::cout << "union of tree1 and tree2\n";
  write_json(std::cout, tree1 | tree2);
  
  std::cout << "intersection of tree1 and tree2\n";
  write_json(std::cout, tree1 & tree2);
  
  std::cout << "symmetric difference of tree1 and tree2\n";
  write_json(std::cout, tree1 ^ tree2);
}