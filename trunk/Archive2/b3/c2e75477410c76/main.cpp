#include <iostream>
#include <string>
#include <vector>

#define MAX_NUM 100
#define  max(x, y) (((x) > (y)) ? (x) : (y))
#define ROOT_OFFSET 0//根节点偏移
#define NODE_NUM_OFFSET 4//节点数量偏移
#define DELFLAG 8//删除标志
#define DATA_BEG 12//数据存储位置

#define PARENT_BASE(x) (sizeof(x)) //父结点偏移基址
#define LEFT_BASE(x) (sizeof(x)+sizeof(int))//左孩子偏移基址
#define RIGHT_BASE(x) (sizeof(x)+sizeof(int)*2)//右孩子偏移基址
#define FLAG_BASE(x) (sizeof(x)+sizeof(int)*3)//标志位偏移基址
#define NEXT_BASE(x) (sizeof(x)+sizeof(int)*4)//链表偏移基址
#define ALL_SIZE(x) (sizeof(x)+sizeof(int)*5)//数据区大小




template<typename T>
//数组
class CMyArray
{
public:
    CMyArray()
	{
		m_pData = NULL;
		m_nSize = 0;
		m_nLength = 0;
	}
	CMyArray(int nSize)
	{
		AllocForSize(nSize);
		m_nLength = nSize;
	}
	virtual ~CMyArray()
	{
		Clear();
	}
	inline int Length() const
	{
		return m_nLength;
	}
	void Clear()
	{
		if (m_pData != NULL)
		{
			delete[] m_pData;
			m_pData = NULL;
		}
		m_nLength = 0;
		m_nSize = 0;
	}
	bool Empty() const
	{
		return m_nLength == 0;
	}
	T GetElem(int nIndex)
	{
		return m_pData[nIndex];
	}
	T PriorElem(int nIndex)
	{
		return m_pData[nIndex - 1];
	}
	T AfterElem(int nIndex)
	{
		return m_pData[nIndex + 1];
	}
	void InsertElem(int nIndex, const T& Elem)
	{
		if (m_pData == NULL)
		{
			AllocForSize(2);
		}

		//检查空间
		if (m_nLength >= m_nSize)
		{
			//空间不够
			ReAlloc(m_nSize * 2);
		}

		//[1] 2 [3] 4 [5]

		//数据往后移动
		for (int i = m_nLength - 1; i >= nIndex; i--)
		{
			m_pData[i + 1] = m_pData[i];
		}

		m_pData[nIndex] = Elem;
		m_nLength++;
	}
	void AddTail(const T& Elem)
	{
		if (m_pData == NULL)
		{
			AllocForSize(2);
		}

		//检查空间
		if (m_nLength >= m_nSize)
		{
			//空间不够
			ReAlloc(m_nSize * 2);
		}

		m_pData[m_nLength++] = Elem;
	}
	void DeleteElem(int nIndex)
	{
		//[1] 2 [3] 4 5 [6]

		//[1]
		for (int i = nIndex; i < m_nLength - 1; i++)
		{
			m_pData[i] = m_pData[i + 1];
		}
		m_nLength--;
	}
	T& operator[] (int nIndex)
	{
		return m_pData[nIndex];
	}
private:
	void AllocForSize(int nSize)
	{
		m_pData = new T[nSize];
		m_nSize = nSize;
	}
	void ReAlloc(int nSize)
	{
		m_nSize = nSize;
		T *pNew = new T[m_nSize];
		//memmove(pNew, m_pData, m_nLength * sizeof(int));

		for (int i = 0; i < m_nLength; i++)
		{
			pNew[i] = m_pData[i];
		}
		delete[] m_pData;
		m_pData = pNew;
	}
private:
	T    *m_pData;
	int  m_nLength;  //表长
	int  m_nSize;    //空间大小
};

//链表
template<typename T>
class CMyList
{
private:
	template<typename T>
	class CMyNode
	{
	public:
		CMyNode(const T& Elem)
		{
			m_Elem = Elem;
			m_pPrev = NULL;
			m_pNext = NULL;
		}
		T   m_Elem;
		CMyNode *m_pPrev;//前驱
		CMyNode *m_pNext;//后继
	};

public:
	class iterator//迭代器
	{
	public:
		friend class CMyList<T>;
		iterator(CMyNode<T> *pNode = NULL)
		{
			m_pNode = pNode;
		}
		//重载运算符
		bool operator!= (iterator& obj)
		{
			return m_pNode != obj.m_pNode;
		}
		iterator operator++ ()
		{
			return  m_pNode = m_pNode->m_pNext;
		}
		iterator operator++ (int)
		{
			CMyNode<T> *p = m_pNode;
			m_pNode = m_pNode->m_pNext;
			return p;
		}
		T& operator* ()
		{
			return m_pNode->m_Elem;
		}
	private:
		CMyNode<T> *m_pNode;
	};
public:
	CMyList()//默认构造
	{
		m_pHead = m_pTail = NULL;
		m_nCount = 0;
	}
	virtual ~CMyList()
	{
		RemoveAll();
	}
public:
	int  Length() const;  //表长
	void RemoveAll();     //清空链表
	bool Empty() const;   //是否为空
	iterator push_back(const T& Elem) //加到尾结点

	{
		CMyNode<T> *pNewNode = new CMyNode<T>(Elem);
		if (pNewNode == NULL)//未申请到空间
		{
			return NULL;
		}

		//空表
		if (Empty())
		{
			m_pHead = m_pTail = pNewNode;
			m_nCount++;
		}
		else
		{

			m_pTail->m_pNext = pNewNode;//链表尾部下一个节点挂钩新节点
			pNewNode->m_pPrev = m_pTail;//新节点头部挂钩链表尾结点

			m_pTail = pNewNode;//设置新的尾结点
			m_nCount++;//计数器自加操作
		}

		return pNewNode;
	}
	iterator push_front(const T& Elem) //加头尾结点
		//表头插入
	{
		CMyNode<T> *pNewNode = new CMyNode<T>(Elem);
		if (pNewNode == NULL)
		{
			return NULL;
		}

		//空表
		if (Empty())
		{
			m_pHead = m_pTail = pNewNode;
			m_nCount++;
		}
		else
		{
			pNewNode->m_pNext = m_pHead;//新节点后继挂入表头
			m_pHead->m_pPrev = pNewNode;//表头前驱挂入新节点

			m_pHead = pNewNode;//新节点给表头
			m_nCount++;//计数器自加
		}

		return pNewNode;//返回新节点
	}


