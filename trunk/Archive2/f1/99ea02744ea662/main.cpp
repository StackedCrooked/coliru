// <boost/tuple/tuple.hpp>

namespace boost{ namespace tuples{
  struct tuple{
      
  };
  
}}

// <project/specific/operators.hpp>

bool operator ==(boost::tuples::tuple t, boost::tuples::tuple u){ // global namespace
    return false;
}

// <algorithm.hpp>

namespace stood{
    template <typename T> struct vector{ T t;};
    template <typename T> void find(vector<T> v, T u){
        v.t == u; // no "operator ==" in "boost::tuples" or "stood"
    }
}

int main(){
    boost::tuples::tuple t, u;
    stood::vector<boost::tuples::tuple> v = {t};
    find(v, u);
}