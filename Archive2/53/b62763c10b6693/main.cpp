#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <math.h>
#include <sys/types.h>
#include <errno.h>

#include "boost/multi_array.hpp"
#include "boost/array.hpp"
#include "boost/fusion/iterator/deref.hpp"
#include "boost/fusion/include/deref.hpp"

#include "boost/function/function0.hpp"

#include "boost/variant.hpp"
#include "boost/variant/variant_fwd.hpp"
#include "boost/variant/variant.hpp"
#include "boost/variant/recursive_variant.hpp"
#include "boost/variant/recursive_wrapper.hpp"
#include "boost/variant/apply_visitor.hpp"
#include "boost/variant/get.hpp"
#include "boost/variant/bad_visit.hpp"
#include "boost/variant/static_visitor.hpp"
#include "boost/variant/visitor_ptr.hpp"
#include "boost/tokenizer.hpp"

#include <iostream>

using namespace std;
using namespace boost;

typedef boost::variant<double, std::string > my_types;

void print_console(std::string str)  {
    cout << str << endl;
}

class MyQVariant {
public:
    using variant = my_types;
    variant data;

    struct invalid_conversion_helper : boost::static_visitor<MyQVariant> {
        std::string app_str;
        template<typename P>
        MyQVariant operator()(P&&) const {
        print_console("invalid conversion  1");
        }

        template<typename P1, typename P2>
        MyQVariant operator()(P1 const& p1_, P2 const& p2_) const {
            std::string s1 = typeid(P1).name();
            std::string s2 = typeid(P2).name();


            print_console(s1);
            print_console(s2);

            // -------------------------
            // P1 : Ss -> std:string
            // P2 : d  -> double
            // -------------------------
            if (s1 == "Ss" && s2 == "d")
            {
                std::string str = boost::get<std::string>(MyQVariant(p1_).data);
                double      val = boost::get<double>     (MyQVariant(p2_).data);

                app_str = app_str + str;
                app_str = app_str + std::to_string(val);
            }
            // -------------------------
            // P1 : d  -> double
            // P2 : Ss -> std:string
            // -------------------------
            else if (s1 == "d" && s2 == "Ss")
            {
                double      val1 = boost::get<double>     (MyQVariant(p1_).data);
                std::string val2 = boost::get<std::string>(MyQVariant(p2_).data);

                app_str = app_str + val2;
            }
            else {
                print_console("invalid conversion.");
                throw std::runtime_error("Error in Application.");
            }
            print_console(app_str);
        }
    };

public:
    MyQVariant(void) { }
    MyQVariant(double i) : data(i) {}
    MyQVariant(std::string s) : data(std::move(s)) {}
    MyQVariant(MyQVariant const &c) : data(c.data) {}

    friend MyQVariant operator + (MyQVariant const& lhs, MyQVariant const& rhs) {
        struct add_visitor : invalid_conversion_helper {
            using invalid_conversion_helper::operator();

            MyQVariant operator()(double const x, double const y) const {
                print_console("doublestr");
                return x + y;
            }

            MyQVariant operator()(double const x, std::string const& y) const {
                print_console("tester");
                return y;
            }

            MyQVariant operator()(std::string const& x, double const y) {
		std::string str = x + std::to_string(y);
                print_console(str);
                return  str;
            }
            MyQVariant operator()(std::string const& x, std::string const& y) const {
                return x + y;
            }
        };
        return boost::apply_visitor(add_visitor{}, lhs.data, rhs.data);
    }

    friend MyQVariant operator-(MyQVariant& lhs, MyQVariant& rhs) {
        struct sub_visitor : invalid_conversion_helper {
            using invalid_conversion_helper::operator();

            MyQVariant operator()(double x, double y) {
                return x - y;
            }
        };
        return boost::apply_visitor(sub_visitor{}, lhs.data, rhs.data);
    }

    friend MyQVariant operator*(MyQVariant& lhs, MyQVariant& rhs) {
        struct mul_visitor : invalid_conversion_helper {
            using invalid_conversion_helper::operator();

            MyQVariant operator()(double x, double y) {
                return x * y;
            }
        };
        return boost::apply_visitor(mul_visitor{}, lhs.data, rhs.data);
    }
};

void print_console(MyQVariant v) {
    std::cout << boost::get<std::string>(v.data) << std::endl;
}

MyQVariant global_var10;

int main(int argc, char **argv)
{
	std::cout << "start..." << std::endl;

	MyQVariant local_var10 =
	MyQVariant(std::string("Hello")) +
	MyQVariant(2.000000 + 3.000000) +
	MyQVariant(std::string(" World!!!")) +
	MyQVariant(0.270000 + 0.000300) +
	MyQVariant(std::string("popo"));
	global_var10 = local_var10;

	print_console(global_var10);

	return 0;
}



/* runtime output:

start...
Ss
d
Hello5.000000
Assertion failed!

Program: I:\Projects\windows\out\test\testcase\release\app.exe
File: C:/Qt/Qt5.2.1/5.2.1/mingw48_32/include/boost/variant/detail/visitation_impl.hpp, Line 207

Expression: false

This application has requested the Runtime to terminate it in an unusual way.
Please contact the application's support team for more information.

*/