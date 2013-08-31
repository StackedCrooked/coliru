template <void (*INIT)(), void (*DESTROY)()>
class Initializer
{
public:

    Initializer();

	~Initializer();
};


template <void (*INIT)(), void (*DESTROY)()>
Initializer<INIT, DESTROY>::Initializer()
{
	INIT();
}


template <void (*INIT)(), void (*DESTROY)()>
Initializer<INIT, DESTROY>::~Initializer()
{
	DESTROY();
}


//Then, just include a static instance of Initializer<> at the bottom
// of your class definition, and you have a cheap and free "static constructor".