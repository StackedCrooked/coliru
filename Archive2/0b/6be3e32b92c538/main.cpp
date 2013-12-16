#include <stack>
#include <map>
#include <string>

int main() {
    std::stack<std::map<std::string,int>> st; 
    std::map<std::string,int> ma; 
    st.push(ma); 
    ma = st.top();
    st.pop(); 
    return 0; 
} 