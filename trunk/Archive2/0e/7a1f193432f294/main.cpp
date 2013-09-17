#include <iostream>
#include <map>
#include <tuple>
#include <string>
#include <unordered_map>
 
 class MyClass {
    public:
		MyClass(int x, int y) : x(x), y(y) {
			printf("create %d %d\n", x, y);
		}
		MyClass(int x, MyClass y) : x(y.x), y(y.y) {
			printf("create2 %d %d\n", this->x, this->y);
		}
		MyClass(const MyClass &source) : x(source.x), y(source.y) {
			printf("copy %d %d\n", x, y);
		}
		MyClass(MyClass &&source) : x(source.x), y(source.y) {
			printf("move %d %d\n", x, y);
		}
		MyClass& operator=(const MyClass &source) {
			x = source.x;
			y = source.y;
			printf("=& %d %d\n", x, y);
			return *this;
		}
		MyClass& operator=(MyClass &&source) {
			x = source.x;
			y = source.y;
			printf("=&& %d %d\n", x, y);
			return *this;
		}
		int x, y;
	};
 
int main()
{
    /*std::map<int, std::string> m;
 
    m.emplace(std::forward_as_tuple(10, std::string(20, 'a')));
    std::cout << "m[10] = " << m[10] << '\n';*/
 std::unordered_map<int, MyClass> table;
table.emplace(0, MyClass(0, 0));

    table.emplace(std::make_pair(1, MyClass(1, 1)));
	
	table.insert(std::make_pair(2, MyClass(2, 2)));
	
	table.emplace(std::piecewise_construct, std::forward_as_tuple(3), std::forward_as_tuple(3, MyClass(3, 3)));
	table.emplace(std::piecewise_construct, std::forward_as_tuple(4), std::forward_as_tuple(4, 4)); 
    // The following is an error: it produces a
    // std::tuple<int&&, std::string&&> holding two dangling references.
    //
    // auto t = std::forward_as_tuple(10, std::string(20, 'a'));
    // m.emplace(t);
}