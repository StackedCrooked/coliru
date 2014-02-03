#include <iostream>
#include <vector>
#include <memory>

class TCPConnection {
    int inst;
    static int inst_count;
public:
    TCPConnection() { inst=inst_count++; std::cout << "TCPConnection created: " << inst << std::endl; }
    ~TCPConnection() { std::cout << "TCPConnection destroyed:" << inst << std::endl; }
};
int TCPConnection::inst_count;

// version if If c++11 is available, can be also implemented with boost::shared_ptr
// Removing individual TCPConnection from vector will also decrement its shared_ptr
// usage count and if it is zero then will destroy also such connections.
typedef std::shared_ptr<TCPConnection> TCPConnectionPtr;
typedef std::vector<TCPConnectionPtr> TCPConnectionPtrVec;

void fun1() {
    TCPConnectionPtrVec vec;
    vec.push_back(TCPConnectionPtr(new TCPConnection()));
}

// version for pre c++11 compiler, but I would recomend using boost::shared_ptr
// Class TCPConnectionsVecWrapper is a helper to make sure connections are safely freed.
class TCPConnectionsVecWrapper {
    // No copying allowed
    TCPConnectionsVecWrapper( const TCPConnectionsVecWrapper& );
    TCPConnectionsVecWrapper& operator=( const TCPConnectionsVecWrapper& );    
    
    typedef std::vector<TCPConnection*> TCPConnectionPtrsVec;    
    TCPConnectionPtrsVec vec;    
public:
    TCPConnectionsVecWrapper() {}
    ~TCPConnectionsVecWrapper() {
        for (TCPConnectionPtrsVec::const_iterator itr = vec.begin(); itr != vec.end(); ++itr) delete *itr;
    }
    
    TCPConnection* createConnection() {
        vec.push_back(new TCPConnection());
        return vec.back();
    }
    
    void remove(int index) {
        delete vec[index];
        vec.erase(vec.begin() + index);
    }
    
    TCPConnection* get(int index) { return vec[index]; }
    const TCPConnection* get(int index) const  { return vec[index]; }
    
    std::size_t size() const { return vec.size(); }        
};

void fun2() {
  // All TCPConnection will get deleted once tcpConnectionsWrapper is out of scope
  // Removing individual connections requires calling delete on them.
  TCPConnectionsVecWrapper conns; 
  
  TCPConnection* con1 = conns.createConnection();
  (void)con1; // unused
  TCPConnection* con2 = conns.createConnection();
  (void)con2; // unused
  
  for ( size_t i = 0; i < conns.size(); ++i ) {
    TCPConnection* con = conns.get(i);
    (void)con; // unused
  }
  conns.remove(0);
}

int main(int argc, char** argv){ 
    fun1();
    fun2();
}
    