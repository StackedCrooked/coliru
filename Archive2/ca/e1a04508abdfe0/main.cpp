#include <iostream>
#include <memory>
#include <vector>

struct Session
{
    int data; 
    Session() { std::cout << '*'; }
    ~Session() { std::cout << " -DESTRUCT- "; }
};

int main()
{




  




  std::cout << "constructions (3): ";
  // allocates storage for five objects, but does not construct them:
  Session * pool = static_cast<Session*> (::operator new (sizeof(Session[5]),[] ));
  std::cout << '\n';

  std::cout << "constructions (4): ";
  // constructs five objects at p3, but does not allocate:
  
  Session * freeSession = pool;
  
  Session * session1 = new (freeSession) Session();
  
  std::shared_ptr<Session> p1 (session1);
  ++freeSession;
  Session * session2 = new (freeSession) Session;
  /**std::shared_ptr<Session> p2 (session2);
  
  std::vector<std::shared_ptr<Session>> poolList;
  poolList.push_back(p1);
  //delete[] pool;
**/

  return 0;
}