	iterator InsertAfter(iterator pos, const T& Elem) //在指定位置之后插入
		//指定节点之后插入
	{
		CMyNode<T> *pNewNode = new CMyNode<T>(Elem);
		if (pNewNode == NULL)
		{
			return NULL;
		}

		//查找插入的结点
		CMyNode<T> *pFindNode = pos.m_pNode;
		if (pFindNode == NULL)
		{
			return NULL;
		}

		//空表
		if (Empty())
		{
			m_pHead = m_pTail = pNewNode;
		}
		else
		{
			//定义临时后继数据，因为涉及到新的挂钩所以定义中间变量临时保存数据
			CMyNode<T> *pNext = pFindNode->m_pNext;
			pFindNode->m_pNext = pNewNode;//需要插入位置的后继为新节点

			if (pNext != NULL)//如果插入位置后继不为空（非尾节点），则原节点前驱挂为需插入的值
				pNext->m_pPrev = pNewNode;
			else//否则则置为尾部
				m_pTail = pNewNode;

			pNewNode->m_pPrev = pFindNode;//新节点前驱设置为原节点
			pNewNode->m_pNext = pNext;//新节点后继设置为零时对象中节点
		}
		m_nCount++;

		return pNewNode;
	}
	iterator InsertBefore(iterator pos, const T& Elem)//在指定位置之前插入
		//指定位置之后插入
	{
		CMyNode<T> *pNewNode = new CMyNode<T>(Elem);
		if (pNewNode == NULL)
		{
			return NULL;
		}

		//查找插入的结点
		CMyNode<T> *pFindNode = pos.m_pNode;
		if (pFindNode == NULL)
		{
			return NULL;
		}

		//空表
		if (Empty())
		{
			m_pHead = m_pTail = pNewNode;
		}
		else
		{

			CMyNode<T> *pPrev = pFindNode->m_pPrev;//保存原节点前驱值

			if (pPrev != NULL)//前驱不为空（不为头结点）
				pPrev->m_pNext = pNewNode;//前驱的后继设置插入新节点
			else
				m_pHead = pNewNode;//头部插入，设置为头部

			pFindNode->m_pPrev = pNewNode;//插入位置节点前驱设置为新节点
			pNewNode->m_pPrev = pPrev;//新节点前驱设置为原来节点前驱
			pNewNode->m_pNext = pFindNode;//新节点后继设置为插入位置节点
		}
		m_nCount++;

		return pNewNode;
	}
	T pop_back();//弹栈
	T pop_front();
	void RemoveAt(iterator pos);
	iterator Find(const T& Elem)
	{
		CMyNode<T> *pCurNode = m_pHead;
		while (pCurNode != NULL)
		{
			if (pCurNode->m_Elem == Elem)
			{
				return pCurNode;
			}
			pCurNode = pCurNode->m_pNext;
		}

		return NULL;
	}
	T GetAt(iterator pos);
	void SetAt(iterator pos, const T& Elem);

	iterator GetHead() const//获取表头
	{
		return m_pHead;
	}
	iterator GetTail() const//获取表尾
	{
		return m_pTail;
	}

	iterator begin()
	{
		return m_pHead;
	}
	iterator end()
	{
		return NULL;
	}
private:
	CMyNode<T> *m_pHead;  //头结点
	CMyNode<T> *m_pTail;  //尾结点
	int      m_nCount; //表长
};

template<typename T>
inline int CMyList<T>::Length() const
{
	return m_nCount;
}

template<typename T>
void CMyList<T>::RemoveAll()//清空链表
{
	CMyNode<T> *pCurNode = m_pHead;//保存链表头
	while (pCurNode != NULL)
	{
		CMyNode<T> *pNext = pCurNode->m_pNext;
		delete pCurNode;//释放当前位置
		pCurNode = pNext;//将下一个位置给现在
	}

	m_pHead = m_pTail = NULL;//node指针清空
	m_nCount = 0;//计数器归零
}

template<typename T>
inline bool CMyList<T>::Empty() const
{
	return m_nCount == 0;
}

//template<typename T>
//CMyList<T>::iterator CMyList<T>::push_front(const T& Elem)

//template<typename T>
//CMyList<T>::iterator CMyList<T>::push_back(const T& Elem)

//template<typename T>
//CMyList<T>::iterator CMyList<T>::InsertAfter(iterator pos, const T& Elem)

//template<typename T>
//CMyList<T>::iterator CMyList<T>::InsertBefore(iterator pos, const T& Elem)

template<typename T>
T CMyList<T>::pop_back()
{
	T Elem = m_pTail->m_Elem;//使用临时变量取尾结点的值
	RemoveAt(m_pTail);//使用删除释放尾节点
	return Elem;
}

template<typename T>
T CMyList<T>::pop_front()
{
	T Elem = m_pHead->m_Elem;//使用临时变量取头结点的值
	RemoveAt(m_pHead);//使用删除释放头节点
	return Elem;
}

template<typename T>
void CMyList<T>::RemoveAt(iterator pos)
{
	if (pos.m_pNode == NULL)//需要指定删除位置为空则直接返回
		return;

	CMyNode<T> *pDelNode = pos.m_pNode;//需要删除的节点
	CMyNode<T> *pPrev = pDelNode->m_pPrev;//需要删除节点的前驱
	CMyNode<T> *pNext = pDelNode->m_pNext;//需要删除节点的后继

	if (pPrev != NULL)//前驱不为空（不为头结点）
		pPrev->m_pNext = pNext;//前节点后继为需要删除位置下一节点
	else
		m_pHead = pNext;//需要删除节点直接为头结点

	if (pNext != NULL)
		pNext->m_pPrev = pPrev;
	else
		m_pTail = pPrev;

	delete pDelNode;//脱钩完成后直接删除
	m_nCount--;
}


//返回NULL表示没有找到
//template<typename T>
//CMyList<T>::iterator CMyList<T>::Find(const T& Elem)

template<typename T>
T CMyList<T>::GetAt(iterator pos)
{
	return pos.m_pNode->m_Elem;
}

template<typename T>
void CMyList<T>::SetAt(iterator pos, const T& Elem)
{
	pos.m_pNode->m_Elem = Elem;
}




template<typename T>
class CMyStack :private CMyList<T>
{
public:
	void push(const T& Elem)
	{
		push_front(Elem);
	}
public:
	CMyList<T>::push_back;
	CMyList<T>::pop_back;
	CMyList<T>::Empty;
	CMyList<T>::Length;
};

template<typename T>
class CMyQueue :private CMyList<T>
{

public:
	CMyList<T>::push_back;
	CMyList<T>::pop_front;
	CMyList<T>::Empty;
	CMyList<T>::Length;
};


template<typename T>
struct  tagFileSt//读文件
{
	T m_Data;					//数据
	int m_nParentOffset;         //文件中父亲偏移
	int m_nLeftOffset;           //文件中左孩子偏移
	int m_nRightOffset;          //文件中有孩子偏移
	int m_nFLAG;				 //标志偏移
	int m_nNextOffset;            //链表后继的偏移 
};

