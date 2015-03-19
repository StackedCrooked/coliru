#include <algorithm>
#include <memory>
#include <iostream>
#include <string>
#include <vector>

template <typename Iter>
void rot13(Iter begin, const Iter& end) {

    while (begin != end) {

        //Doesn't need to be here, but I'm lazy and don't like
        //typing *begin over and over again.
        char& c = *begin;

        if (c >= 'a' && c <= 'm') {
            c += 13;
        } else if (c >= 'n' && c <= 'z') {
            c -= 13;
        } else if (c >= 'A' && c <= 'M') {
            c += 13;
        } else if (c >= 'N' && c <= 'Z') {
            c -= 13;
        }

        ++begin;
    }
}


class Test
{
    public:
        Test(std::unique_ptr<std::string> str) :
        m_txt(std::move(str))
        {
        }

        ~Test() = default;

        void Print()
        {
            std::string s(*m_txt);
            rot13(s.begin(), s.end());
            
            std::cout << s << std::endl;
        }

    private:
        std::unique_ptr<std::string> m_txt;
};

int main()
{
    std::unique_ptr<Test> t = std::make_unique<Test>((std::make_unique<std::string>("G'rf ienvzrag dh'ha pbaaneq.")));
    t->Print();
}
