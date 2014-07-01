class T
{
public:    
	void (*f)(int);
};

int main()
{
    int k = 1;
	T t;
	t.f = [k](int a) {};
}

