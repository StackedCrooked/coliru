class Parent
{
  public:
    virtual int get_b(unsigned int index) = 0;
  protected:  
    int a;
};

template<int count>
class Child : public Parent
{
  public:
    int get_b(unsigned int index) { return b[index]; }
  private:
    int b[count];
};

Parent* make_Parent(int count) {
    if (count <= 8) return new Child<8>();
    if (count <= 16) return new Child<16>();
    if (count <= 32) return new Child<32>();
    if (count <= 64) return new Child<64>();
    if (count <= 128) return new Child<128>();
    if (count <= 256) return new Child<256>();
    if (count <= 512) return new Child<512>();
    throw std::bad_alloc();
}