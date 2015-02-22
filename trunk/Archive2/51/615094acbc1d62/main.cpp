#include <iostream>
#include <sstream>
#include <string>

std::string trim_comments(std::string const& code) {
    typedef std::string::size_type size_t;

    std::string const comment_start = ";";
    std::ostringstream result;

    // Iteratively search for the start of the next comment and copy code before
    // that into the result.
    // We start by setting the previous comment end (the newline position) to
    // the start of the code.
    size_t newline_pos = 0;

    while (newline_pos != std::string::npos) {
        size_t const comment_pos = code.find(comment_start, newline_pos);

        if (comment_pos == std::string::npos) {
            // No more comments; copy the rest of the code from here until the
            // end into the result and quit.
            result << code.substr(newline_pos);
            break;
        }

        result << code.substr(newline_pos, comment_pos - newline_pos);
        // Find end of comment, assuming UNIX line endings.
        newline_pos = code.find('\n', comment_pos + comment_start.length());
    }

    return result.str();
}

int main() {
    std::string code = "push int32(50)\npush int32(45)\nadd\ndump\n;;";
    std::cout << code << "\n\n======\n\n" << trim_comments(code) << '\n';
}
