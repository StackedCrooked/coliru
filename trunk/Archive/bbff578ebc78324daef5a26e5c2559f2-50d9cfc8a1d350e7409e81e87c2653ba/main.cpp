class Foo {};

class Bar {

public:
    Bar(Foo*) {}

};


class myApp{
public:
	int main();

    myApp(): bar(&foo) {}

	Foo foo;
	Bar bar;
};

int myApp::main ()
{
}

int main()
{
    myApp {}.main();
}