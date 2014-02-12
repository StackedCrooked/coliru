
class Transaction
{
public:
    Transaction() : _commit(false), _para1(0), _para2(0) {}

    ~Transaction()
    {
        if (!_commit)
        {
            // unroll all the actions
            delete _para2;
            delete _para1;
        }
    }

    void LogFirst(Paragraph* para)
    {
        _para1 = para;
    }
    
    void LogSecond(Paragraph* para)
    {
        _para2 = para;
    }
    
    void Commit()
    {
        _commit = true;
    }
    
private:
    bool        _commit;
    Paragraph* _para1;
    Paragraph* _para2;
};
