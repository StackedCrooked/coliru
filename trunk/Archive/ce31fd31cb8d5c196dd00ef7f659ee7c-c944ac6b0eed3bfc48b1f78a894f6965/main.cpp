#include <cassert>
#include <string>

namespace Path {
    static const char SEGMENT_SEPARATOR = '/';
}

std::string normalize(std::string parentPath, const std::string& name) {
    if (name.empty()) {
        return parentPath;
    } else {
        parentPath.reserve(parentPath.length()+name.length()+1);
        if (*name.begin() != Path::SEGMENT_SEPARATOR) {
            parentPath.append(1,Path::SEGMENT_SEPARATOR);
        }
        if(*name.rbegin() != Path::SEGMENT_SEPARATOR){
            parentPath.append(name);
        }else{
            parentPath.append(name.begin(), --name.end());
        }
        return parentPath;
    }
}

int main() {
    assert("a/b/c/d" == normalize("a/b/c", "d"));
    assert("a/b" == normalize("a/b", ""));
    assert("a/b/c" == normalize("a/b", "c/"));
    assert("a/b/c" == normalize("a/b", "/c/"));
}
