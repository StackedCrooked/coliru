#include <vector>
#include <cassert>
#include <iostream>

namespace 
{
  unsigned long long node_count{0ULL};
  struct node
  {
      std::vector<node> parent;
	  std::vector<node> children;

    // default construct: rely on member initialisation bump node count up
    node()
    {
        ++node_count;
    }

    // copy construct: copy other's vector members and bump node count up
    node( node const & other )
    : parent(other.parent)
    , children(other.children)
    {
      ++node_count;
    }

    // copy assignment: copy rhs and swap vector members with this
    node & operator=(node rhs)
    {
      parent.swap(rhs.parent);
      children.swap(rhs.children);
      return *this;
    }

    // destroy node: bump node count down.
    ~node() 
    {
      --node_count;
    }
  };

}

void print_status(const char * prefix="")
{
  std::cout << prefix << "Node count: "<< node_count << "\n";
}
void print_status(unsigned i, const char * prefix="")
{
  std::cout << prefix <<  " node insert no.: "<< i << ";  ";
  print_status();
}

void create_root_with_n_children_posted_method(unsigned n)
{
    node r;

    for (unsigned i=0; i!=n; ++i)
    {
        print_status(i, "Before");
        node c;
        c.parent.push_back(r);
        r.children.push_back(c);
        print_status(i, " After");
    }
}


void create_root_with_n_children_adjusted_method(unsigned n)
{
    node r;

    for (unsigned i=0; i!=n; ++i)
    {
        print_status(i, "Before");
        r.children.push_back(node());

      // ensure copy of child node has copy of r as parent
        r.children.back().parent.push_back(r);
        print_status(i, " After");
    }
}

int main()
{
    const unsigned NumberOfNodes(20);
    print_status("Before create_root_with_n_children_posted_method: "); // should be 0
    create_root_with_n_children_posted_method(NumberOfNodes);
    print_status(" After create_root_with_n_children_posted_method: "); // should be 0
    print_status("\n Before create_root_with_n_children_adjusted_method: "); // should be 0
    create_root_with_n_children_adjusted_method(NumberOfNodes);
    print_status(" After create_root_with_n_children_adjusted_method: "); // should be 0
}


