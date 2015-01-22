template <class X> struct FreeListVector : public vector<X> {
    vector<int> free_list;
    void Clear() { this->clear(); free_list.clear(); }
    virtual int Insert(const X &v) {
        if (free_list.empty()) {
            this->push_back(v);
            return this->size()-1;
        } else {
            int free_ind = PopBack(free_list);
            (*this)[free_ind] = v;
            return free_ind;
        }
    }
    virtual void Erase(unsigned ind) {
        CHECK_LT(ind, this->size());
        free_list.push_back(ind);
    }
};

template <class K, class V> struct AVLTree {
    struct Node {
        K key; unsigned val:30, left:30, right:30, height:6;
        Node(K k=K(), unsigned v=0) : key(k), val(v), left(0), right(0), height(1) {}
        void SetChildren(unsigned l, unsigned r) { left=l; right=r; }
    };
    struct Query {
        const K &key; const V *val; V *ret;
        Query(const K &k, const V *v=0) : key(k), val(v), ret(0) {}
    };

    FreeListVector<Node> node;
    FreeListVector<V> val;
    int head=0;

    V*   Find  (const K &k)             { Query q(k);     return Find  (head, &q); }
    V*   Insert(const K &k, const V &v) { Query q(k, &v); head = Insert(head, &q); return q.ret; }
    bool Erase (const K &k)             { Query q(k);     head = Erase (head, &q); return q.ret; }

    V *Find(int ind, Query *q) {
        if (!ind) return 0;
        Node *n = &node[ind-1];
        if      (q->key < n->key) return Find(n->left,  q);
        else if (n->key < q->key) return Find(n->right, q);
        else return &val[n->val];
    }
    int Insert(int ind, Query *q) {
        if (!ind) return Create(q);
        Node *n = &node[ind-1];
        if      (q->key < n->key) node[ind-1].left  = Insert(n->left,  q);
        else if (n->key < q->key) node[ind-1].right = Insert(n->right, q);
        else { q->ret = &(val[n->val] = *q->val); return ind; }
        return Balance(ind);
    }
    int Create(Query *q) {
        int val_ind = val.Insert(*q->val);
        q->ret = &val[val_ind];
        return node.Insert(Node(q->key, val_ind))+1;
    }
    int Erase(int ind, Query *q) {
        if (!ind) return 0;
        Node *n = &node[ind-1];
        if      (q->key < n->key) n->left  = Erase(n->left,  q);
        else if (n->key < q->key) n->right = Erase(n->right, q);
        else {
            q->ret = &val[n->val];
            int left = n->left, right = n->right;
            val.Erase(n->val);
            node.Erase(ind);
            if (!right) return left;
            ind = GetMinNode(right);
            right = EraseMinNode(right);
            node[ind-1].SetChildren(left, right);
        }
        return Balance(ind);
    }
    int EraseMinNode(int ind) {
        Node *n = &node[ind-1];
        if (!n->left) return n->right;
        n->left = EraseMinNode(n->left);
        return Balance(ind);
    }
    int Balance(int ind) {
        Node *n = &node[ind-1];
        n->height = GetHeight(n);
        int nbal = GetBalance(ind);
        if (GetBalance(ind) > 1) {
            if (GetBalance(n->right) < 0) n->right = RotateRight(n->right);
            return RotateLeft(ind);
        } else if (nbal < -1) {
            if (GetBalance(n->left) > 0) n->left = RotateLeft(n->left);
            return RotateRight(ind);
        } else return ind;
    }
    int RotateLeft(int ind) {
        Node *n = &node[ind-1], *o = &node[n->right-1];
        n->right = o->left;
        o->left = ind;
        n->height = GetHeight(n);
        o->height = GetHeight(o);
        return n->right;
    }
    int RotateRight(int ind) {
        Node *n = &node[ind-1], *o = &node[n->left-1];
        n->left = o->right;
        o->right = ind;
        n->height = GetHeight(n);
        o->height = GetHeight(o);
        return n->left;
    }
    int GetMinNode(int ind) const {
        const Node *n = &node[ind-1];
        return n->left ? GetMinNode(n->left) : ind;
    }
    int GetHeight(Node *n) const {
        return max(n->left  ? node[n->left -1].height : 0,
                   n->right ? node[n->right-1].height : 0);
    }
    int GetBalance(int ind) const {
        const Node *n = &node[ind-1];
        return (n->right ? node[n->right-1].height : 0) -
               (n->left  ? node[n->left -1].height : 0);
    }
};

