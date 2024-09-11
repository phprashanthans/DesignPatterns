/*
Composite: Structural Design Pattern
This lets you compose objects into tree structures and then work with
these structures as if they were individual objects. It is quite 
popular for problems that require building a tree structure.
 */

#include <iostream>
#include <list>

// The base component class declares common operations for both 
// simple and complex objects of composition
class Component {
    protected:
        Component* parent_;
    public:
        virtual ~Component() {}
        void setParent(Component *parent) {
            this->parent_ = parent;
        }
        Component* getParent() const {
            return this->parent_;
        }
        virtual void Add(Component* component) {}
        virtual void Remove(Component* component) {}
        virtual bool IsComposite() const {
            return false;
        }
        // Abstract behaviour
        virtual std::string Operation() const = 0;
};
class Leaf : public Component {
    public:
        std::string Operation() const override {
            return "Leaf";
        }
};
class Composite : public Component {
    protected:
        std::list<Component*> children_;
    public:
        void Add(Component* component) override {
            this->children_.push_back(component);
            component->setParent(this);
        }
        void Remove(Component* component) override {
            children_.remove(component);
            component->setParent(nullptr);
        }
        bool IsComposite() const override {
            return true;
        }
        std::string Operation() const override {
            std::string result;
            for (const Component* c : children_) {
                if (c == children_.back()) {
                    result += c->Operation();
                } else {
                    result += c->Operation() + '+';
                }
            }
            return "Branch(" + result + ")";
        }
};
void ClientCode(Component* component) {
    std::cout << "Result:" << component->Operation();
}

int main() {
    Component* simple = new Leaf();
    std::cout << "Client: I have got a simple component:\n";
    ClientCode(simple);
    std::cout << "\n\n";
    delete simple;

    Component* tree = new Composite();
    Component* branch_1 = new Composite();
    Component* leaf_1 = new Leaf();
    Component* leaf_2 = new Leaf();
    Component* leaf_3 = new Leaf();
    branch_1->Add(leaf_1);
    branch_1->Add(leaf_2);
    Component* branch_2 = new Composite();
    branch_2->Add(leaf_3);
    tree->Add(branch_1);
    tree->Add(branch_2);
    std::cout << "Client: Now I've got a composite tree:\n";
    ClientCode(tree);
    std::cout << "\n\n";
    delete leaf_1;
    delete leaf_2;
    delete leaf_3;
    delete branch_1;
    delete branch_2;
    delete tree;
    return 0;
}