template<typename T>
struct CTreeNode
{
	CTreeNode(T Elem)
	:m_Elem(Elem),
	m_pLeft(NULL), m_pRight(NULL), m_pParent(NULL),
	m_nSubHeight(0), m_pNextNode(NULL), m_nParentOffset(-1),
	m_nLeftOffset(-1), m_nRightOffset(-1), m_nFLAG(1), m_nCurFileOffset(8),
	m_nNextOffset(-1)
	{
	}

	T m_Elem;//存入数据
	int m_nParentOffset;        //文件中父亲偏移
	int m_nLeftOffset;          //文件中左孩子偏移
	int m_nRightOffset;         //文件中有孩子偏移
	int m_nFLAG;				//标志位偏移
	int m_nNextOffset;          //链表后继的偏移
	int m_nCurFileOffset;       //自己的偏移



	int m_nSubHeight;//高度差
	CTreeNode *m_pLeft;//左孩子
	CTreeNode *m_pRight;//右孩子
	CTreeNode *m_pParent;//父节点
	CTreeNode *m_pNextNode;//链表结点 


};


template<typename T>
class CMyTree
{
public:
	CMyTree()
	{
		m_pRoot = NULL;
		m_nCount = 0;
	}
	virtual ~CMyTree()
	{
		m_pRoot = NULL;
		m_nCount = 0;
	}

	//写标志信息
	void WriteFileFlag(int DelFlag = 0)
	{
		out.open("data.txt", ios::binary | ios::app);//没有文件创造文件
		out.close();

		out.open("data.txt", ios::binary | ios_base::in | ios_base::out);
		out.seekp(ROOT_OFFSET, ios::beg);//移动偏移到结点偏移位置
		out.write((char*)&m_pRoot->m_nCurFileOffset, sizeof(m_pRoot->m_nCurFileOffset));//写入根节点信息

		out.seekp(NODE_NUM_OFFSET, ios::beg);//移动偏移到数据偏移区
		out.write((char*)&m_nCount, sizeof(m_nCount));  //写入个数


		out.seekp(DELFLAG, ios::beg);
		out.write((char*)&g_nDelFlag, sizeof(g_nDelFlag));


		out.close();
	}
	//写结点信息
	void WriteFile(CTreeNode<T>* pNode)
	{
		if (pNode->m_pParent != NULL)//判断父节点情况来决定是否更新父节点
		{
			pNode->m_nParentOffset = pNode->m_pParent->m_nCurFileOffset;
		}
		//判断标志位是否可写入
		int nIndex = 0;//数组下标

		in.open("data.txt", ios::binary);
		in.seekg(DELFLAG, ios::beg);
		in.read((char*)&g_nDelFlag, sizeof(g_nDelFlag));
		in.close();

		if (g_nDelFlag >0)//存在空闲位置
		{
			in.open("data.txt", ios::binary);
			in.seekg(0, ios::end);
			int nFileSize = in.tellg();//文件尺寸
			in.seekg(DATA_BEG, ios::beg);
			in.read((char*)&g_Data, nFileSize - DATA_BEG);//取出所有数据放入结构体数组中
			in.close();

			while (nIndex<MAX_NUM)//循环寻找空位置插入（注意上模版）
			{
				if (g_Data[nIndex].m_nFLAG == 0)
				{
					out.open("data.txt", ios::binary | ios_base::in | ios_base::out);
					out.seekp(DATA_BEG + nIndex*ALL_SIZE(T), ios::beg);//定位区块数据(模版数据)
					out.write((char*)&pNode->m_Elem, ALL_SIZE(T)); //写数据层（模版数据）

					break;
				}
				nIndex++;
			}
			if (nIndex == MAX_NUM)//找不到空位
			{
				out.open("data.txt", ios::binary | ios::app);
				out.write((char*)&pNode->m_Elem, ALL_SIZE(T)); //写数据层、

			}

		}
		else
		{
			out.open("data.txt", ios::binary | ios::app);
			out.write((char*)&pNode->m_Elem, ALL_SIZE(T)); //写数据层

		}

		int nOffset = out.tellp();//获取偏移值
		pNode->m_nCurFileOffset = nOffset - ALL_SIZE(T);//计算父节点偏移
		out.close();

		if (pNode->m_nParentOffset != -1)//更新父节点左右孩子偏移
		{
			out.open("data.txt", ios::binary | ios_base::in | ios_base::out);
			if (pNode == pNode->m_pParent->m_pLeft)//判断左右孩子
			{
				out.seekp(pNode->m_nParentOffset + LEFT_BASE(T), ios::beg);
			}
			else
			{
				out.seekp(pNode->m_nParentOffset + RIGHT_BASE(T), ios::beg);
			}
			out.write((char*)&pNode->m_nCurFileOffset, sizeof(pNode->m_nCurFileOffset));
			out.close();
		}
	}

