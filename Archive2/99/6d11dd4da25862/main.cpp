
#include <string>
struct Spam
{
    Spam();
	explicit Spam(bool flag);
	Spam(const std::initializer_list<std::pair<const std::string, Spam > > &  il);
	Spam(const std::initializer_list<Spam > & il);
};
int main()
{
	Spam({ { "1", Spam() }, { "2", Spam() } });
}