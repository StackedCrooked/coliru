#include <iostream>
#include <unordered_map>
#include <mutex>

template<typename T>
class ObjectPool
{
private:
  struct Node
  {
    
    Node *_prevNode;
	Node *_nextNode;
	 T* value;
    Node( )
	{
		value = new T();
        std::cout << " created node " <<std::endl;
	}
	
    ~Node()
    {
      delete value;
      std::cout << " destroying node " <<std::endl;
    }
   };
   
	
	Node* head;
	Node* tail;
	Node* firstfree;
    typename std::unordered_map<T*,Node*> tnmap;
	std::mutex op_mutex;
	
	
	void _pushbackNewNode()
	{
		Node* n = new Node();
        tnmap[n->value] = n;
		if (tail){
			
			_insertNodeAfter(n,tail);
			
		}
		else{
			
			head = n;
			tail = n;
		}
	}	
		
	void _removeNode(Node * n)
	{
        
        if (!n->_prevNode && !n->_nextNode){
            // this node is not connected so nothing to do to remove.
            return;
        }
        
		if (n->_prevNode){
				n->_prevNode->_nextNode = n->_nextNode;
			}
            else{
                // must be head 
                head = n->_nextNode;
            }
        
		if (n->_nextNode){
				n->_nextNode->_prevNode = n->_prevNode;
		}
        else{
            //must be tail
            tail = n->_prevNode;
        }
        
			
		return;
	}
	
	void _insertNodeAfter(Node* n, Node* after){
	
			n->_prevNode = after;
			Node * oldafter = after->_nextNode;
			after->_nextNode= n ;
			
			
			if(oldafter){
				//the node was linked
				oldafter->_prevNode = n;	
			}
			else{
				// it was the tail
				tail =n;
			}
			n->_nextNode = oldafter;
			
	}
		
	void _moveNodeAfter(Node* n, Node* after){
	
			//first plug gap in old position
			_removeNode(n);
			_insertNodeAfter(n,after);
	
	}
	
	void _releaseNode(Node * n)
	{
		_moveNodeAfter(n,tail);
		if (!firstfree){
			//there was no free node so the firstfree is this one
			firstfree = n;
		}
		
	}
	
	
	T* _allocateNode(Node * n)
	{
		T* toret = n->value;
		firstfree = n->_nextNode;
		
		return toret;
	}
	
	public:
	
		ObjectPool():head(nullptr),tail(nullptr),firstfree(nullptr)
	{
	}
	
		~ObjectPool()
		{
			Node* curn = head;
			Node * nextn;
			while(curn!=nullptr){
				nextn = curn->_nextNode;
				delete curn;
				curn = nextn;
			}
		}
	
	
		T* hold()
		{
			
            std::lock_guard<std::mutex> lock(op_mutex);
            if(!firstfree){
				_pushbackNewNode();
				firstfree = tail;
			}
			
			return _allocateNode(firstfree);
			
		}
		
		void release(T* valrel)
		{
            std::lock_guard<std::mutex> lock(op_mutex);
			// parcoure la liste
            typename std::unordered_map<T*,Node*>::iterator it = tnmap.find(valrel);
            
            if(it != tnmap.end()){
                   Node* curn = it->second;
                    _releaseNode(curn);
                }
			
		}
	
  };
  
  
struct A {
    int i ;
	A(){std::cout << " created A " <<std::endl;}
    ~A(){std::cout << " destroyed A " <<std::endl;}
	};
 
 int main(int argc, char *argv[])
 {
      ObjectPool<A> op;
	  
	  A* first = op.hold();
	  A* second = op.hold();
	  A* third = op.hold();
	  first->i = 1;
	  second->i =2 ;
	  third->i =3;
	  
	  op.release(second); 
	  op.release(first); 
      op.release(third); 
	  A* isitsecond = op.hold();
      std::cout << isitsecond->i  << std::endl;
      A* isitfirst = op.hold();
      std::cout << isitfirst->i  << std::endl;
	  
	   A* isitthird = op.hold();
      std::cout << isitthird->i  << std::endl;
      
	  A* notinpool ;
      op.release(notinpool);
	  //delete notinpool;
 }