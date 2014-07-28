typedef struct internal_data * Opaque;

struct internal_data {};

template<typename T>
struct Internal {
 T data;
};

template <typename T>
Opaque map_internal(Internal<T>* in)
{
  return reinterpret_cast<Opaque>(in);
}

template<typename T>
Internal<T>* Initialise(T data) {
  Internal<T>* t = new Internal<T>();
  t->data = data;
  return map_internal(t);
}

int main(int argc, char** argv)
{
  Opaque o = Initialise(argc);
  return 0;
}