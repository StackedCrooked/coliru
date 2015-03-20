#include <memory>
#include <sstream>
#include <vector>

using namespace std;

int main()
{
    vector< shared_ptr<stringstream> > vstream;
    
    vstream.emplace_back( make_shared<stringstream>() ) ;
    auto external_reference = make_shared<stringstream>("This is a stringstream");
    vstream.push_back( external_reference );
    return 0;
}