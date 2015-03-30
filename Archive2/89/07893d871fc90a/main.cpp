#include <atomic>
#include <string>
#include <vector>

std::string g_str;
std::vector<char> g_vec;

void
copy_str(const std::string &str) {
    g_str = str;
}

void
copy_vec(const std::vector<char> &vec) {
	g_vec = vec;
}

int
main(int ac, char **av) {
	if (ac != 2 || (av[1][0] != 's' && av[1][0] != 'v')) {
		fprintf(stderr, "invalid arguments");
		return 1;
	}

	const char *cp = "foo";
	for (int i = 0; i < 10 * 1000 * 1000; i++) {
		if (av[1][0] == 's') {
			std::string s(cp);
			copy_str(s);
		} else {
			std::vector<char> v(cp, cp + 4);
			copy_vec(v);
		}
		std::atomic_signal_fence(std::memory_order_seq_cst);
	}
	return 0;
}
