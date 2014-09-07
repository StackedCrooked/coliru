class A
{
public:
    A(int i){ a = i; }
	A(double j){ b = j; }
private:
	int a;
	double b;
};

class B :public A
{
public:
	using A::A;
};
int main() 
{
    B b(1);
}