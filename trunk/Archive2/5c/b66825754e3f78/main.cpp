#include <iostream>
#include <memory>

void Euler14(int N = 1000000)
{
    auto memo = std::make_unique<int[]>(N);
	int max_chain = 0, max_index = 0;

	for (int i = 1; i < N; ++i) {
		int chain = 1;
		for (long long link = i; link > 1; ++chain) {
			link = (link & 1) ? (3 * link + 1) : (link / 2);
			if (link < i) {
				chain += memo[link];
				break;
			}
		}
		if (max_chain < chain) {
			max_chain = chain;
			max_index = i;
		}
		memo[i] = chain;
	}
	std::cout << "14. longest(" << N << ")=" << max_index << '\n';
}

int main()
{
    Euler14();
}
