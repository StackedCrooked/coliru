#include <iostream>
#include <string>
#include <vector>

template <class T>
struct batman;

template <class T>
struct batman_node
{
friend batman<T>;
    
public:
  T value;
  
  batman_node<T>* next(void)
  {
      return m_n;
  }
  
  batman_node<T>* prev(void)
  {
      return m_p;
  }

private:
  batman_node<T>* m_p;
  batman_node<T>* m_n;

};

template <class T>
struct batman
{
public:
  batman()
  {
      m_head = nullptr;
  }

  void add(T p_val)
  {
    if (m_head == nullptr)
    {
      m_head = new batman_node<T>;
      m_head->value = p_val;
      m_head->m_n = m_head;
      m_head->m_p = m_head;
      printf("added %i\n", m_head->value);
    }
    else
    {
      batman_node<T>* ol = m_head->m_p;
      ol->m_n = new batman_node<T>;
      batman_node<T>* ne = ol->m_n;
      ne->m_p = ol;
      ne->m_n = m_head;
      ne->value = p_val;
      printf("added %i\n", ne->value);
      
    }
       batman_node<int>* now = m_head;
    
    do
    {
        printf("-- %i\n", now->value);
        now = now->m_n;
    }
    while(now != m_head);
  }

  batman_node<T>* head(void)
  {
      return m_head;
  }

private:
  batman_node<T>* m_head;
  
};

int main()
{
    batman<int> b;
    b.add(5);
    b.add(7);
    b.add(8);
    
    batman_node<int>* now = b.head();
    
    do
    {
        printf("!!!!! %i\n", now->value);
        now = now->prev();
    }
    while(now != b.head());
    
    b.add(2);
    b.add(3);
    
    printf("%s\n", "Nananananananannanannana, batman!");
}
