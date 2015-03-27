#include <iostream>
#include <random>
#include <vector>
#include <memory>

class Rand{
    public:
        Rand(double const& min_inclusive, double const& max_exclusive):
            mt_(std::random_device()()),
            dist_(min_inclusive,max_exclusive){}
        ~Rand(){}
        double get() { return dist_(mt_); }
    private:
        std::mt19937_64 mt_;
        std::uniform_real_distribution<double> dist_;
};

class Base {
    public:
        Base():rnd(0.0,1.0){ std::cout<<"Base created "<<&rnd<<" "<<rnd.get()<<std::endl; }
        virtual ~Base(){};
        Rand rnd;
};

class Child: public Base{
    public:
        Child():var(0.0){ std::cout<<"Child created"<<std::endl; }
        double var;
};

class Other {
    public:
        Other(std::vector<std::shared_ptr<Base> > b):b_(b){
            std::cout<<"Other created "<<std::endl;
            for(unsigned int i(0);i<b_.size();i++){
                std::cout<<&(b_[i]->rnd)<<" and "<<&(b[i]->rnd)<<"--->"<<b_[i]->rnd.get()<<" "<<b[i]->rnd.get()<<std::endl;
            }
        }
        std::vector<std::shared_ptr<Base> > b_;
};

int main(){
    unsigned int N(2);
    std::cout<<"#############"<<std::endl;
    Other o1(std::vector<std::shared_ptr<Base> >(N, std::make_shared<Base>()));
 //   std::cout<<"#############"<<std::endl;
    Other o2(std::vector<std::shared_ptr<Base> >(N, std::make_shared<Child>()));
    std::cout<<"#############"<<std::endl;
}