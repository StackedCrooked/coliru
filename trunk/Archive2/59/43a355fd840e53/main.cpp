#include <cstdlib>
#include <iostream>
#include <boost/coroutine/all.hpp>


using namespace boost::coroutines;


int main()
{
    using Pull   = boost::coroutines::asymmetric_coroutine<std::string>::pull_type;
    using Push   = boost::coroutines::asymmetric_coroutine<std::string>::push_type;

    Push push([&](Pull& pull)
    {
        for (;;)
        {
            std::string s = pull.get();

            auto b = s.begin();
            for (; b != s.end() ;)
            {
                auto i = std::find(b, s.end(), '=');
                std::cout.write(&*b, i - b);
                if (i == s.end()) break;
                b = i + 1;

                std::cout << " => ";

                i = std::find(b, s.end(), '&');
                std::cout.write(&*b, i - b) << std::endl;
                if (i == s.end()) break;
                b = i + 1;
            }

            //
            pull();
        }
    });

    push("a=1&b=2&c=3");

    std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;

    push("one=uno&two=due&three=tre");

    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;

    push("R=red&B=blue&G=green");

    std::cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << std::endl;
}
