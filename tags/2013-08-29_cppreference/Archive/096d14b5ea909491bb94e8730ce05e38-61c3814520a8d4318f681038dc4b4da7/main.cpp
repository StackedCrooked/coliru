 #include <string>
#include <unordered_map>
 
 
using namespace std;
 
 
class compare {
    public:
		bool operator()(const string& x, const string& y) const { 
			return x==y;
		}
};
 
int main(int argc, char* argv[])
{
	unordered_map<string, int, std::hash<std::string>, compare> map;
	string a = "test";
	map.insert({a,13});
}