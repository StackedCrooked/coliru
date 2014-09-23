#include <iostream>
#include <fstream>

int main() {
    std::ofstream htmlfile;
    htmlfile.open ("index.html");
    htmlfile << "<!DOCTYPE html>";
    htmlfile << "<html>";
    htmlfile << "<head>";
    htmlfile << "<meta charset="UTF-8">";
    htmlfile << "<title>Title of the document</title>";
    htmlfile << "</head>";
    htmlfile << "<body>";
    htmlfile << "Content of the document.";
    htmlfile << "</body>";
    htmlfile << "</html>";
    htmlfile.close();
}