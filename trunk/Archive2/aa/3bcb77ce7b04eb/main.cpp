class AClass {
public:
  struct AStruct { };

private:
  const AStruct m_struct {};
};

int main() {
  AClass a;
}
