class MPageArrayCursor { 
protected: 
    int m_nIndex;

public: 
    MPageArrayCursor(int nIndex) { 
        m_nIndex = nIndex; 
    } 

    virtual ~MPageArrayCursor(); 

    int GetIndex() {
        return m_nIndex; 
    } 

    void SetIndex(int nIndex) {
        m_nIndex = nIndex;
    } 
};

template<typename T>
void Set(int, T, MPageArrayCursor *){}

template<typename T>
void Add(T pData, MPageArrayCursor* pCursor=0)
{
    int nFreeSlot = 5;

    Set(nFreeSlot, pData, pCursor);
}

int main(){}