// f.h
auto f();

////////
// f.cc
auto f()
{
    return 10;
}

///////
// main.cc

template <typename F>
void run(const F& f)
{
}

int main() {
    run(f);

	return 0;
}