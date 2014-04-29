#include <map>
#include <list>

using namespace std;

class Foo
{
};

static void UnRegister(unsigned int, std::list<Foo*>::iterator){}
int main() 
{
    std::map<unsigned int, std::list<Foo*>::iterator> listeners;

	UnRegister(0, listeners[0]);
}