#include <iostream>
#include <vector>

using namespace std;

class computer
{
    public:
        computer(double RAM=0, double CPUSpeed=0, int numberOfCores=0, double HDDSize=0);
        double RAM;
        double CPUSpeed;
        int    numberOfCores;
        double HDDSize;

        virtual std::ostream& print(std::ostream& os) const {
            return os << "RAM:" << RAM << ", CPUSpeed:" << CPUSpeed << ", numberOfCores:" << numberOfCores << ", HDDSize:" << HDDSize;
        }
};

class desktop : public computer
{
    public:
        desktop(double RAM=0, double CPUSpeed=0, int numberOfCores=0, double HDDSize=0,
                bool hasMonitor=false, double monitorSize=0);
        bool   hasMonitor;
        double monitorSize;
        friend istream& operator>> (istream &in, desktop &myDesktop);
        virtual std::ostream& print(std::ostream& os) const {
            return computer::print(os) << ", hasMonitor:" << std::boolalpha << hasMonitor << ", monitorSize:" << monitorSize;
        }
};

class laptop : public computer
{
    public:
        laptop(double RAM=0, double CPUSpeed=0, int numberOfCores=0, double HDDSize=0, double screenSize=0);
        double screenSize;
        virtual std::ostream& print(std::ostream& os) const {
            return computer::print(os) << ", screenSize:" << screenSize;
        }
};

class cluster : public computer
{
    public:
        cluster(double RAM=0, double CPUSpeed=0, int numberOfCores=0, double HDDSize=0, unsigned numOfComp=0);
        unsigned numOfComp;
        virtual std::ostream& print(std::ostream& os) const {
            return computer::print(os) << ", numOfComp:" << numOfComp;
        }
};

computer::computer(double RAM, double CPUSpeed, int numberOfCores, double HDDSize) :
    RAM(RAM), CPUSpeed(CPUSpeed), numberOfCores(numberOfCores), HDDSize(HDDSize) 
{
}

desktop::desktop(
        double RAM, double CPUSpeed, int numberOfCores, double HDDSize,
        bool hasMonitor, double monitorSize) :
    computer(RAM, CPUSpeed, numberOfCores, HDDSize), 
    hasMonitor(hasMonitor), monitorSize(monitorSize)
{
}

laptop::laptop(
        double RAM, double CPUSpeed, int numberOfCores, double HDDSize,
        double screenSize) : 
    computer(RAM, CPUSpeed, numberOfCores, HDDSize), 
    screenSize(screenSize)
{
}

cluster::cluster(
        double RAM, double CPUSpeed, int numberOfCores, double HDDSize, 
        unsigned numOfComp) :
    computer(RAM, CPUSpeed, numberOfCores, HDDSize), 
    numOfComp(numOfComp)
{
}

istream& operator>> (istream &in, desktop &myDesktop)
{
    in >> myDesktop.hasMonitor;
    in >> myDesktop.monitorSize;
    in >> myDesktop.RAM;
    in >> myDesktop.CPUSpeed;
    in >> myDesktop.HDDSize;
    in >> myDesktop.numberOfCores;
    return in;
}

istream& operator>> (istream &in, laptop &mylaptop)
{
    in >> mylaptop.RAM;
    in >> mylaptop.CPUSpeed;
    in >> mylaptop.HDDSize;
    in >> mylaptop.numberOfCores;
    in >> mylaptop.screenSize;
    return in;
}

istream& operator>> (istream &in, cluster &myCluster)
{
    in >> myCluster.RAM;
    in >> myCluster.CPUSpeed;
    in >> myCluster.HDDSize;
    in >> myCluster.numberOfCores;
    in >> myCluster.numOfComp;
    return in;
}

cluster operator+(cluster const& a, cluster const& b)
{
    return cluster(std::min(a.RAM, b.RAM),
            std::min(a.CPUSpeed, b.CPUSpeed),
            std::min(a.HDDSize, b.HDDSize),
            std::min(a.numberOfCores, b.numberOfCores),
            a.numOfComp + b.numOfComp);
}

cluster operator+(cluster const& a, computer const& b)
{
    return cluster(std::min(a.RAM, b.RAM),
            std::min(a.CPUSpeed, b.CPUSpeed),
            std::min(a.HDDSize, b.HDDSize),
            std::min(a.numberOfCores, b.numberOfCores),
            a.numOfComp + 1);
}

cluster operator+(computer const& a, computer const& b)
{
    return cluster(std::min(a.RAM, b.RAM),
            std::min(a.CPUSpeed, b.CPUSpeed),
            std::min(a.HDDSize, b.HDDSize),
            std::min(a.numberOfCores, b.numberOfCores),
            2);
}

cluster operator+(computer const& a, cluster const& b)
{
    return b + a;
}

std::ostream& operator<<(std::ostream& os, computer const& c)
{
    return c.print(os);
}

int main()
{
    desktop desktop1(2048, 2.8, 300*1024, 8);
    desktop desktop2(4096, 3.1, 100*1024, 4);
    laptop  laptop1(2048, 1.5, 100*1024, 2);

    std::cout << desktop1 + desktop2 << "\n";
    std::cout << laptop1 + desktop1 << "\n";
    std::cout << laptop1 + desktop2 << "\n";
     
    cluster clust1 = desktop1 + desktop2;
    clust1         = clust1 + laptop1;

    std::cout << clust1 << "\n";
}
