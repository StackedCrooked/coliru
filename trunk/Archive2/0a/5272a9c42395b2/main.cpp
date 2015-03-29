
#include <string>
struct Spam
{
    Spam();
	Spam(bool flag);
	Spam(const std::initializer_list<std::pair<const std::string, Spam > > &  il);
	Spam(const std::initializer_list<Spam > & il);
};
int main()
{
    using namespace std::literals;
	Spam({ { "1"s, Spam() }, { "2"s, Spam() } });
}