#include <iostream>
#include <vector>
using namespace std;

template<int dim,typename T> class n_dim_vector {

public:
    typedef std::vector<typename n_dim_vector<dim - 1, T>::vector> vector;
};

template<typename T> class n_dim_vector <0, T> {

public:
    typedef T vector;
};

template<int dim, typename T> class n_dim_ssc {

public:
    typename n_dim_vector<dim, T>::vector searchspace;
    
    n_dim_ssc() {}
    n_dim_ssc(typename n_dim_vector<dim, T>::vector space) : searchspace(space) {}
    
    n_dim_ssc<dim-1, T> operator[](std::size_t i) {
        
        if(searchspace.size() < ++i)
            searchspace.resize(i);
        return n_dim_ssc<dim-1, T>(searchspace[--i]);
    }
    
    typename n_dim_vector<dim, T>::vector get() {
        return searchspace;
    }
    
};

template<typename T> class n_dim_ssc<0,T> {

public:
    typename n_dim_vector<0, T>::vector searchspace;
    
    n_dim_ssc() {}
    n_dim_ssc(typename n_dim_vector<0, T>::vector space) : searchspace(space) {}
    
    typename n_dim_vector<0, T>::vector get() {
        return searchspace;
    }
};



int main(int argc, char** argv) {
  n_dim_ssc<0, int> ea;
  int a = ea.get();
  
  n_dim_ssc<1, int> ea2;
  auto dd2 = ea2[0].get();
  
  n_dim_ssc<2, int> ea3;
  auto dd3 = ea3[0][0].get();
}