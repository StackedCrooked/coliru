#include <iostream>
#include <thread>
class eg
{
public:
    eg(char *test)
	{
		t = test;
	}
	
private:
	char *t;
};

int main(int argc, char **argv)
{
	eg("hello");
	
	return 0;
}
