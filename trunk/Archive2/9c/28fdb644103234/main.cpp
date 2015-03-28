#include <iostream>
#include <list>
#include <utility>

struct Student
{
//...
};

class MagicList
{
  public:
    void AddNode(int addData);
    void DeleteNode(int delData);
    void PrintList() const;
  private:
    using Node = std::pair<int, std::list<Student>>;
    std::list<Node> data;
};

void MagicList::AddNode(int addData)
{
    data.push_back(std::make_pair(addData, std::list<Student>()));
}

void MagicList::DeleteNode(int delData)
{
    data.remove_if([delData](const Node& x){ return x.first == delData;});
}

void MagicList::PrintList() const
{
    unsigned count = 0;
    for(const auto& item: data) {
        std::cout << "Node " << count << ", data value: " << item.first << std::endl;
        std::cout << "Students: ";
        if (item.second.empty()) {
            std::cout << "None;" << std::endl;
            continue;
        }
        bool first = true;
        for(const auto& student: item.second) {
            std::cout << (first?"":", ") ;//<< student;
                                          //↑Commented for the sake of example, 
                                          //provide your own operator << overload
        }
        std::cout << ';' << std::endl;
    }
}


int main()
{
    MagicList l;
    l.AddNode(6);
    l.AddNode(2);
    l.AddNode(4);
    l.DeleteNode(2);
    l.PrintList();
}