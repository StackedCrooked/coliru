template <typename T>
struct Yin {
  T *m_ptr;
};

template <typename T>
struct Yang {
  T *m_ptr;
};

struct mutual_yin_yang;

template <>
struct Yin<mutual_yin_yang> {
  Yang<mutual_yin_yang> *m_ptr;
};

template <>
struct Yang<mutual_yin_yang> {
  Yin<mutual_yin_yang> *m_ptr;
};

int main() {
    Yin<mutual_yin_yang> a {}; 
    Yang<mutual_yin_yang> b {};
    a.m_ptr = &b;
    b.m_ptr = &a;
    //proof of recursion
    a.m_ptr->m_ptr->m_ptr->m_ptr->m_ptr->m_ptr->m_ptr->m_ptr->m_ptr->m_ptr->m_ptr->m_ptr->m_ptr->m_ptr->m_ptr;
    return 0;
}