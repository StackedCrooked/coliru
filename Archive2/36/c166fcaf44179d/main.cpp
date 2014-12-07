#include <string>
#include <algorithm>
#include <locale>
#include <limits>
#include <exception>
#include <list>
#include <iostream>
#include <functional>

    class myclass
    {
        private:
        std::string s;
        public:
        static bool isnewline(char ch)
        {
            return '\r' == ch || '\n' == ch;

        }
        void splitlines(bool keepends = false)
        {
            std::string::const_iterator start_of_line = s.begin();
            std::string::const_iterator end_of_line = s.end();
            std::string::const_iterator new_line = std::find_if(s.cbegin(), end_of_line, &myclass::isnewline);
        }
    };

int
main() { }
