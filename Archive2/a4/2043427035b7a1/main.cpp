#include <iostream>
#include <string>
#include <vector>

class Publisher ;

class Subscriber
{
    std::vector<Publisher*> subscribed_to ;
public:
    void subscribeTo(Publisher*);
    virtual void getPublication(const Publisher*) = 0 ;
};

class Person : public Subscriber
{
    std::string name ;
public:
    Person(const std::string& s) : name(s) {}
    void getPublication(const Publisher*);
    
    friend std::ostream& operator<<(std::ostream& stream, const Person& p)
    {
        stream << p.name ;
        return stream ;
    }
};

class Publisher
{
    std::vector<Subscriber*> subscribers ;
    std::string name ;
    std::vector<std::string> publications; 
    
    void publish() { for(auto& c : subscribers) c->getPublication(this); }
    
public:
    Publisher(const std::string &n) : name(n) {}
    void addSubscriber(Subscriber* s) { subscribers.push_back(s); }
    std::string getName() const { return name; }
    std::string getLatestPublication() const { return publications.back(); }
    void addPublication(const std::string& ct) { publications.push_back(ct); publish(); }
};

void Subscriber::subscribeTo(Publisher* p) 
{ subscribed_to.push_back(p); p->addSubscriber(this); }
 
void Person::getPublication(const Publisher* p) 
{ std::cout << name << " got publication : " << p->getLatestPublication() << " from " << p->getName() << std::endl; }

int main() {
	Publisher p1("mcgrawhill"), p2("pearson");
    Person n1("Shaun"), n2("Nick");
    n1.subscribeTo(&p1);
    n2.subscribeTo(&p1);
    n2.subscribeTo(&p2);
    p1.addPublication("C++11 Reference");
    p2.addPublication("C++14 Reference");
	return 0;
}