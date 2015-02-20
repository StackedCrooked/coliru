
struct foo
{
    foo(volatile bool& b) : bar(b) {}
	volatile bool& bar; 
};


int main() {
	volatile bool b = true;
	foo f(b);
	return 0;
}