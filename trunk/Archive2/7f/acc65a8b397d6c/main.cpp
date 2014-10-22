#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <boost/fusion/include/sequence.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <boost/fusion/include/next.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <tuple>

typedef boost::fusion::vector<std::tuple<int&, bool&>,
                              std::tuple<short&, bool&>, 
                              std::tuple<char&, bool&> > Params;


class Dupa
{
public:
    Dupa()
    {
        Params params(std::tie(x, xbool), std::tie(y, ybool), std::tie(z, zbool));
        
        boost::fusion::for_each(params, Filler());
            
    }
    int getX()
    {
        return x;
    }
    short getY()
    {
        return y;
    }
    char getZ()
    {
        return z;
    }
    
    struct Filler
    {
        template<typename T>
        void fillElem(T& t) const
        {
            t = T();
        }

        void fillElem(int& x) const
        {
            x = 5;
        }

        void fillElem(short& y) const
        {
            y = 2;
        }

        void fillElem(char& z) const
        {
            z = 'c';
        }
        template<typename Pair>
        void operator()(Pair& pair) const
        {
            if(std::get<1>(pair))
            {
                fillElem(std::get<0>(pair));
            }
        }
    };
    
private:

    

    int x = 0;
    short y = 1;
    char z ='a';
    bool xbool = true;
    bool ybool = true;
    bool zbool = true;
};

int main()
{
    Dupa dupa;
    std::cout << dupa.getX() << std::endl;
    std::cout << dupa.getY() << std::endl;
    std::cout << dupa.getZ() << std::endl;
}
