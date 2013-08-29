struct s {
    int x, y, z;
};
bool operator<(const s& lhs, const s& rhs) {
    return std::tie(lhs.x, lhs.y, lhs.z) < std::tie(rhs.x, rhs.y, rhs.z);
}