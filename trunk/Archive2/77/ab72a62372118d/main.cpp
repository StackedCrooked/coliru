#include <iostream>
#include <fstream>
 
int main()
{
    // Prépare le fichier d'exemple
    std::ofstream ofs ("/tmp/4e82e821-9f38-4ecf-bd8a-4297aa8d440c");
    ofs << "a a" << std::endl;
    ofs << "b b " << std::endl;
    ofs << "c c"; // On omet le fin de ligne explicitement
    ofs.close ();
        
    // Ouvre le fichier temporaire
    std::filebuf fb;
    if (!fb.open ("/tmp/4e82e821-9f38-4ecf-bd8a-4297aa8d440c", std::ios::in))
        return -1;

    // Print toutes les lignes
    char buf[512];
    std::istream is (&fb);
    while (is.getline (buf, sizeof (buf)))
        std::cout << "Line : \"" << buf << "\"" << std::endl;
    fb.close ();
    
    return 0;
}

