//Creates string representations of the tree - toString is "pretty"
    std::string toString(const Node* t) const{
        std::vector<std::vector<T*> > elements;
        createLevelVector(t,elements);
        //Format the string according to the vector
        //No idea how to do that...
    }
    void createLevelVector(const Node* t, std::vector<std::vector<T*> >& e, int level = 0){
        if(t==NULL){
            e[level].push_back(NULL);
            return;
        }
        e[level].push_back(t->data);
        createLevelVector(t->left,e,level+1);
        createLevelVector(t->right,e,level+1);
    }
