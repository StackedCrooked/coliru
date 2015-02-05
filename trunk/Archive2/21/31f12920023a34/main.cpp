//Layout.h
#ifndef LAYOUT_H
#define LAYOUT_H

#ifndef SPEAKER_H
#define SPEAKER_H
namespace LSS
{
    struct Speaker
    {
        Speaker(int val1, float val2)
        :some_int(val1)
        , some_float(val2)
        {
        }

        ~Speaker()    
        {
            //do other stuff
        }

         int some_int;
         float some_float;

    };//struct Speaker
}
#endif

class Layout
{
    public:
        //unrelated stuff
    private:
        LSS::Speaker temp;
};
#endif


int main() {}
