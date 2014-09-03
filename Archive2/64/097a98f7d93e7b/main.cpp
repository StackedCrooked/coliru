#include <iostream>
#include <string>
#include <vector>

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
	
	
	
	void _pushbackNewNode()
	{
		Node* n = new Node();
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
			if(!firstfree){
				_pushbackNewNode();
				firstfree = tail;
			}
			
			return _allocateNode(firstfree);
			
		}
		
		void release(T* valrel)
		{
			// parcoure la liste
            
            
            
			Node* curn = head;
			while(curn!=nullptr){
				if (valrel==curn->value){
					_releaseNode(curn);
					break;
				}
				curn = curn->_nextNode;
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