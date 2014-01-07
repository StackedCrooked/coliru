#include <string>

struct DummyPolicy { };

template <typename>
struct Policy1 { Policy1(int, std::string) { } };

template <typename T,
          typename P1 = Policy1<T> >
struct X 
{
     X(P1 p1 = {}) : _policy1(std::move(p1)) { }

   private:
     P1 _policy1;
};

int main()
{
     X<int, DummyPolicy> no_questions_asked;
     X<int> use_params({42, "hello world"});
}
