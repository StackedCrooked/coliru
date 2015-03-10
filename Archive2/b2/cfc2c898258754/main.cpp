#include <iostream>
#include <fstream>

int main() {
    //Write part
    std::string filename = "binary_file.bin";
    std::ofstream file_write(filename.c_str(), std::ofstream::binary);
    if(!file_write.is_open()) {
      return -1;
    }

    //Write char (1 byte)
    char c = 'A';
    file_write.write((char *)(&c), sizeof(c));

    //Write unsigned char (1 byte)
    unsigned char uc = 255;
    file_write.write((char *)(&uc), sizeof(uc));

    //Write int (4 bytes)
    int integer = 2147483647;
    file_write.write((char *)(&integer), sizeof(integer));

    //Write an unsigned char array of 4 elements
    unsigned char c_array[] = {128, 129, 130, 131};
    file_write.write((char *)(&c_array[0]), sizeof(c_array));

    //Write a char arry of 4 elements
    size_t length = 4;
    char *c_array2 = new char[length];
    c_array2[0] = 'A';
    c_array2[1] = 'B';
    c_array2[2] = 'C';
    c_array2[3] = '\0';
    file_write.write((char *)(c_array2), sizeof(char)*length);

    file_write.close();


    //Read part
    std::ifstream file_read(filename.c_str(), std::ifstream::binary);
    if(!file_read.is_open()) {
      return -1;
    }

    //Read char
    c = 0;
    file_read.read((char *)(&c), sizeof(c));
    std::cout << "Read char=" << c << " ; numerical value=" << static_cast<unsigned>(c) << std::endl;

    //Read unsigned char
    uc = 0;
    file_read.read((char *)(&uc), sizeof(uc));
    std::cout << "Read unsigned char=" << static_cast<unsigned>(uc) << std::endl;

    //Read int
    integer = 0;
    file_read.read((char *)(&integer), sizeof(integer));
    std::cout << "Read integer=" << integer << std::endl;

    //Read an unsigned char array of 4 elements
    unsigned char c_array_read[4];
    file_read.read((char *)(c_array_read), sizeof(c_array_read));
    std::cout << "Read c_array_read={" << static_cast<unsigned>(c_array_read[0]) << ", "
        << static_cast<unsigned>(c_array_read[1]) << ", "
        << static_cast<unsigned>(c_array_read[2]) << ", "
        << static_cast<unsigned>(c_array_read[3]) << "}" << std::endl;

    //Read a char array of 4 elements
    char *c_array_read2 = new char[length];
    file_read.read((char *)(c_array_read2), sizeof(char)*length);
    std::cout << "Read c_array_read2=" << c_array_read2 << std::endl;

    file_read.close();


    //Test conversion 16 bits stored in int <==> char
    int value = 65530;
    unsigned char c1 = static_cast<unsigned char>(value);
    std::cout << "c1=" << static_cast<unsigned>(c1) << std::endl;

    unsigned char c2 = static_cast<unsigned char>(value >> 8);
    std::cout << "c2=" << static_cast<unsigned>(c2) << std::endl;

    value = 0;
    value = (c2 << 8) + c1;
    std::cout << "value=" << value << std::endl;
}
