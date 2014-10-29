template <typename type>
class SnglLnkLstDmHdr
{
public:
    SnglLnkLstDmHdr()
	{
		this->Start = nullptr;
	}
private:
	struct Node
	{
		type Data;
		Node *link;
	};

	Node *Start;
	static Node *DummyHead;
};

template <typename type>
typename SnglLnkLstDmHdr<type>::Node* SnglLnkLstDmHdr<type>::DummyHead = nullptr;

int main()
{
    SnglLnkLstDmHdr<int> f;
}
