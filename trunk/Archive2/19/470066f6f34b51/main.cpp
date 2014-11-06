#include <cstddef>
 
void function(void*) {}
 
struct foo
{
    operator std::nullptr_t()
	{
		return nullptr;
	}
};
 
int main()
{
	function(foo());
}