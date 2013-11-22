#include <iostream>
#include <memory>

template <
          class N
         >
class Edge
{
  public:

    typedef std::shared_ptr<N> N_ptr;

    Edge
    (
      N_ptr node
     )
    {
       //...
    }

    template <class Archive>
    static Edge* load_and_allocate( Archive & ar )
    {
      N_ptr node;
      ar( node );
      return new Edge( node );
    }
};

void archive(Edge<int>::N_ptr) {}

int main()
{
    auto p = Edge<int>::load_and_allocate(archive);
}