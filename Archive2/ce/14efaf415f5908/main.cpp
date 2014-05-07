#include <unordered_map>

enum ENUM1 {
    ENUM1_A,
    ENUM1_B,
};

enum ENUM2 {
    ENUM2_A,
    ENUM2_B
};

enum ENUM3 {
    ENUM3_A,
    ENUM3_B
};

namespace std
{
    template <> struct hash<ENUM1> : std::hash<int> {};
    template <> struct hash<ENUM2> : std::hash<int> {};
    template <> struct hash<ENUM3> : std::hash<int> {};
}

int main()
{
    std::unordered_map<ENUM1, std::unordered_map<ENUM2, std::unordered_map<ENUM3, int>>> A = {
        {
            ENUM1_A, {
                {   
                    ENUM2_A, {
                        { ENUM3_A, 123 },
                        { ENUM3_B, 45 },
                    },
                },
                {
                    ENUM2_B, {
                        { ENUM3_A, 733 },
                        { ENUM3_B, 413 },
                    }
                }
            }
        }
    };
}
