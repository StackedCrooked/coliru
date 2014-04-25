#include <string>

#include <algorithm>
#include <iostream>
#include <vector>

using std::string;

class PCB
{
public:
    void setPID (int a)
    {
        PID = a;
    }
    int retrievePID()
    {
        return PID;
    }
    void setFilename (string input)
    {
        Filename = input;
    }
    string retrieveFilename()
    {
        return Filename;
    }
    void setMemstart (int a)
    {
        Memstart = a;
    }
    int retrieveMemstart()
    {
        return Memstart;
    }
    void setRW (char a)
    {
        rw = a;
    }
    char retrieveRW()
    {
        return rw;
    }
    void setFilelength (int input)
    {
        Filelength = input;
    }
    int retrieveFilelength()
    {
        return Filelength;
    }
    int retrieveCylinder()
    {
        return Cylinder;
    }
    void setCylinder (int a)
    {
        Cylinder = a;
    }

private:
    int PID;
    string Filename;
    int Memstart;
    char rw;
    int Filelength;
    int Cylinder;
};

int main() {
    int const DiskDevices = 10;
    int const QueueNumber = 3;
    using std::vector;
    vector<PCB> Disks2[DiskDevices];
    std::sort(Disks2[QueueNumber-1].begin(), Disks2[QueueNumber-1].end(),
         [](PCB a, PCB b)
         {
           return (a.retrieveCylinder()>b.retrieveCylinder());
         });
    std::cout << "Worksforme\n";
}
