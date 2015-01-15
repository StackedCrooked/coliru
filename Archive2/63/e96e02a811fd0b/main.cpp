#include <iostream>
#include <iomanip>
#include <unordered_map>

static bool is_anagram(const std::string &p, const std::string &q)
{
    std::unordered_map<char, std::size_t> m, n;
    for (char ch : p) {
        m[ch]++;
    }
    for (char ch : q) {
        n[ch]++;
    }
    return m == n;
}

int main()
{
    std::string s = "anagramma", q = "agarmamna", r = "ez nem az";
    std::cout << std::boolalpha << is_anagram(s, q) << std::endl;
    std::cout << std::boolalpha << is_anagram(q, s) << std::endl;
    std::cout << std::boolalpha << is_anagram(s, r) << std::endl;
	return 0;
}