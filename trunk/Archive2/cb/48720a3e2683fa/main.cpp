#include <iostream>
#include <string>
#include <vector>

std::string g_str;
std::vector<char> g_vec;

int
main(int ac, char **av) {
    if (ac != 2 || (av[1][0] != 's' && av[1][0] != 'v')) {
		std::cerr << "invalid arguments\n";
		return 1;
	}

	const char cp[] = "foo-bar-baz-quuuuuuuuuux";
	for (int i = 0; i < 10 * 1000 * 1000; i++) {
		if (av[1][0] == 's') {
			std::string s(cp, sizeof(cp) - 1);
			g_str = s;
		} else {
			std::vector<char> v(cp, cp + sizeof(cp));
			g_vec = v;
		}
	}
	return 0;
}
