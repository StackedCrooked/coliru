#include <iostream>
#include <string>
#include <vector>

int main() 
{
    const std::string output_filename_base = "output_MyFancyProgram_";
    const std::string output_filename_extension = ".csv";

    const std::vector<double> whatevers {1., 2., 3.};
    const std::vector<double> stuffs {11., 22., 33.};
    
    for (auto whatever : whatevers)
    {
        for (auto stuff : stuffs)
        {
            const std::string output_filename = output_filename_base
                                                + std::to_string(whatever)
                                                + "_"
                                                + std::to_string(stuff)
                                                + output_filename_extension;
            std::cout << "output_filename = " << output_filename << "\n";
        }
    }
}
