#include <iostream>
#include <string>
#include <boost/unordered_map.hpp>
#include <boost/foreach.hpp>
#include <boost/spirit/home/support/detail/hold_any.hpp>


typedef boost::spirit::hold_any anything;

typedef boost::unordered_map<int, anything> anyhash;

class Base {
    public:
        Base(anyhash val) : data(val) {}
        void printdata() 
            { 
                BOOST_FOREACH(anyhash::value_type i, data)
                   std::cout<<"key: " << i.first<<" \t -> value: "<<i.second<<"\n";
            }
        virtual anyhash gett(void) = 0;
    protected:
        anyhash data;
};

class Derived: public Base {
    public:
        Derived(anyhash val) : Base(val) {}
        anyhash gett() { return data; }  
};

int main()
{
anyhash somehash;

somehash.insert(std::make_pair(12, anything(123)));
somehash.insert(std::make_pair(93, anything(std::string("some text"))));
somehash.insert(std::make_pair(99, anything(999.9)));
somehash[666]=anything(555);
somehash[31415]=anything(3.1415);
somehash[123]=321;
somehash[0];
somehash[3333]=std::string("qergewrg");
//somehash[777]=std::make_pair(123, 456);

Derived test(somehash);
test.printdata();
//cout << "fromgetter:" << test.gett() << endl << endl;

}
