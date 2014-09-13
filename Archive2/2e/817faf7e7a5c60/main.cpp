#include <stdlib.h>
#include <stdio.h>

auto terminal = [] (auto term) {
    return [=] (auto func) {
		return func(term);
	};
};

auto fmap = [] (auto f) {
	return [=] (auto t) {
		return terminal(f(t));
	};
};

int main() 
{
	auto hello = [] (auto s) { fprintf (s, "Hello "); return s;};
	auto world = [] (auto s) { fprintf (s, "world "); return s;};
	auto newline = [] (auto s) {fprintf (s, "\n"); return s;};
	
	terminal(stdout)
		(fmap(hello))
		(fmap(world))
		(fmap(newline));
		
	return EXIT_SUCCESS;
}
