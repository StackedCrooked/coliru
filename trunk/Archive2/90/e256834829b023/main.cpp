struct StrPair {
    const char* s1;
    const char* s2;
};

StrPair s0[] = {
    {"a", "b"}, {"c", "d"}
};

struct C
{
  static constexpr StrPair s1[]={ {"a", "b"}, {"c", "d"} };
  //static StrPair s2[]={ {"a", "b"}, {"c", "d"} };
  //static const StrPair s3[]={ {"a", "b"}, {"c", "d"} };
};

int main(int argc, char** argv)
{
}
