    
    #include <iostream>
    #include <string>

    struct x {
      static const std::string PARTIAL_PAPER_CUT;
    };

    const std::string x::PARTIAL_PAPER_CUT = "\x1bi";

    int main() {
      std::cout << "\n\x1bi" << std::flush;
      std::cout << '\n' << char(27) << char(105) << std::flush;
      std::cout << '\n' << x::PARTIAL_PAPER_CUT << std::flush;
    }