	//遍历
	//前序遍历
	void BeforOrder(CTreeNode<T>*pRoot)
	{
		if (pRoot == NULL)
		{
			return;
		}

		printf("%C ", pRoot->m_Elem);
		BeforOrder(pRoot->m_pLeft);
		BeforOrder(pRoot->m_pRight);
	}
	//非递归前序遍历
	void _BeforOrder(CTreeNode<T>*pCurNode)
	{
		CMyStack<CTreeNode*> stack;
		CTreeNode* pPopNode = NULL;

		while (true)
		{
			while (pCurNode != NULL)
			{
				printf("%C ", pCurNode->m_Elem);
				stack.push_back(pCurNode);
				pCurNode = pCurNode->m_pLeft;
			}

			if (stack.Empty())
			{
				break;
			}

			pPopNode = stack.pop_back();
			pCurNode = pPopNode->m_pRight;
		}
	}
	//非递归中序遍历
	void _MidOrder(CTreeNode<T>*pCurNode)
	{
		CMyStack<CTreeNode*> stack;
		CTreeNode* pPopNode = NULL;

		while (true)
		{
			while (pCurNode != NULL)
			{
				stack.push_back(pCurNode);
				pCurNode = pCurNode->m_pLeft;
			}

			if (stack.Empty())
			{
				break;
			}

			pPopNode = stack.pop_back();
			printf("%d ", pPopNode->m_Elem);
			pCurNode = pPopNode->m_pRight;
		}
	}
	//非递归后遍历
	void _AfterOrder(CTreeNode<T>*pCurNode)
	{
		//E F B G D C A
		CMyStack<CTreeNode*> stack;
		CTreeNode* pPopNode = NULL;
		CTreeNode *pLastNode = NULL;

		while (true)
		{
			while (pCurNode != NULL)
			{
				stack.push_back(pCurNode);
				pCurNode = pCurNode->m_pLeft;
			}

			if (stack.Empty())
			{
				break;
			}

			pPopNode = stack.pop_back();

			if (pPopNode->m_pRight == NULL ||
				pPopNode->m_pRight == pLastNode)
			{
				pLastNode = pPopNode;
				printf("%C ", pPopNode->m_Elem);
				continue;
			}
			else
			{
				stack.push_back(pPopNode);
			}

			pCurNode = pPopNode->m_pRight;
		}
	}
	//中序遍历
	void MidOrder(CTreeNode<T>*pRoot)
	{
		if (pRoot == NULL)
		{
			return;
		}

		MidOrder(pRoot->m_pLeft);
		printf("%C ", pRoot->m_Elem);
		MidOrder(pRoot->m_pRight);
	}
	//后遍历
	void AfterOrder(CTreeNode<T>* pRoot)
	{
		if (pRoot == NULL)
		{
			return;
		}

		AfterOrder(pRoot->m_pLeft);
		AfterOrder(pRoot->m_pRight);
		printf("%C ", pRoot->m_Elem);
	}
	//层序遍历
	void LayerOrder(CTreeNode<T>* pCurNode)
	{
		CMyQueue<CTreeNode*> queue;

		while (pCurNode != NULL)
		{
			printf("%d[%d] ", pCurNode->m_Elem, pCurNode->m_nSubHeight);
			if (pCurNode->m_pLeft != NULL)
				queue.push_back(pCurNode->m_pLeft);
			if (pCurNode->m_pRight != NULL)
				queue.push_back(pCurNode->m_pRight);

			if (queue.Empty())
			{
				break;
			}
			pCurNode = queue.pop_front();
		}
	}
	static void LayerReadFile(CMyTree& tree)   //层序遍历
	{
		CMyQueue<int> queue;

		in.open("data.txt", ios::binary);
		in.seekg(0, ios::end);
		int nFileSize = in.tellg();
		in.seekg(ios::beg);
		in.seekg(DATA_BEG, ios::beg);
		in.read((char*)&g_Data, nFileSize - DATA_BEG);
		in.close();

		//读根结点偏移
		int nRootOffset = 0;
		in.open("data.txt", ios::binary);
		in.seekg(0, ios::beg);
		in.read((char*)&nRootOffset, sizeof(nRootOffset));
		in.close();


		//插入根结点
		int Data = g_Data[(nRootOffset - DATA_BEG) / sizeof(tagFileSt<T>)].m_Data;
		printf("%d ", Data);
		tree.RecoverTree(Data);

		while (true)
		{
			int pLeftOffset = g_Data[(nRootOffset - DATA_BEG) / sizeof(tagFileSt<T>)].m_nLeftOffset;
			if (pLeftOffset != -1)  //左边入队列
			{
				queue.push_back(pLeftOffset);

				Data = g_Data[(pLeftOffset - DATA_BEG) / sizeof(tagFileSt<T>)].m_Data;;
				tree.RecoverTree(Data);
			}


			int pRightOffset = g_Data[(nRootOffset - DATA_BEG) / sizeof(tagFileSt<T>)].m_nRightOffset;
			if (pRightOffset != -1) //右边入队列
			{
				queue.push_back(pRightOffset);

				Data = g_Data[(pRightOffset - DATA_BEG) / sizeof(tagFileSt<T>)].m_Data;;
				tree.RecoverTree(Data);
			}

			if (queue.Empty())
			{
				return;
			}
			nRootOffset = queue.pop_front(); //出队列
		}
	}




	//获取根节点
	CTreeNode<T>* GetRoot() const
	{
		return m_pRoot;
	}
	//获取高度
	int GetCount() const
	{
		return m_nCount;
	}
	//获取结点数量
	int GetNodeNum() const
	{
		return m_nCount;
	}


	//增加结点
	bool InsertElem(const T& Elem)
	{
		CTreeNode<T>* pNewNode = new CTreeNode<T>(Elem);
		CTreeNode<T>* pTmp = NULL; //当前结点缓冲
		CTreeNode<T>* pFindNode = m_pRoot;

		if (pNewNode == NULL)//检查
			return false;


		if (m_pRoot == NULL)//空树
		{
			m_pRoot = pNewNode;
			m_nCount++;
			if (g_nDelFlag > 0)
			{
				g_nDelFlag--;
			}
			WriteFileFlag();  //写根结点信息和结点数量信
			WriteFile(pNewNode);
			return true;
		}
		else
		{
			//查找插入的位置
			while (true)
			{
				//放在右边
				if (Elem > pFindNode->m_Elem)
				{
					if (pFindNode->m_pRight == NULL)
					{
						pFindNode->m_pRight = pNewNode;
						break;
					}
					pFindNode = pFindNode->m_pRight;
				}
				//放在左边
				else if (Elem < pFindNode->m_Elem)
				{
					if (pFindNode->m_pLeft == NULL)
					{
						pFindNode->m_pLeft = pNewNode;
						break;
					}
					pFindNode = pFindNode->m_pLeft;
				}
				//相等放入链表
				else
				{
					while (pFindNode->m_pNextNode != NULL)//搜寻空位置
					{
						pFindNode = pFindNode->m_pNextNode;
					}
					pFindNode->m_pNextNode = pNewNode;//新节点放入该位置
					out.open("data.txt", ios::app | ios::binary);
					//写入pnew以及pnew的偏移
					out.write((char*)&pNewNode->m_Elem, ALL_SIZE(T));//在最后写入
					int nOffset = out.tellp();//或许当前文件指针位置()
					pNewNode->m_nCurFileOffset = nOffset - ALL_SIZE(T);//获取自身偏移
					out.close();

					//修改pnew的前驱偏移
					out.open("data.txt", ios::binary | ios_base::in | ios_base::out);
					out.seekp(pFindNode->m_nCurFileOffset + NEXT_BASE(T), ios::beg);
					out.write((char*)&pNewNode->m_nCurFileOffset, sizeof(pNewNode->m_nCurFileOffset));
					out.close();

					return 1;
				}
			}
		}

		pNewNode->m_pParent = pFindNode;
		m_nCount++;


		WriteFile(pNewNode); //写结点信息

		AdjuestSubHeight(pNewNode);//调整高度差


		//旋转
		Rotatel(pNewNode);
		if (g_nDelFlag > 0)
		{
			g_nDelFlag--;
		}
		WriteFileFlag();//写入根节点信息
		return true;
	}

	//查找结点
	CTreeNode<T>* FindItem(const T& Elem)
	{
		CTreeNode<T>* pCurNode = m_pRoot;

		//查找插入的位置
		while (pCurNode != NULL)
		{
			//在右边
			if (Elem > pCurNode->m_Elem)
			{
				pCurNode = pCurNode->m_pRight;
			}
			//在左边
			else if (Elem < pCurNode->m_Elem)
			{
				pCurNode = pCurNode->m_pLeft;
			}
			//相等返回结点
			else
			{
				return pCurNode;
			}
		}

		return NULL;
	}

