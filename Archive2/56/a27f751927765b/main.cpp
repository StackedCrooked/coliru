
struct foo
{
    foo(bool& b) : bar(b) {}
	bool& bar; 
};


int main() {
	volatile bool b = true;
	foo f(b);
	return 0;
}