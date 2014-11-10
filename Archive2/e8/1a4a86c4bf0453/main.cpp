struct Object;

struct Const_Visitor
{
  // Visit function cannot modified the given object.
  virtual void visit(const Object& o) = 0;
};

struct Mutable_Visitor
{
  // The visit function may modify the given object;
  virtual void visit(Object& o) = 0;
};

struct Object{};
const unsigned int LIMIT = 16;
struct Container
{
  Object obj_container[LIMIT];

  template<class C, class V>
  static void for_each(C& c, V& v) {
    for (unsigned int i = 0; i < LIMIT; ++i)
    {
      v.visit(c.obj_container[i]);
    }
  }

  // Apply the read-only (constant) visitor
  // to each object in the container
  void for_each(Const_Visitor& cv) const
  {
    for_each(*this, cv);
  }


  // Apply the read/write (mutable) visitor
  // to each object in the container.
  void for_each(Mutable_Visitor& mv)
  {
    for_each(*this, mv);
  }
};