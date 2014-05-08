#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

typedef std::vector<double> dvec;
 
class Key {
public:
    Key( const std::string &name, const std::string &spalte );
    Key( const std::string &name,
         const std::string &spalte,
         int jahr1,
         int jahr2,
         double x1 = 0.0,
         double x2 = 0.0 );
    Key( const std::string &name1,
         const std::string &name2,
         const std::string &spalte,
         double v );
    Key( const dvec *qx, double v );
    bool operator<( const Key &k ) const {
        return memcmp( this, &k, sizeof( Key ) ) < 0;
    }
private:
    char name1_[ 20 ];
    char name2_[ 20 ];
    char spalte_[ 10 ];
    const dvec *ptr_;
    int j1_;
    int j2_;
    double v_;
    double x1_;
    double x2_;
};
    
int main() {
    std::cout << std::boolalpha;
    std::cout << std::is_trivially_copyable<Key>::value << '\n';
}