	//修改节点
	bool ModifyElem(T& Elem1, T& Elem2)
	{
		if (m_nCount == 0) //空树
		{
			return false;
		}
		RemoveElem(Elem2);
		InsertElem(Elem1);
		return true;
	}

	bool RemoveElem(const T& Elem)
	{
		//查找删除结点
		CTreeNode<T>* pDelNode = FindItem(Elem);
		if (pDelNode == NULL)
		{
			return false;
		}


		return RemoveNode(pDelNode);
	}

	bool RemoveNode(CTreeNode<T>* pDelNode)
	{

		/*
		30
		[11]       55
		4      18         70
		1    8  15   19   58
		6


		1
		1      3
		1.叶子结点
		2.有一个孩子
		3.有两个孩子
		*/


		int nEof = -1;
		int nDelFlag = 0;



		// 1.叶子
		if (pDelNode->m_pLeft == NULL &&
			pDelNode->m_pRight == NULL)
		{
			CTreeNode<T>* pParent = pDelNode->m_pParent;

			//调整高度差
			AdjuestSubHeight(pDelNode, -1);

			if (pParent == NULL)
			{
				//删除结点置标志
				out.open("data.txt", ios::binary | ios_base::in | ios_base::out);
				out.seekp(pDelNode->m_nCurFileOffset + FLAG_BASE(T), ios::beg);
				out.write((char*)&(nDelFlag), sizeof(nDelFlag));
				out.close();
				m_pRoot = NULL;

			}
			else if (pDelNode == pParent->m_pLeft)
			{
				//删除结点置标志
				out.open("data.txt", ios::binary | ios_base::in | ios_base::out);


				out.seekp(pDelNode->m_nCurFileOffset + FLAG_BASE(T), ios::beg);
				out.write((char*)&(nDelFlag), sizeof(nDelFlag));




				pParent->m_pLeft = NULL;




				//删除结点的父亲的左孩子做调整
				out.seekp(pDelNode->m_pParent->m_nCurFileOffset + LEFT_BASE(T), ios::beg);
				out.write((char*)&(nEof), sizeof(nEof));
				out.close();



			}
			else
			{
				//删除结点置标志
				out.open("data.txt", ios::binary | ios_base::in | ios_base::out);

				out.seekp(pDelNode->m_nCurFileOffset + FLAG_BASE(T), ios::beg);
				out.write((char*)&(nDelFlag), sizeof(nDelFlag));

				pParent->m_pRight = NULL;

				//删除结点的父亲的右孩子做调整
				out.seekp(pDelNode->m_pParent->m_nCurFileOffset + RIGHT_BASE(T), ios::beg);
				out.write((char*)&(nEof), sizeof(nEof));
				out.close();

			}

			Rotatel(pDelNode);

			if (pDelNode->m_pNextNode == NULL)
			{
				//删除结点置标志
				out.open("data.txt", ios::binary | ios_base::in | ios_base::out);
				out.seekp(pDelNode->m_nCurFileOffset + FLAG_BASE(T), ios::beg);
				out.write((char*)&(nDelFlag), sizeof(nDelFlag));
				out.close();
				delete pDelNode;
			}
			else
			{
				CTreeNode<T>* pTmp = NULL;
				while (pDelNode != NULL)
				{
					pTmp = pDelNode->m_pNextNode;
					//删除结点置标志
					out.open("data.txt", ios::binary | ios_base::in | ios_base::out);
					out.seekp(pDelNode->m_nCurFileOffset + FLAG_BASE(T), ios::beg);
					out.write((char*)&(nDelFlag), sizeof(nDelFlag));
					out.close();
					delete pDelNode;
					pDelNode = pTmp;
				}
			}

			pDelNode = NULL;
			m_nCount--;
			g_nDelFlag++;
		}
		//两个孩子
		else if (pDelNode->m_pLeft != NULL &&
			pDelNode->m_pRight != NULL)
		{
			//左边找最大的结点
			CTreeNode<T>* pWapNode = pDelNode->m_pLeft;
			while (pWapNode->m_pRight != NULL)
				pWapNode = pWapNode->m_pRight;

			//交换
			pDelNode->m_Elem = pWapNode->m_Elem;

			//调整文件中的数据
			out.open("data.txt", ios::binary | ios_base::in | ios_base::out);
			out.seekp(pDelNode->m_nCurFileOffset, ios::beg);
			out.write((char*)&(pWapNode->m_Elem), sizeof(pWapNode->m_Elem));
			out.close();

			return RemoveNode(pWapNode);
		}
		//一个孩子
		else
		{
			CTreeNode<T>* pParent = pDelNode->m_pParent;
			CTreeNode<T>* pChild = NULL;

			//调整高度差
			AdjuestSubHeight(pDelNode, -1);

			if (pDelNode->m_pLeft != NULL)
			{
				pChild = pDelNode->m_pLeft;
			}
			else
			{
				pChild = pDelNode->m_pRight;
			}


			if (pParent == NULL)
			{
				m_pRoot = pChild;
			}
			else if (pDelNode == pParent->m_pLeft)
			{
				pParent->m_pLeft = pChild;
				//调整父节点的左孩子偏移
				out.open("data.txt", ios::binary | ios_base::in | ios_base::out);
				out.seekp(pParent->m_nCurFileOffset + LEFT_BASE(T), ios::beg);
				out.write((char*)&(pChild->m_nCurFileOffset), sizeof(pChild->m_nCurFileOffset));
				out.close();
			}
			else
			{
				pParent->m_pRight = pChild;
				//调整父节点的右孩子偏移
				out.open("data.txt", ios::binary | ios_base::in | ios_base::out);
				out.seekp(pParent->m_nCurFileOffset + RIGHT_BASE(T), ios::beg);
				out.write((char*)&(pChild->m_nCurFileOffset), sizeof(pChild->m_nCurFileOffset));
				out.close();
			}

			pChild->m_pParent = pParent;
			//调整孩子的父节点偏移
			out.open("data.txt", ios::binary | ios_base::in | ios_base::out);
			out.seekp(pChild->m_nCurFileOffset + PARENT_BASE(T), ios::beg);

			if (pParent == NULL)
			{
				out.write((char*)&(nEof), sizeof(nEof));
			}
			else
			{
				out.write((char*)&(pParent->m_nCurFileOffset), sizeof(pParent->m_nCurFileOffset));
			}

			//删除结点置标志
			out.seekp(pDelNode->m_nCurFileOffset + FLAG_BASE(T), ios::beg);
			out.write((char*)&(nDelFlag), sizeof(nDelFlag));
			out.close();



			Rotatel(pDelNode);

			if (pDelNode->m_pNextNode == NULL)
			{
				//删除结点置标志
				out.open("data.txt", ios::binary | ios_base::in | ios_base::out);
				out.seekp(pDelNode->m_nCurFileOffset + FLAG_BASE(T), ios::beg);
				out.write((char*)&(nDelFlag), sizeof(nDelFlag));
				delete pDelNode;
			}
			else
			{
				CTreeNode<T>* pTmp = NULL;
				while (pDelNode != NULL)
				{
					pTmp = pDelNode->m_pNextNode;
					//删除结点置标志
					out.open("data.txt", ios::binary | ios_base::in | ios_base::out);
					out.seekp(pDelNode->m_nCurFileOffset + FLAG_BASE(T), ios::beg);
					out.write((char*)&(nDelFlag), sizeof(nDelFlag));
					out.close();
					delete pDelNode;
					pDelNode = pTmp;
				}
			}
			out.close();
			pDelNode = NULL;
			m_nCount--;
			g_nDelFlag++;
		}
		WriteFileFlag();
		return true;
	}

