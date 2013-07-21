#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi = boost::spirit::qi;
namespace phx= boost::phoenix;

struct Person
{
    std::string name;
    double height, weight;
    friend std::ostream& operator<<(std::ostream& os, Person const& s) {
        return os << "Person { name:" << s.name << ", height:" << s.height << ", weight:" << s.weight << " }";
    }
};

struct Student : Person
{
    Student() = default;
    Student(std::string n, double h, double w) : Person {n,h,w} {}
};

struct Teacher : Person
{
    Teacher() = default;
    Teacher(std::string n, double h, double w, double s) : Person {n,h,w}, salary(s) {}
    double salary;
};

int main()
{
    std::stringstream ss;
    ss << std::cin.rdbuf();

    std::map<std::string, boost::variant<Student, Teacher> > names;

    using namespace qi;
    auto add_student  = phx::ref(names)[_1] = phx::construct<Student>(_1, _2, _3);
    auto add_teacher  = phx::ref(names)[_1] = phx::construct<Teacher>(_1, _2, _3, _4);
    auto remove       = phx::erase(phx::ref(names), _1);
    auto print_all    = [&] (int i) { for(auto& p : names) { std::cout << p.second << "\n"; if (--i==0) break; } };
    auto print_salary = [&] () 
    { 
        struct _ : boost::static_visitor<> {
            void operator()(Teacher const& v) const { std::cout << "Teacher salary: " << v.salary << "\n"; }
            void operator()(Student const& v) const { }
        } v_;
        for(auto& p : names) boost::apply_visitor(v_, p.second);
    };

    auto name_ = as_string[lexeme[+graph]];

    if (phrase_parse(begin(ss.str()), end(ss.str()), 
                (
                     ("ADD_STUDENT" >> name_ >> double_ >> double_)            [ add_student ]
                   | ("ADD_TEACHER" >> name_ >> double_ >> double_ >> double_) [ add_teacher ]
                   | (eps >> "PRINT" >> "TEACHER" >> "SALARY")                 [ print_salary ]
                   | ("PRINTALL" >> int_)      [ phx::bind(print_all, _1) ]
                   | ("PRINT"  >> +name_       [ std::cout << phx::ref(names)[_1] << std::endl ])
                   | ("REMOVE" >> +name_       [ remove ])
                ) % +eol,
                qi::blank))
    {
        std::cout << "Success";
    }
    else
    {
        std::cout << "Parse failure";
    }
}

