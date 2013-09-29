
// takes two absolute paths, and returns the second path as relative to the first.
std::string make_relative(const std::string& parent, std::string path)
{
    auto copy = path;
    copy.resize(parent.size());
    if (copy == parent)
    {
        path.erase(path.begin(), path.begin() + parent.size());
        while (!path.empty() && path.front() == '/')
        {
            path.erase(path.begin());
        }
    }
    return path;
}