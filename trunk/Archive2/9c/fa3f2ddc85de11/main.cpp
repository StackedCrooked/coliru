#include <vector>

class packet
{
private:
    unsigned int command;
    const unsigned char msgTail[4] = { 1, 0, 3, 2 };
public:
    packet(unsigned int cmd) :command(cmd){};
	~packet();
	void pack(std::vector<unsigned char>& snd)
    {
        
        };
};

int main()
{


};

