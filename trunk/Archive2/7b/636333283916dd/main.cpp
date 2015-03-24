
class bad { 
public:
    void f(int) {}
private:
	void f(double) {}
};

int main() { 
	bad b;
	b.f(1.23);
}
