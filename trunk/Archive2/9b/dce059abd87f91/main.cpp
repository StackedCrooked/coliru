    #include <iostream>
    #include <vector>
    #include <list>
    #include <set>
    using namespace std;
     
    template<class Container>
    void print(Container const& c){
      for(auto& x:c){
        std::cout << x; 
        if(&x != &(*std::prev(std::end(c)))) std::cout << ", ";
      }
      std::cout << std::endl;
    }
     
    int main() {
      std::vector<double> v{1.,2.,3.};
      print(v); // prints 1,2,3
      std::list<double> l{1.,2.,3.};
      print(l); // prints 1,2,3
      std::initializer_list<double> i{1.,2.,3.};
      print(i); // prints 1,2,3
      std::set<double> s{1.,2.,3.};
      print(s); // print 1,2,3
      double a[3] = {1.,2.,3.};
      print(a); // print 1,2,3
    }
