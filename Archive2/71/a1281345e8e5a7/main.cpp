
#include <string>
#include <iostream>
#include <fstream>
#include <valarray>

using namespace std;

typedef std::valarray<float>  FVector;


int main(int argc, char *argv[])
{

    string a = "../data/TestBoW/TestTSSIFTBoW.EH.CM";
    string b = "../data/Train1024BowEHCM.txt";
    ifstream inFea(a.c_str());
    ifstream inFusion(b.c_str());


    while (!inFea.eof())
    {
        //if the message isnt 2*625*4 bytes, is wruung

        FVector feature;
        FVector fusion;

        if (!(inFea >> feature))
            break;

        if (!(inFusion >> fusion))
            break;

    }
    return app.exec();
}
