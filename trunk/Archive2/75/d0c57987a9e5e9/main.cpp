#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <regex>

namespace
{
    std::vector<std::string> get_names(const std::string& sentence)
    {
        std::regex author_regex("(?!:)[^ ]+\\w+, (\\w.)+", std::regex_constants::ECMAScript);
        std::vector<std::string> names(std::sregex_token_iterator(sentence.begin(), sentence.end(), author_regex), std::sregex_token_iterator());
        return names;
    }
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}
/*
int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;

   const std::string citations[] = {"Smith, M.N., Martin, G., Erdos, P.: Newtonian forms of prime factor matrices",
                                    "Erdos, P., Reisig, W.: Stuttering in petri nets",
                                    "Smith, M.N., Chen, X.: First oder derivates in structured programming",
                                    "Jablonski, T., Hsueh, Z.: Selfstabilizing data structures"};
   //std::set<std::string> all_authors;

   for (const auto& citation : citations) {
      auto citation_authors = get_names(citation);
      std::cout << citation_authors << std::endl;
      //std::copy(citation_authors.begin(), citation_authors.end(), std::back_inserter(all_authors));
   }
   

}*/

#include <iostream>
#include <array>
#include <memory>

class A
{
public :
   A() { std::cout << "A  " << std::endl; }
   virtual ~A() = default;
   virtual void f() { std::cout << "1 " << std::endl; }
};

class B : public A
{
public:
	B() { std::cout << "B  " << std::endl; }
    virtual ~B() = default;
    virtual void f() override { std::cout << "2  " << std::endl; }
protected:
    std::array<char, 2048> buffer_;
};

int main()
{
	std::unique_ptr<A> p(std::make_unique<B>());
    p->f();

    return 0;
} 

