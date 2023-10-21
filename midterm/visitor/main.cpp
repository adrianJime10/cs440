#include <iostream>

// Sec 1: There are some errors here. You may need to fix things and/or add
// functions.
class Visitor;
class TextNode;
class IntNode;

class Node {
    public:
	Node(){};
	virtual ~Node(){};
        Node(Node *l, Node *r) : m_left_child(l), m_right_child(r) {}
        void accept(const Visitor &) const;
	const Node *m_left_child;
	const Node *m_right_child;
    private:
        static void recurse(const Node *n, const Visitor &v) {
            if (n != nullptr) {
                n->accept(v);
            }
        }
};

class Visitor {
    public:
	Visitor(){};
	~Visitor(){};
        virtual void visit(const IntNode &) const = 0;
        virtual void visit(const TextNode &) const = 0;
};

void
Node::accept(const Visitor &v) const {
    recurse(m_left_child, v);
    recurse(m_right_child, v);
}

class TextNode : public Node {
    public:
	const Node *m_left_child;
	const Node *m_right_child;
	TextNode(const char* s, Node *l, Node *r) : m_str(s), m_left_child(l), m_right_child(r){}
        //TextNode(const char *s) : m_str(s) {}
        const std::string &str() const { return m_str; }
    private:
        const std::string m_str;
};

class IntNode : public Node {
    public:
	const Node *m_left_child;
	const Node *m_right_child;
	IntNode(const int i, Node *l, Node *r) : m_int(i), m_left_child(l), m_right_child(r){}
        //IntNode(const int i) : m_int(i) {}
        int intt() const { return m_int; }
	
    private:
        const int m_int;
};


// Sec 2: There are some errors here.
//
// Tips: Where do you need virtual functions?  And where do you need pure
// virtual functions?

class MyVisitor1 : public Visitor {
    public:
        virtual void visit(const IntNode &) const;
        virtual void visit(const TextNode &) const;
};

class MyVisitor2 : public Visitor {
    public:
        virtual void visit(const IntNode &) const;
        virtual void visit(const TextNode &) const;
};

// Sec 3: There are some errores, but there is no need to add more functions.

void
MyVisitor1::visit(const TextNode &n) const {
    std::cout << "MyVisitor1: " << n.str() << std::endl;
}

void
MyVisitor1::visit(const IntNode &n) const {
    std::cout << "MyVisitor1: " << n.intt() << std::endl;
}

void
MyVisitor2::visit(const TextNode &n) const {
    std::cout << "MyVisitor2: " << n.str() << std::endl;
}

void
MyVisitor2::visit(const IntNode &n) const {
    std::cout << "MyVisitor2: " << n.intt() << std::endl;
}

int
main() {

    TextNode t4{"T4", nullptr, nullptr};
    TextNode t2{"T2", nullptr, nullptr};
    IntNode i222{222, nullptr, &t4};
    IntNode i333{333, nullptr, nullptr};
    IntNode i111{111, &t2, &i222};
    TextNode t3{"T3", &i333, nullptr};
    TextNode t1{"T1", &i111, &t3};

    MyVisitor1 v1;
    MyVisitor2 v2;

    //ATTEMPTED TO DYNAMIC CAST
    /*t1.accept(dynamic_cast<Visitor&>(&v1));
    t1.accept(dynamic_cast<Visitor&>(&v2));*/
}
