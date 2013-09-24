struct a {
    int x;
};

struct b {
	int x;
};

struct c : virtual a, virtual b {
	int x;
};

struct d : virtual a, virtual b, c {
	void fn() { x = 5; }
};

int main() {
	return 0;
}