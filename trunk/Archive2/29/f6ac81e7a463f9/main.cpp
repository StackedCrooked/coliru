#include <boost/container/vector.hpp>
#include <boost/container/list.hpp>
#include <boost/container/map.hpp>
#include <boost/container/stable_vector.hpp>
#include <boost/container/string.hpp>

using namespace boost::container;

struct data
{
   int               i_; 
   vector<data>      v_; //A vector holding still undefined class 'data'
   list<data>        l_; //A list holding still undefined 'data'
   map<data, data>   m_; //A map holding still undefined 'data'

   friend bool operator <(const data &l, const data &r)
   { return l.i_ < r.i_; }
};

struct tree_node
{
   string name;
   string value;

   //children nodes of this node
   list<tree_node>        children_;
};

int main()
{
   //a container holding a recursive data type
   stable_vector<data> sv;
   sv.resize(100);

   //Let's build a tree based in
   //a recursive data type
   tree_node root;
   root.name  = "root";
   root.value = "root_value";
   root.children_.resize(7);
   return 0;
}