TEST(TypesTest, AVLTree) {
    map<int, int> m;
    map<int, int>::const_iterator mi;
    AVLTree<int, int> at;
    vector<int> db;

    int *v, rand_test_size = 65536;
    unordered_set<int> rand_unique;
    for (int i=0; i<rand_test_size; i++) {
        int ri = Rand(0, 10000000);
        if (!rand_unique.insert(ri).second) { i--; continue; }
        db.push_back(ri);
    }
    PerformanceTimers *timers = Singleton<PerformanceTimers>::Get();
    int avl_ctid = timers->Create("AVLTree  ins1"),   map_ctid = timers->Create("std::map ins1");
    int avl_qtid = timers->Create("AVLTree  query1"), map_qtid = timers->Create("std::map query1");
    int avl_dtid = timers->Create("AVLTree  del"),    map_dtid = timers->Create("std::map del");
    int avl_rtid = timers->Create("AVLTree  query2"), map_rtid = timers->Create("std::map query2");
    int avl_Ctid = timers->Create("AVLTree  ins2"),   map_Ctid = timers->Create("std::map ins2");

    timers->AccumulateTo(avl_ctid); for (auto i : db) at.Insert(i, i);
    timers->AccumulateTo(avl_qtid); for (auto i : db) { EXPECT_NE((int*)0, (v=at.Find(i))); if (v) EXPECT_EQ(i, *v); }
    timers->AccumulateTo(avl_dtid); for (int i=0, hl=db.size()/2; i<hl; i++) EXPECT_EQ(true, at.Erase(db[i]));
    timers->AccumulateTo(avl_rtid);
    for (int i=0, l=db.size(), hl=l/2; i<l; i++) {
        if (i < hl) EXPECT_EQ(0, at.Find(db[i]));
        else { EXPECT_NE((int*)0, (v=at.Find(db[i]))); if (v) EXPECT_EQ(db[i], *v); }
    }
    timers->AccumulateTo(avl_Ctid); for (int i=db.size()/2-1; i>=0; i--) at.Insert(db[i], db[i]);

    timers->AccumulateTo(map_ctid); for (auto i : db) m[i] = i;
    timers->AccumulateTo(map_qtid); for (auto i : db) { EXPECT_NE(m.end(), (mi=m.find(i))); if (mi!=m.end()) EXPECT_EQ(i, mi->second); }
    timers->AccumulateTo(map_dtid); for (int i=0, l=db.size()/2; i<l; i++) EXPECT_EQ(1, m.erase(db[i]));
    timers->AccumulateTo(map_rtid);
    for (int i=0, l=db.size(), hl=l/2; i<l; i++) {
        if (i < hl) EXPECT_EQ(m.end(), m.find(db[i]));
        else { EXPECT_NE(m.end(), (mi=m.find(db[i]))); if (mi!=m.end()) EXPECT_EQ(db[i], mi->second); }
    }
    timers->AccumulateTo(map_Ctid); for (int i=db.size()/2-1; i>=0; i--) m[db[i]] = db[i];

    timers->AccumulateTo(0);
    INFO(timers->DebugString());

    // rand_test_size = 1024*1024;
    // AVLTree  ins1 1.198
    // std::map ins1 0.944
    // AVLTree  query1 0.67
    // std::map query1 0.966

    // rand_test_size = 65536;
    // AVLTree  ins1 0.03
    // std::map ins1 0.015
    // AVLTree  query1 0.014
    // std::map query1 0.012
}