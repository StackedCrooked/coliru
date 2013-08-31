namespace ast
{
    struct Num;
    struct AddOp;

    struct Visitor
    {
        virtual void visit(Num&) = 0;
        virtual void visit(AddOp&) = 0;
    };

    struct AbstractNode
    {
        virtual void accept(Visitor&) = 0;
        virtual ~AbstractNode() {}
    };

    template<typename T>
    struct NodeHelper : AbstractNode
    {
        virtual void accept(Visitor& v) override { v.visit(static_cast<T&>(*this)); }
    };

    struct Num : NodeHelper<Num>
    {
        Num(int x) : x(x) {}
        int x;
    };

    struct AddOp : NodeHelper<AddOp>
    {
        AddOp(AbstractNode* a, AbstractNode* b) : a(a), b(b) {}
        AbstractNode* a;
        AbstractNode* b;
    };
}

//////////////////////////////////////////////////////////////////////////
// test code

#include <iostream>

inline std::ostream& operator<<(std::ostream& os, ast::AbstractNode* n)
{
    struct PrintVisitor : ast::Visitor
    {
        std::ostream& os;
        PrintVisitor(std::ostream& os) : os(os) {}

        virtual void visit(ast::Num& o) override { os << o.x; }
        virtual void visit(ast::AddOp& o) override { os << "(" << o.a << "+" << o.b << ")"; }
    }
    v(os);
    n->accept(v);
    return os;
}

int calc(ast::AbstractNode* n)
{
    struct CalcVisitor : ast::Visitor
    {
        int result;

        virtual void visit(ast::Num& o) override { result = o.x; }
        virtual void visit(ast::AddOp& o) override { result = calc(o.a) + calc(o.b); }
    }
    v;
    n->accept(v);
    return v.result;
}

#include <sstream>

struct Emitter
{
    std::stringstream code;
    void load(int x) { code << "load " << x << "; "; }
    void add() { code << "add; "; }
};

void emit(Emitter& e, ast::AbstractNode* n)
{
    struct EmitVisitor : ast::Visitor
    {
        Emitter& e;
        EmitVisitor(Emitter& e) : e(e) {}

        virtual void visit(ast::Num& o) override
        {
            e.load(o.x);
        }
        virtual void visit(ast::AddOp& o) override
        {
            emit(e, o.a);
            emit(e, o.b);
            e.add();
        }
    }
    v(e);
    n->accept(v);
}

#include <memory>
#include <deque>

template<typename T>
class GarbageCollector
{
public:
    GarbageCollector() {}

    void* alloc(std::size_t size)
    {
        auto mem = std::malloc(size);
        objList.push_back((T*)mem);
        return mem;
    }

    void free_last()
    {
        std::free(objList.back());
        objList.pop_back();
    }

    ~GarbageCollector()
    {
        for (auto& p : objList)
            delete p;
    }

private:
    GarbageCollector(const GarbageCollector&); // = delete;
    void operator=(const GarbageCollector&); // = delete;
    
    std::deque<T*> objList;
};

template<class T>
inline void* operator new(std::size_t size, GarbageCollector<T>& gc)
{
    return gc.alloc(size);
}

/// called on exception in `new(gc) T`
template<class T>
inline void operator delete(void*, GarbageCollector<T>& gc)
{
    gc.free_last();
}

int main()
{
    GarbageCollector<ast::AbstractNode> gc;

    auto root = 
        new(gc) ast::AddOp(
            new(gc) ast::AddOp(
                new(gc) ast::Num(100),
                new(gc) ast::Num(20)
            ),
            new(gc) ast::Num(3)
        );

    std::cout << root << " = " << calc(root) << std::endl;

    Emitter e;
    emit(e, root);
    std::cout << e.code.rdbuf() << std::endl;
}