template <typename T = int>
struct thingo {
  int always;
  T sometimes;
};

int main()
{
    thingo <> compile_error; // <- compiles now
    thingo <float> wastes_space;
    return 0;
}