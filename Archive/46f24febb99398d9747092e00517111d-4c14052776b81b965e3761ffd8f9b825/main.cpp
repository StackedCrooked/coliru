#include <map>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/signals2.hpp>
#include <memory>

typedef boost::signals2::signal<double(void)> sig;
typedef std::shared_ptr<sig> pSig;
typedef std::map<int, pSig> map_sig;

double f(void){return 1.;}

int main(){
    pSig s(new sig);
    s->connect(f);
    
    map_sig m;
    m.insert( map_sig::value_type(1, s) );
}
