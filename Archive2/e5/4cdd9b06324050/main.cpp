    #include <iostream>
    #include <fstream>
    
    void writeToFile () {
        std::fstream fs;
        fs.open ("./test.txt", std::fstream::in | std::fstream::out | std::fstream::app);
        fs << " test content";
    
        fs.close();
    }
    
    int main() {
        writeToFile();
    }
    
    
    