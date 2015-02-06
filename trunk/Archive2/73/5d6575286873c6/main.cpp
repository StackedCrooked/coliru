#include <iostream>
#include <vector>

int x = 0;

    struct graph {
        graph()
        : intern(x++) {}
        int intern;
    };
    
    
    void add_graph(void*& app_ptr) {
        // (1) access the pointer
        auto ptr = reinterpret_cast<graph*>(app_ptr);
        std::cout << ptr->intern << "\n";
        
        // (2) delete the pointer
        delete ptr;
        
        // (3) set pointer in the vector to 0
        app_ptr = 0;    
    }
    
    
    int main() {
        std::vector<graph*> gr_arr;
        gr_arr.push_back(new graph());
        gr_arr.push_back(new graph());
        gr_arr.push_back(new graph());
        gr_arr.push_back(new graph());
        
        
        std::cout << "before\n";
        for(auto& it : gr_arr)
            std::cout << it << "\n";
            
        // (4) pass as reference to pointer
        add_graph((void*&)gr_arr.at(1));
        
        for(auto it : gr_arr)
            std::cout << it << "\n";
            
        std::cout << "after\n";
    }
