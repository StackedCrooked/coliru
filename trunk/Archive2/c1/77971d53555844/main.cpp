

template<typename It, typename ReverseIt>
bool isPalindrome(It begin, ReverseIt rbegin) {
    return begin == rbegin || (*begin == *rbegin && isPalindrome(++begin, ++rbegin));
}