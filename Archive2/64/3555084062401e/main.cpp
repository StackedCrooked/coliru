#include <iostream>
struct D;
struct S{ operator D(); };

struct D{
    D() { std::cout << "plop" << std::endl; }
    D(D&&) { std::cout << "move constructor" << '\n'; }
};

S::operator D() { std::cout << "conversion function" << '\n'; return D(); }

#include <array>
#include <memory>

enum class Position
{
  Left,
  Middle,
  Right
};

template <typename T>
class Node
{
public:
  Node(T x) : x_(x) {}
  T x_;
  bool addChildren(Node && children, Position position)
  {
      childrens_[(int)position] = std::make_unique<Node>(std::move(children));
      return true;
  }
  
  int size() const
  {
      int count = 1;
      for (int i = 0 ; i < 3 ; ++i)
      {
        count += (childrens_[i] != nullptr) ? childrens_[i]->size() : 0;
      }
      
      return count;
  }
  
  bool hasChildren() const
  {
      for (int i = 0 ; i < 3 ; ++i)
      {
        if (childrens_[i] != nullptr)
        {
            return true;
        }
      }
      return false;
  }
  
  void print() const
  {
      std::cout << x_;
      if (hasChildren()) std::cout << "\n";
      for (int i = 0 ; i < 3 ; ++i)
      {
        if (childrens_[i] != nullptr)
        {
            childrens_[i]->print();
        }
      }
  }
  
private:
  std::array<std::unique_ptr<Node<T>>, 3> childrens_;
};

#include <unordered_map>

namespace lol
{
    enum class Status
    {
        idle,
        sent    
    };
    
    class Order
    {
        friend class Connection;
    public:
        Order() = delete;
        Order(Order&&) = default;
        Order& operator=(Order&&) & = default;

        virtual ~Order() {}

        void status(Status status) { status_ = status; }
        Status status() const { return status_; }

        int id() const { return id_; }
        std::string getLastError() const { return error_; }        
        
    private:
        Order(int id, int x, int y, int z) : id_(id) {}
        Order(const Order&) = default;
        Order& operator=(const Order&) & = default;
        
        int id_;
        Status status_ = Status::idle;
        std::string error_;
    };
    
    class Connection
    {
    private:
        static int nextOrderId_;
        Order dumbOrder{-1, 0, 0, 0};
    public:
        Order createNewSingleOrder(int x, int y, int z)
        {
            Order o{nextOrderId_++, x, y, z};
            return o;
        }
        
        std::pair<Status, int> send(Order & o)
        {
            o.status(Status::sent);
            Status status = o.status();
            int id = o.id();
            orderBook_.insert(std::make_pair(id, std::move(o)));
            return std::make_pair(status, id);
        }
        
        Order findOrder(int id)
        {
            auto found = orderBook_.find(id);
            if (found != std::end(orderBook_))
            {
                Order foundOrder{found->second};
                return foundOrder;
            }
            
            return dumbOrder;
        }
        
    private:
        std::unordered_map<int, Order> orderBook_;
    };
    
    int Connection::nextOrderId_ = 0;
}


int main()
{
    //S s;
    //D d{D{}};
    /*
    Node<int> tree(0);
    tree.addChildren(Node<int>(1), Position::Left);
    tree.addChildren(Node<int>(2), Position::Middle);    
    tree.addChildren(Node<int>(3), Position::Right);
    
    std::cout << tree.size() << std::endl;
    tree.print();
    
    const int * pToto = new int(1);
    delete pToto;*/
    using namespace lol;
    Connection c;
    int orderId1, orderId2;
    // Creation test
    {
        auto order = c.createNewSingleOrder(1, 2, 3);
        std::cout << "Order id[" << order.id() << "]\n";
        auto order2 = c.createNewSingleOrder(1, 2, 3);    
        std::cout << "Order2 id[" << order2.id() << "]\n";    

        auto result1 = c.send(order);
        orderId1 = result1.second;
        auto result2 = c.send(order2);
        orderId2 = result2.second;
    }
    
    // Find test
    {
        auto order = c.findOrder(orderId1);
        std::cout << "Order id[" << order.id() << "]\n";
        auto order2 = c.findOrder(orderId2);
        std::cout << "Order2 id[" << order2.id() << "]\n";    
        auto order3 = c.findOrder(12);
        std::cout << "Order3 id[" << order3.id() << "]\n";            
    }
    
}