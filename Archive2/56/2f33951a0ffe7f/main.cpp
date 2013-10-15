#include <iostream>
#include <string>
#include <vector>
//#include <boost/range.hpp>

template< typename GeneratorOfGenerators >
class HomogenousCartesianGenerator
{
public:
    typedef GeneratorOfGenerators gen_gen_type;
    typedef typename gen_gen_type::value_type gen_type;
    typedef typename gen_type::value_type value_type;
    typedef std::vector<value_type> combination_type;
private:
    combination_type _prefix;
};

using namespace std;

typedef vector<int> Vec;
typedef vector<Vec> VecVec;

struct VecGen
{
    typedef Vec::const_iterator const_iterator;
    VecGen(const Vec& vec) : first(vec.begin()), last(vec.end()) { }
    bool hasNext() { return first != last; }
    int next() { return *(first++); }
private:
    const_iterator first, last;
};

struct VecVecGen
{
    typedef VecVec::const_iterator const_iterator;
    VecVecGen(const VecVec& vec) : first(vec.begin()), last(vec.end()) { }
    bool hasNext() { return first != last; }
    VecGen next() { return VecGen(*(first++)); }
//    {
//        VecGen gen(*first);
//        ++first;
//    }
private:
    const_iterator first, last;
};

int main()
{
    VecVec vecvec;
    {
        vector<int> v;
        v.clear(); v.push_back(11); v.push_back(12); v.push_back(13);
        vecvec.push_back(v);
        v.clear(); v.push_back(21); v.push_back(22);
        vecvec.push_back(v);
        v.clear(); v.push_back(31); v.push_back(32);
        vecvec.push_back(v);
    }
    
    VecVecGen vvgen(vecvec);
    while (vvgen.hasNext())
    {
        VecGen vgen(vvgen.next());
        while (vgen.hasNext())
            cout << vgen.next() << " ";
        cout << endl;
    }
    
    cout << "hello" << endl;
}