	void RecoverTree(T& Elem)
	{
		CTreeNode<T>* pNew = new CTreeNode<T>(Elem);
		CTreeNode<T>* pTmp = NULL;   //当前结点缓冲

		if (m_nCount == 0)  //空树
		{
			m_pRoot = pNew;
			m_nCount++;
			if (g_nDelFlag > 0)
			{
				g_nDelFlag--;
			}

			return;
		}

		if (m_nCount != 0) //不为空树
		{
			pTmp = m_pRoot;
			while (true)
			{
				if (pTmp->m_Elem < Elem)  //插到右边
				{
					if (pTmp->m_pRight == NULL)  //找到了
					{
						pTmp->m_pRight = pNew;
						break;
					}
					pTmp = pTmp->m_pRight;
				}
				else if (pTmp->m_Elem > Elem) //插到左边
				{
					if (pTmp->m_pLeft == NULL)  //找到了
					{
						pTmp->m_pLeft = pNew;
						break;
					}
					pTmp = pTmp->m_pLeft;
				}
				else  //相等转化成链表 暂时不处理
				{
					while (pTmp->m_pNextNode != NULL)
					{
						pTmp = pTmp->m_pNextNode;
					}
					pTmp->m_pNextNode = pNew;
					return;
				}
			}
		}

		pNew->m_pParent = pTmp;
		m_nCount++;  //插入成功，调整结点数量
		if (g_nDelFlag > 0)
		{
			g_nDelFlag--;
		}

		AdjuestSubHeight(pNew, 1);
		Rotatel(pNew);

	}

	//旋转
	void Rotatel(CTreeNode<T>* pNewNode)
	{
		CTreeNode<T>* pParent = pNewNode->m_pParent;
		CTreeNode<T>* pK1 = NULL;
		CTreeNode<T>* pK2 = NULL;
		CTreeNode<T>* pK3 = NULL;

		while (pParent != NULL)
		{
			/*
			pK1[3]
			pK2[2]
			pK3[1]
			*/

			//需要旋转
			if (abs(pParent->m_nSubHeight) >= 2)
			{
				pK1 = pParent;

				//左边重
				if (pK1->m_nSubHeight > 0)
				{
					pK2 = pK1->m_pLeft;
				}
				//右边重
				else
				{
					pK2 = pK1->m_pRight;
				}

				//左边重
				if (pK2->m_nSubHeight > 0)
				{
					pK3 = pK2->m_pLeft;
				}
				//右边重
				else
				{
					pK3 = pK2->m_pRight;
				}


				//右单旋转
				if (pK2 == pK1->m_pLeft && pK3 == pK2->m_pLeft)
				{
					//printf("RightRotatel\n");
					RightRotatel(pK1, pK2);
				}
				//左单旋转
				else if (pK2 == pK1->m_pRight && pK3 == pK2->m_pRight)
				{
					//printf("LeftRotatel\n");
					LeftRotatel(pK1, pK2);
				}
				//左双旋转
				else if (pK2 == pK1->m_pLeft && pK3 == pK2->m_pRight)
				{
					/*
					K1        K1       K3
					K2         K3      K2    K1
					K3     K2
					*/
					//printf("LeftRotatel RightRotatel\n");
					LeftRotatel(pK2, pK3);
					RightRotatel(pK1, pK3);
				}
				//右双旋转
				else if (pK2 == pK1->m_pRight && pK3 == pK2->m_pLeft)
				{
					/*
					K1        K1            K3
					K2       K3      K1    K2
					K3            K2
					*/
					//printf("RightRotatel LeftRotatel\n");
					RightRotatel(pK2, pK3);
					LeftRotatel(pK1, pK3);
				}
			}

			pNewNode = pParent;
			pParent = pNewNode->m_pParent;
		}
	}

	void RightRotatel(CTreeNode<T>* pK1, CTreeNode<T>* pK2)
	{
		/*
		G               G
		K1               K2
		K2     C   ==>  A       K1
		A     B                  B     C
		*/
		CTreeNode<T>* pG = pK1->m_pParent;
		CTreeNode<T>* pA = pK2->m_pLeft;
		CTreeNode<T>* pB = pK2->m_pRight;
		CTreeNode<T>* pC = pK1->m_pRight;


		int nEof = -1;

		if (pB != NULL)
		{
			pB->m_pParent = pK1;

			out.open("data.txt", ios::binary | ios_base::in | ios_base::out);
			out.seekp(pB->m_nCurFileOffset + PARENT_BASE(T), ios::beg);
			out.write((char*)&pK1->m_nCurFileOffset, sizeof(pK1->m_nCurFileOffset));
			out.close();
		}


		if (pG != NULL)
		{
			if (pK1 == pG->m_pLeft)
			{
				pG->m_pLeft = pK2;

				out.open("data.txt", ios::binary | ios_base::in | ios_base::out);
				out.seekp(pG->m_nCurFileOffset + LEFT_BASE(T), ios::beg);
				out.write((char*)&pK2->m_nCurFileOffset, sizeof(pK2->m_nCurFileOffset));
				out.close();
			}
			else
			{
				pG->m_pRight = pK2;

				out.open("data.txt", ios::binary | ios_base::in | ios_base::out);
				out.seekp(pG->m_nCurFileOffset + RIGHT_BASE(T), ios::beg);
				out.write((char*)&pK2->m_nCurFileOffset, sizeof(pK2->m_nCurFileOffset));
				out.close();
			}
		}
		else
		{
			m_pRoot = pK2;

			out.open("data.txt", ios::binary | ios_base::in | ios_base::out);
			out.seekp(pK2->m_nCurFileOffset + PARENT_BASE(T), ios::beg);
			out.write((char*)&(nEof), sizeof(nEof));
			out.close();
		}

		pK1->m_pLeft = pB;
		pK1->m_pParent = pK2;

		pK2->m_pRight = pK1;
		pK2->m_pParent = pG;


		//处理pk2的右孩子偏移
		out.open("data.txt", ios::binary | ios_base::in | ios_base::out);
		out.seekp(pK2->m_nCurFileOffset + RIGHT_BASE(T), ios::beg);
		out.write((char*)&pK1->m_nCurFileOffset, sizeof(pK1->m_nCurFileOffset));


		//处理pk2的父节点偏移
		out.seekp(pK2->m_nCurFileOffset + PARENT_BASE(T), ios::beg);
		if (pG != NULL)
		{
			out.write((char*)&pG->m_nCurFileOffset, sizeof(pG->m_nCurFileOffset));
		}
		else
		{
			out.write((char*)&(nEof), sizeof(nEof));
		}

		//处理pk1的左孩子偏移
		out.seekp(pK1->m_nCurFileOffset + LEFT_BASE(T), ios::beg);
		if (pB != NULL)
		{
			out.write((char*)&pB->m_nCurFileOffset, sizeof(pB->m_nCurFileOffset));
		}
		else
		{
			out.write((char*)&(nEof), sizeof(nEof));
		}

		//处理pk1的父节点偏移
		out.seekp(pK1->m_nCurFileOffset + PARENT_BASE(T), ios::beg);
		out.write((char*)&pK2->m_nCurFileOffset, sizeof(pK2->m_nCurFileOffset));


		out.close();


		//调整右单旋转的高度差
		AdjustRightSubHeight(pK1, pK2);
	}

