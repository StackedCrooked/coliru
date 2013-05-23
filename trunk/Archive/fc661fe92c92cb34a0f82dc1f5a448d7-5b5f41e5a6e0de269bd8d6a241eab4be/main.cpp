template <typename T1>
class LList 
{
         class Node;
  public:
         class Iterator
         {
               public:
                      Iterator();
                      T1 get() const;
                      void next();
                      void previous();
                      bool equals(Iterator iter) const;
               private:
                       Node* position;
                       LList* container;
         };

         LList();
         ~LList();
         void pushBack(T1 data);
         Iterator begin();
         Iterator end();
         void insert (Iterator iter, T1 data);
         Iterator erase(Iterator Iter);
  private:
         class Node
         {
               public:
                      Node(T1 data);
               private:
                       T1 data;
                       Node* ptr_next;
                       Node* ptr_prev;
         };
         Node* ptr_first;
         Node* ptr_last;
};

template <typename T1> 
LList<T1>::Node::Node(T1 data)
{
     this->data = data;
     ptr_next = 0;
     ptr_prev =0;
}

template <typename T1> 
LList<T1>::Iterator::Iterator()
{
    position = 0;
    container = 0;
}

template <typename T1> 
T1 LList<T1>::Iterator::get() const
{
    return position->data;
}

template <typename T1> 
void LList<T1>::Iterator::next()
{
    if(position == container->ptr_last)
    {
                position = container->ptr_first;
    }
    else
    {
                position = position->ptr_next;
    }
}

template <typename T1> 
void LList<T1>::Iterator::previous()
{
 if(!position)
 {                  
                    position = container->ptr_last;
 }
 else
 {
     position = position->ptr_prev;
 }
}

template <typename T1> 
bool LList<T1>::Iterator::equals(Iterator iter) const
{
 return position == iter.position;
}

template <typename T1>      
LList<T1>::LList()
{
  ptr_first = 0;
  ptr_last = 0;
}

template <typename T1> 
LList<T1>::~LList()
{
  while (ptr_first)
  {
        Node* tmp = ptr_first;
        ptr_first = ptr_first->ptr_next;
        delete tmp;
        tmp = 0;
  }
}

template <typename T1> 
void LList<T1>::pushBack(T1 data)
{
 Node* new_node = new Node(data); 
 if(ptr_first==0)
 {
       ptr_first = new_node;
       ptr_last = new_node;
 }
 else
 {
     ptr_last->ptr_next = new_node;
     new_node->ptr_prev = ptr_last;
     ptr_last = new_node;
  }
 }          

 template <typename T1> 
 typename LList<T1>::Iterator LList<T1>::begin()
 {
     Iterator iter;
     iter.positon = ptr_first;
     iter.container = this;
     return iter;
  }

template <typename T1> 
 typename LList<T1>::Iterator LList<T1>::end()
{
     Iterator iter;
     iter.position = ptr_last;
     iter.container = this;
     return iter;
 }

 template <typename T1> 
 void LList<T1>::insert(Iterator iter, T1 data)
 {
     if (iter.position == 0)
     {
         pushBack(data);
         return;
     }
     Node* before;
     Node* after;
     after = iter.position;
     before = iter.position->ptr_prev;
     Node* new_node = new Node(data);

     after->ptr_prev = new_node;
     if (before == 0) ptr_first = new_node;
     else before->ptr_next = new_node;

     new_node->ptr_prev = before;
     new_node->ptr_next = after;
  }                             

  template <typename T1> 
   typename LList<T1>::Iterator LList<T1>::erase(Iterator iter)
  {
     Node* after = iter.position->ptr_next;
     Node* before = iter.position->ptr_prev;
     Node* remove = iter.position;
     if (remove == ptr_first) ptr_first = after;
     else before->ptr_next = after;
     if (remove == ptr_last) ptr_last = before;
     else after->ptr_prev = before;
     delete remove;
     remove = 0;
   }
   
   int main()
   {
       return 0;
   }