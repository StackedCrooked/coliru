constexpr const char *StrChr(const char *Str, const char C) {
    for (; *Str; ++Str) {
        if (*Str == C) {
            return Str;
        }
    }

    return nullptr;
}

int main() {
    static_assert(StrChr("abcdefghijkl", 'f')[1] == 'g', "");
}