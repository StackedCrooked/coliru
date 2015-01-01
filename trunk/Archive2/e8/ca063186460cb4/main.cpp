// Using standard allocator:
map<string, vector<string> my_map = {
        { "s1", { "a", "b", "c" } },
        { "s2", { "d", "e", "e" } }
};

// Using custom and stateful allocator:
Alloc alloc;
MyMap my_map = {
        { { { "s1", alloc }, { { { "a", alloc }, { "b", alloc }, { "c", alloc } }, alloc } },
          { { "s2", alloc }, { { { "a", alloc }, { "b", alloc }, { "c", alloc } }, alloc } }
        }, MyMap::key_compare(), alloc
    };
    
    
    // real example http://coliru.stacked-crooked.com/a/ef88bff092316c7b