#include <string>
#include <map>

template< class btype >
class registry {
  typedef std::map< std::string, int > maptype;
  static maptype mapvar;
};

template< class btype >
std::map< std::string, int > registry< btype >::mapvar;
//registry< btype >::maptype registry< btype >::mapvar;

int main(){
}
