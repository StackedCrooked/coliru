#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>
using namespace std; // bite me

BOOST_FUSION_DEFINE_STRUCT(, User, (string,name)(bool,ismoron))

int main() {
    string const input = R"(
        Bartek Banachewicz: false
        Ell: false
        Puppy: true
        rightfold: false)" ;

    vector<User> users;

    using namespace boost::spirit::qi; // real hard
    phrase_parse(begin(input), end(input), 
            +(lexeme[+(char_ - ':')] > ':' > bool_),
            space, 
            users);

    for (auto e : users)
        std::cout << e.name << " is" << (e.ismoron? "":" not") << " a moron\n";
}
