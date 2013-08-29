class Foo {}

Class Bar {

public:
    Bar(Foo* f);

}


class myApp{
public:
	int main();
	Foo foo;
	//I want to do this:
	extern Bar bar;	
	//But obviously it won't work
}

int myApp::main ()
{
	Bar bar(&foo);
}