#include <iostream>
#include <string>
#include <initializer_list>

using QString = std::string;

struct qDebug
{
    ~qDebug() { std::cout << std::endl; }
};

template<typename T>
qDebug const& operator<<(qDebug const& qd, T const& t)
{ 
    std::cout << t << ' ';
    return qd;
}

enum eElementMode { modeDefault };

class ProtocolDescriptorTestNode {

public:
    ProtocolDescriptorTestNode(const ProtocolDescriptorTestNode&) = default;

    ProtocolDescriptorTestNode(std::initializer_list<ProtocolDescriptorTestNode > init); // 1
    ProtocolDescriptorTestNode(QString name, std::initializer_list<ProtocolDescriptorTestNode > init); // 2
    ProtocolDescriptorTestNode(QString name, QString id, enum eElementMode = modeDefault); // 4
    ProtocolDescriptorTestNode(QString name, enum eElementMode = modeDefault); //5

    ~ProtocolDescriptorTestNode() {}

     QString name, id;
//     tProtocolDescriptorTestList list;
};

ProtocolDescriptorTestNode::ProtocolDescriptorTestNode(std::initializer_list<ProtocolDescriptorTestNode> init)
{
    qDebug() << "*** CONSTRUCTOR CALLED - 1 *** ";
    qDebug() << init.size();
    
    bool first = true;
    for(ProtocolDescriptorTestNode x : init) {
        qDebug() << "(";
        qDebug() << x.name << x.id;
        qDebug() << ")"
/*        
        if(first) {
            name = x.name; 
            id = x.id;
            first = false;
        }
*/        
    }
}

ProtocolDescriptorTestNode::ProtocolDescriptorTestNode(QString name, std::initializer_list<ProtocolDescriptorTestNode> init) {
    qDebug() << "*** CONSTRUCTOR CALLED - 2 *** ";
    qDebug() << init.size();
    for(ProtocolDescriptorTestNode x : init) {
        qDebug() << x.name << x.id;
    }
}

ProtocolDescriptorTestNode::ProtocolDescriptorTestNode(QString name, QString id, enum eElementMode) :
    name(name),
    id(id)
{
    qDebug() << "*** CONSTRUCTOR CALLED - 4 *** ";
    qDebug() << name << id;
}

ProtocolDescriptorTestNode::ProtocolDescriptorTestNode(QString name, enum eElementMode)  :
    name(name),
    id("***")
{
    qDebug() << "*** CONSTRUCTOR CALLED - 5 *** ";
    qDebug() << name << id;
}

int main()
{
    ProtocolDescriptorTestNode groupOther
    {
        {QString("name1"),"groupOther1"},
        {"name2","groupOther2"},
    
        { "B", 
            {
                {"name3","groupOther3"},
                {
                    {"intra1","a"},
                    {QString("intra2")}
                },
                {"name4","groupOther4"}
            } 
        }
    };
}