	void AdjustRightSubHeight(CTreeNode<T>* pK1, CTreeNode<T>* pK2)
	{
		/*
		G               G
		K1               K2
		K2     C   ==>  A       K1
		A     B                  B     C


		计算树高度的变化
		HeightChang = max(HA, max(HB, HC) + 1) -  max(HC, max(HA, HB) + 1)
		HeightChang = max(HA, HA - T2NEW) -  max(HC, T1 + HC)
		HeightChang = max(HA, HA - T2NEW) -  max(HC, T1 + HC)
		HeightChang = max(T2 + HB, T2 + HB - T2NEW) -  max(HB - T1NEW, T1 + HB - T1NEW)
		HeightChang = max(T2 + HB, T2 - T2NEW + HB) -  max(- T1NEW +  HB, T1 - T1NEW + HB)

		T1,T2为旋转前K1，K2高度差
		T1 = (max(HA, HB) + 1) - HC
		T2 = HA - HB

		T1NEW,T2NEW为旋转后的高度差
		T1NEW = HB - HC
		T2NEW = HA - (max(HB, HC) + 1)

		T1NEW = HB - HC
		T1NEW = (HA - T2) - ((max(HA, HB) + 1) - T1)
		T1NEW = ((T2 + HB) - T2) - ((max(T2 + HB, HB) + 1) - T1)
		T1NEW = T2 + HB - T2 - (max(T2 + HB, HB) + 1) + T1
		T1NEW = HB - (max(T2 + HB, HB) + 1) + T1
		T1NEW = HB - max(T2 + HB, HB) - 1 + T1
		if (T2 > 0)
		T1NEW = HB - (T2 + HB) - 1 + T1
		T1NEW = HB - T2 - HB - 1 + T1
		T1NEW = T1 - T2 - 1
		else (T2 <= 0)
		T1NEW = HB - HB - 1 + T1
		T1NEW = T1 - 1

		T2NEW = HA - (max(HB, HC) + 1)
		T2NEW = T2 + HB - (max(HB, HC) + 1)
		T2NEW = T2 + HB - (max(HB, HB - T1NEW) + 1)
		if (T1NEW > 0)
		T2NEW = T2 + HB - (max(HB, HB - T1NEW) + 1)
		T2NEW = T2 + HB - (HB + 1)
		T2NEW = T2 + HB - HB - 1
		T2NEW = T2 - 1
		else (T1NEW <= 0)
		T2NEW = T2 + HB - (max(HB, HB - T1NEW) + 1)
		T2NEW = T2 + HB - (HB - T1NEW + 1)
		T2NEW = T2 + HB - HB + T1NEW - 1
		T2NEW = T2 + T1NEW - 1

		*/
		int T1 = pK1->m_nSubHeight;
		int T2 = pK2->m_nSubHeight;
		int T1NEW = 0;
		int T2NEW = 0;
		if (T2 > 0)
			T1NEW = T1 - T2 - 1;
		else
			T1NEW = T1 - 1;

		if (T1NEW > 0)
			T2NEW = T2 - 1;
		else
			T2NEW = T2 + T1NEW - 1;

		pK1->m_nSubHeight = T1NEW;
		pK2->m_nSubHeight = T2NEW;


		//调整父结点的高度差
		int HB = 0;
		int nHeightChange = max(T2 + HB, T2 - T2NEW + HB) - max(-T1NEW + HB, T1 - T1NEW + HB);
		AdjuestSubHeight(pK2, nHeightChange);
	}

