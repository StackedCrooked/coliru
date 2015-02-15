#include <iostream>
#include <string>
#include <vector>
using std::cout;

template<class mytype>
class OrderedList
{
public:
  
    OrderedList(int cap);
    OrderedList(const OrderedList& li);
    ~OrderedList();
    /**
     * Precondition:
     * Postcondition: 
     */
    void operator=(const OrderedList& li);
    /**
     * Precondition:
     * Postcondition: 
     */
    int size() const {
        return count;
    }
    /**
     * Precondition:
     * Postcondition: 
     */
    mytype get(int pos) const;
    /**
     * Precondition:
     * Postcondition: 
     */
    OrderedList<mytype>* kLargest(int num);
    /**
     * Precondition:
     * Postcondition: 
     */
    void insert(mytype item) ;
    /**
     * Precondition:
     * Postcondition: 
     */
    void remove(mytype item);
    
    /**
     * Precondition:
     * Postcondition: 
     */
     // I CHANGED THIS HERE TO MAKE IT A TEMPLATE
    template<class T>
    friend OrderedList<T> operator+  (const OrderedList<T>& a, const OrderedList<T>& b);
    /**
     * Precondition:
     * Postcondition: 
     */
     // HERE TOO!!
     template<class T>
    friend std::ostream& operator<<(std::ostream& out, const OrderedList<T>&);
    
private:
    void enlarge();
    void order();
    int capacity;
    mytype *list;
    int count; // how many items are actually in the array
};

template<class mytype>
OrderedList<mytype>::OrderedList(int cap)
{
    list = new mytype[cap];
    capacity = cap;
    count = 0;
}
template<class mytype>
OrderedList<mytype>::OrderedList(const OrderedList& li)
{
    *this = li;
}
template<class mytype>
OrderedList<mytype>::~OrderedList()
{
 
}
template<class mytype>
void OrderedList<mytype>::operator=(const OrderedList& li)
{
    if(list != NULL)
    {
        delete [] list;
    }
    count = li.count;
    capacity = li.capacity;
    list = new mytype[capacity];
    for(int i=0;i<count;i++)
    {
        list[i] = li.list[i];
    }
    
        
}
template<class mytype>
void OrderedList<mytype>::insert(mytype item) 
{
   // check if list is full
   // if it is, make it longer
    if(capacity == count)
    {
        enlarge();
    }
    //append item to the end of the list and increase size
    list[count++] = item;
    order();
}
template<class mytype>
void OrderedList<mytype>::enlarge()
{
    capacity = (int)(1.5*capacity);
    mytype * newList = new mytype[capacity];
    for(int i=0;i<count; i++)
        newList[i] = list[i];
    delete [] list;
    list = newList;
}
template<class mytype>
std::ostream& operator<<(std::ostream& out, const OrderedList<mytype>& li)
{
    out<<"[";
    for(int i=0;i<li.count-1;i++)
        out << li.list[i] <<", ";
    out << li.list[li.count-1] <<"]";
    return out;
}

template<class mytype>
void OrderedList<mytype>::order()
{
    for(int i=0; i<count; i++)
    {
        for(int j=i; j<count-1; j++)
        {
            if(list[i]>list[j+1])
            {
            mytype temp = list[i];
            list[i] = list[j+1];
            list[j+1] = temp;
            }
        }
    }
}

template<class mytype>
void OrderedList<mytype>::remove(mytype item)
{
    int i=0; 
    for(;i<count; i++)
        if(list[i] == item)
            break;
       
    
    for(int j=i; j<count-1;j++)
        list[i] = list[i+1];

     count--;
}

template<class mytype>
mytype OrderedList<mytype>::get(int pos) const
{
    return list[pos];
}

template<class mytype>
 OrderedList<mytype>* OrderedList<mytype>::kLargest(int num)
{
    int counter = count;
    OrderedList<mytype> *newList = new OrderedList<mytype>(num);
    for(int i=num; i>0; i--)
    {
        (*newList).insert(list[i]);
    }
    return newList;
}

template<class mytype>
OrderedList<mytype> operator+ (const OrderedList<mytype>& a,const OrderedList<mytype>& b)
{
    int size = a.size() + b.size();
    int i=0, j=0, k=0;
    OrderedList<mytype> newList(size);
    
       while (i < a.size() && j < b.size()) 
       {
            if (a.get(i) <= b.get(j)) 
            {
                 newList.list[k] = a.list[i];
                  i++;
            } else 
           {
                 newList.list[k] = b.list[j]; // WHICH LIST????
                 j++;
           }
            k++;
      
      if (i < a.size())
      {
            for (int p = i; p < a.size(); p++) 
            {
                  newList.list[k] = a.list[p];
                 k++;
            }
      } else 
      {
            for (int p = j; p < b.count; p++) 
            {
                  newList.list[k] = b.list[p];
                 k++;
            }
      }
    }
//    
//    
    
    return newList;
}

template<class mytype>
class OrderedList;

template <class mytype>
OrderedList<mytype> operator+  (const OrderedList<mytype>& a, const OrderedList<mytype>& b);


template<class mytype>
std::ostream& operator<<(std::ostream& out, const OrderedList<mytype>&);

int main()
{
    OrderedList<double> li(10);
    li.insert(4.0);
    li.insert(550);
    li.insert(23.9);
    
   OrderedList<double> li2(10);
   li2.insert(4.6);
   li2.insert(1.0);
   li2.insert(45.6);


   OrderedList<double> li3 = li+li2;
   cout << li3;
}