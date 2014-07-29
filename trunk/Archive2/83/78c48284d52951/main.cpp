#include <iostream>
#include <vector>

class MultiStream {
    public:
		MultiStream& add(std::ostream& s)
		{
			streams.push_back(&s);
			return *this;
		}
		
		template<typename T> MultiStream& operator<<(const T& item)
		{
			for (std::ostream* s : streams)
			{
				*s << item;
			}
			return *this;
		}
		
	private:
		std::vector<std::ostream*> streams;
};

int main()
{
	MultiStream ms;
	ms.add(std::cout).add(std::cerr);
	ms << "Hello!\n";
	return 0;
}