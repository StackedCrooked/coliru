#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>

using namespace std;


#include <iostream>
using namespace std;
template <class T>
class  List
{    
	struct Node
	{
		T content;
		Node *next;
	};
	Node *head;
public:
	Node* input_element()
	{
		cout<<"please input the elements:"<<endl;
		head=NULL;
		Node *last=head;
		T x;
		while(cin>>x)
		{
			Node *p=new Node;
			p->content=x;
			p->next=NULL;
			if(head==NULL)
				head=p;
			else
				last->next=p;
			last=p;
		}
	return head;
	}

	void sort()
	{
		if(head==NULL||head->next==NULL)
			return ;
		for(Node *p1=head;p1->next!=NULL;p1=p1->next)
		{
			Node *p_min=p1;
			for(Node *p2=p1->next;p2!=NULL;p2=p2->next)
			{
				if(p2->content<p_min->content)
					p_min=p2;
				if(p_min!=p1)
				{
					T temp=p1->content;
					p1->content=p_min->content;
					p_min->content=temp;
				}
			}
		}
	}
	void print()
	{
		for(Node *p=head;p!=NULL;p=p->next)
			cout<<p->content<<" ";
		cout<<endl;
	}
	void delete_element(int i)
	{

		if(i==1)
		{
			Node *p=head;
			head=head->next;
			delete p;
		}
		else
		{
			Node *p=head;
			for(int temp=1;temp<i-1;temp++)
			{
				if(p->next==NULL) break;
				p=p->next;
			}
			if(p->next!=NULL)
			{
				Node *q=p->next;
				p->next=q->next;
				delete q;
			}
			else
				cout<<"cannot find !"<<endl;
		}
	}

	void insert_element(int i,T x)//在第i个位置后添加元素x
	{
		Node *q=head;
		Node *p=new Node;
		p->content=x;
		p->next=NULL;
		int temp;
		for(temp=1;temp<i;temp++)
		{
			if(q->next==NULL)
				break;
			q=q->next;
		}
		if(temp==i)
		{
			p->next=q->next;
			q->next=p;
		}
		else
			cout<<"error"<<endl;
	}
};

template<class T>
class Node
{
	T content;
	Node<T> *next;
public:
	Node()
	{
		next=NULL;
	}
	Node(const T & data)
	{
		content=data;
		next=NULL;
	}
	


};



int main()
{
	//Node<int> *p1;
	List<int> list;
	cout<<"所有输出以井号结束"<<endl;
	list.input_element();
	list.print();
	list.insert_element(1,5);
	list.print();
	list.sort();
	list.print();
	system("pause");
	return 0;
}
