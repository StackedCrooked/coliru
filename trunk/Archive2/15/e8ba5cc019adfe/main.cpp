#include <functional>
#include <iterator>
#include <memory>
#include <vector>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <cstdlib>

struct test_id : std::unary_function< int, bool>
{
      typedef std::vector<int>::const_iterator iterator;
      iterator first, last;
      explicit test_id(std::vector<int> const& v_id) : first(v_id.begin()), last(v_id.end()){}
      bool operator()(int id)const{ return std::binary_search(first, last, id); }
};

struct Node
{
    int id;
    std::string name;
    //...and a lot of members.

   //-------------------
   std::vector< std::unique_ptr<Node> > children;
};

int main()
{

     Node node; 
     // initialize it with some values
     node.id = 0;
     node.name = "root";
     srand(static_cast<unsigned>(time(NULL)));
     for(int i= 0; i < 100; ++i)
     {
        std::unique_ptr<Node> ch (new Node );
        ch->id = i;
        ch->name = "children";
        node.children.push_back( std::move(ch) );
     }

   //............
   std::vector<int> existing_ids; 
    // initialize it with some values.
    for(int i = 0; i < 100; ++i)
      if ( i % 3 == 1) existing_ids.push_back(i);

    //sort it
    std::sort(existing_ids.begin(), existing_ids.end() );

   // Now, I want remove elements from the children, where id is in existing_ids vector.
   node.children.erase( 
    std::remove_if( 
         node.children.begin(), 
         node.children.end(), 
         std::bind(test_id(existing_ids), std::bind(&Node::id, std::placeholders::_1) )//--> compile error
         ), 
   node.children.end() );
   
   for(auto& n : node.children) {
       std::cout << n->id << ' ';
   }
   std::cout << '\n';
}
