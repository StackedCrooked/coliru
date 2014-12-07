#include <vector>
#include <iostream>

class foo {

public:
    virtual int read() { return 0; }
};

class bar : public foo {
	
public:
	int read() override { return 1; }
};
 
int main()
{ 
	std::vector<foo> a;
	
	a.push_back( foo() );
	a.push_back( bar() );

	std::cout << a[0].read() << a[1].read();
}
