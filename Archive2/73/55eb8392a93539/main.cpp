using DWORD = unsigned int;

constexpr DWORD const_getHash(const char *str, DWORD curHash = 0) {
    return !*str ? curHash : const_getHash(str + 1,
        (curHash >> 13 | curHash << (32 - 13)) + (*str >= 'a' ? *str - 32 : *str));
}

int main(int, char**)
{
  constexpr DWORD hash = const_getHash("ok");
  static_assert(hash > 0, "woops");
}
