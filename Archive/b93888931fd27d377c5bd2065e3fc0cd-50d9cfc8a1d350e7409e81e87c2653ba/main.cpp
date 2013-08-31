class Foo {};

class Bar {

public:
    Bar(Foo*) {}

};


class myApp{
public:
	int main();
	Foo foo;
	Bar bar = &foo;
};

int myApp::main ()
{
}

int main()
{
    myApp {}.main();
}