	//左单旋转
	void LeftRotatel(CTreeNode<T>* pK1, CTreeNode<T>* pK2)
	{
		/*
		G                         G
		K1                         K2
		A      K2     C   ==>    K1       C
		B    C            A    B
		*/
		CTreeNode<T>* pG = pK1->m_pParent;
		CTreeNode<T>* pA = pK1->m_pLeft;
		CTreeNode<T>* pB = pK2->m_pLeft;
		CTreeNode<T>* pC = pK2->m_pRight;

		//旋转怎么调整文件结点怎么调整

		int nEof = -1;//-1标志位


		if (pB != NULL)
		{
			pB->m_pParent = pK1;

			out.open("data.txt", ios::binary | ios_base::in | ios::out);
			out.seekp(pB->m_nCurFileOffset + PARENT_BASE(T), ios::beg);
			out.write((char*)&pK1->m_nCurFileOffset, sizeof(pK1->m_nCurFileOffset));
			out.close();
		}



		if (pG != NULL)
		{
			if (pK1 == pG->m_pLeft)
			{
				pG->m_pLeft = pK2;
				out.open("data.txt", ios::binary | ios_base::in | ios_base::out);
				out.seekp(pG->m_nCurFileOffset + LEFT_BASE(T), ios::beg);
				out.write((char*)&pK2->m_nCurFileOffset, sizeof(pK2->m_nCurFileOffset));
				out.close();
			}
			else
			{
				pG->m_pRight = pK2;
				out.open("data.txt", ios::binary | ios_base::in | ios_base::out);
				out.seekp(pG->m_nCurFileOffset + RIGHT_BASE(T), ios::beg);
				out.write((char*)&pK2->m_nCurFileOffset, sizeof(pK2->m_nCurFileOffset));
				out.close();
			}
		}
		else
		{
			m_pRoot = pK2;
			out.open("data.txt", ios::binary | ios_base::in | ios_base::out);
			out.seekp(pK2->m_nCurFileOffset + PARENT_BASE(T), ios::beg);
			out.write((char*)&(nEof), sizeof(nEof));
			out.close();
		}

		pK1->m_pRight = pB;
		pK1->m_pParent = pK2;

		pK2->m_pLeft = pK1;
		pK2->m_pParent = pG;

		//处理pk2的左孩子偏移
		out.open("data.txt", ios::binary | ios_base::in | ios_base::out);
		out.seekp(pK2->m_nCurFileOffset + LEFT_BASE(T), ios::beg);
		out.write((char*)&pK1->m_nCurFileOffset, sizeof(pK1->m_nCurFileOffset));
		out.close();


		//处理pk2的父节点偏移
		out.open("data.txt", ios::binary | ios_base::in | ios_base::out);
		out.seekp(pK2->m_nCurFileOffset + PARENT_BASE(T), ios::beg);
		if (pG != NULL)
		{
			out.write((char*)&pG->m_nCurFileOffset, sizeof(pG->m_nCurFileOffset));
			out.close();
		}
		else
		{
			out.write((char*)&(nEof), sizeof(nEof));
			out.close();
		}

		//处理pk1的右孩子偏移
		out.open("data.txt", ios::binary | ios_base::in | ios_base::out);
		out.seekp(pK1->m_nCurFileOffset + RIGHT_BASE(T), ios::beg);
		if (pB != NULL)
		{
			out.write((char*)&pB->m_nCurFileOffset, sizeof(pB->m_nCurFileOffset));
			out.close();
		}
		else
		{
			out.write((char*)&(nEof), sizeof(nEof));
			out.close();
		}

		//处理pk1的父节点偏移
		out.open("data.txt", ios::binary | ios_base::in | ios_base::out);
		out.seekp(pK1->m_nCurFileOffset + PARENT_BASE(T), ios::beg);
		out.write((char*)&pK2->m_nCurFileOffset, sizeof(pK2->m_nCurFileOffset));

		out.close();




		//调整右单旋转的高度差
		AdjustLeftSubHeight(pK1, pK2);
	}

	void AdjustLeftSubHeight(CTreeNode<T>* pK1, CTreeNode<T>* pK2)
	{
		/*
		G                      G
		K1                      K2
		A     K2      ==>    K1       C
		B    C         A    B

		计算树高度的变化
		HeightChang = max(HC, max(HA, HB)+1) - max(max(HB, HC) + 1, HA)
		HeightChang = max(HC, T2NEW + HC) - max(HA - T1, HA)
		HeightChang = max(HB - T2, T2NEW + HB - T2) - max(T1NEW + HB - T1, T1NEW + HB)

		T1,T2为旋转前K1，K2高度差
		T1 = HA - (max(HB, HC) + 1)
		T2 = HB - HC

		T1NEW,T2NEW为旋转后的高度差
		T1NEW = HA - HB
		T2NEW = max(HA, HB) + 1 - HC

		T1NEW = (T1 + max(HB, HC) + 1) - (T2 + HC)
		T1NEW = (T1 + max(T2 + HC, HC) + 1) - (T2 + HC)
		T1NEW = T1 + max(T2 + HC, HC) + 1 - T2 - HC
		if (T2 > 0)
		T1NEW = T1 + T2 + HC + 1 - T2 - HC
		T1NEW = T1 + 1
		else (T2 <= 0)
		T1NEW = T1 + HC + 1 - T2 - HC
		T1NEW = T1 + 1 - T2

		T2NEW = max(T1NEW + HB, HB) + 1 - (HB - T2)
		T2NEW = max(T1NEW + HB, HB) + 1 - HB + T2
		if (T1NEW > 0)
		T2NEW = T1NEW + HB + 1 - HB + T2
		T2NEW = T1NEW + 1 + T2
		else (T1NEW <= 0)
		T2NEW = HB + 1 - HB + T2
		T2NEW = 1 + T2
		*/
		int T1 = pK1->m_nSubHeight;
		int T2 = pK2->m_nSubHeight;
		int T1NEW = 0;
		int T2NEW = 0;
		if (T2 > 0)
			T1NEW = T1 + 1;
		else
			T1NEW = T1 + 1 - T2;

		if (T1NEW > 0)
			T2NEW = T1NEW + 1 + T2;
		else
			T2NEW = 1 + T2;

		pK1->m_nSubHeight = T1NEW;
		pK2->m_nSubHeight = T2NEW;


		//调整父结点的高度差
		int HB = 0;
		int nHeightChange = max(HB - T2, T2NEW + HB - T2) - max(T1NEW + HB - T1, T1NEW + HB);
		AdjuestSubHeight(pK2, nHeightChange);
	}

	//调整高度差
	void AdjuestSubHeight(CTreeNode<T>* pCurNode, int nAdd = 1)
	{
		CTreeNode<T>* pParent = pCurNode->m_pParent;

		while (pParent != NULL)
		{
			//添加结点
			if (nAdd > 0)
			{
				//左边加
				if (pCurNode == pParent->m_pLeft)
				{
					pParent->m_nSubHeight += nAdd;

					//树没变高，不调整
					if (pParent->m_nSubHeight <= 0)
					{
						break;
					}
				}
				//右边加
				else
				{
					pParent->m_nSubHeight -= nAdd;

					//树没变高
					if (pParent->m_nSubHeight >= 0)
					{
						break;
					}
				}
			}
			//删除结点
			else
			{
				//左边删除
				if (pCurNode == pParent->m_pLeft)
				{
					pParent->m_nSubHeight += nAdd;

					//树没变矮，不调整
					if (pParent->m_nSubHeight < 0)
					{
						break;
					}
				}
				//右边删除
				else
				{
					pParent->m_nSubHeight -= nAdd;

					//树没变矮
					if (pParent->m_nSubHeight > 0)
					{
						break;
					}
				}
			}

			pCurNode = pCurNode->m_pParent;
			pParent = pCurNode->m_pParent;
		}
	}

public:
	static ofstream out;  //全局输出流一份
	static ifstream in;   //全局输入流一份
	static tagFileSt<T> g_Data[MAX_NUM];  //数据数组
	static int g_nDelFlag; //删除标志
private:

	CTreeNode<T>* m_pRoot;   //根节点
	int	m_nCount;  //节点数量

};

template<typename T>
tagFileSt<T> CMyTree<T>::g_Data[MAX_NUM];

template<typename T>
int CMyTree<T>::g_nDelFlag = 0;

template<typename T>
ofstream CMyTree<T>::out;

template<typename T>
ifstream CMyTree<T>::in;
