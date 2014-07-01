class T
{
public:    
	void (*f)(int);
};

int main()
{
	T t;
	t.f = [](int a) {};
}

