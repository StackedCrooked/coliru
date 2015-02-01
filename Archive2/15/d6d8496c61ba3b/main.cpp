#include <fstream>
#include <chrono>
#include <ctime>
#include <stdexcept>

// classes
std::string getProperDate() //plus jamais ça :'(
{
    auto tmp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto str = std::localtime(&tmp); //aïe
    char s[256]; // *se sent mal*
    strftime(s, 256, "%F | %T", str); // pan ! *bruit de tir*
    return std::string(s);
}

class Log
{
public:
    static Log& instance()
    {
        static Log *instance = new Log();
        return *instance;
    }

    void write(std::string const& data)
    {

        file_ << "[" << getProperDate() << "] : ";
        file_ << data << std::endl;
    }

private:
    std::ofstream file_;

    Log() : file_("log.txt", std::ios::out | std::ios::app) //ctor deleted
    {
        if (!file_) throw std::runtime_error("Unable to open log file.");
    }
};
//###########################

//######Code de démon
int main()
{
    Log::instance().write("Coucou, tu veux voir ma bite ?"); //on écrit Coucou tu veux voir ma bite avec la date et l'heure dans le fichier de log   
}
