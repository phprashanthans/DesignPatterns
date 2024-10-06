/* Visitor: Behavorial Design pattern
    This lets you separate algorithms from objects on which they operate. It 
    allows adding new behaviors to existing class hierarchy without altering 
    existing code. 
    It suggests that you place the new behavior into a separate class called 
    as vistor, instead of trying to integrate it inot existing classes. The 
    original object that had to perform the behavior is now passed to one of
    the visitor's method as an argument, providing the method access to all 
    necessary data contained within the object.
    Double Dispatch: Instead of letting the client select a proper version of
    method to call, delegate the choice to objects we're passing to visitor as 
    an argument. 
*/
#include <iostream>
#include <array>
class ConcreteComponentA;
class ConcreteComponentB;
class Visitor {
public:
    virtual void VisitConcreteComponentA(const ConcreteComponentA* element) const = 0;
    virtual void VisitConcreteComponentB(const ConcreteComponentB* element) const = 0;
};
class Component {
public:
    virtual ~Component() {}
    virtual void Accept(Visitor* visitor) const = 0;
};
class ConcreteComponentA : public Component {
public:
    void Accept(Visitor* visitor) const override {
        visitor->VisitConcreteComponentA(this);
    }
    std::string ExclusiveMethodOfConcreteComponentA() const {
        return "A";
    }
};
class ConcreteComponentB : public Component {
public:
    void Accept(Visitor* visitor) const override {
        visitor->VisitConcreteComponentB(this);
    }
    std::string ExclusiveMethodOfConcreteComponentB() const {
        return "B";
    }
};
class ConcreteVisitor1 : public Visitor {
public:
    void VisitConcreteComponentA(const ConcreteComponentA* element) const override {
        std::cout << element->ExclusiveMethodOfConcreteComponentA() << " + ConcreteVisitor1\n";
    }
    void VisitConcreteComponentB(const ConcreteComponentB* element) const override {
        std::cout << element->ExclusiveMethodOfConcreteComponentB() << " + ConcreteVisitor1\n";
    }
};
class ConcreteVisitor2 : public Visitor {
public:
    void VisitConcreteComponentA(const ConcreteComponentA* element) const override {
        std::cout << element->ExclusiveMethodOfConcreteComponentA() << " + ConcreteVisitor2\n";
    }
    void VisitConcreteComponentB(const ConcreteComponentB* element) const override {
        std::cout << element->ExclusiveMethodOfConcreteComponentB() << " + ConcreteVisitor2\n";
    }
};
void ClientCode(std::array<const Component*, 2> components, Visitor* visitor) {
    // ...
    for (const Component* comp : components) {
        comp->Accept(visitor);
    }
    // ...
}
int main() {
    std::array<const Component*, 2> components = {new ConcreteComponentA(), new ConcreteComponentB()};
    std::cout << "The Client code works with all visitors via the base Visitor interface.\n";
    ConcreteVisitor1* visitor1 = new ConcreteVisitor1();
    ClientCode(components, visitor1);
    std::cout << "\n";
    std::cout << "It allows the same client code to work with different types of visitors:\n";
    ConcreteVisitor2* visitor2 = new ConcreteVisitor2();
    ClientCode(components, visitor2);
    for (const Component* comp : components) {
        delete comp;
    }
    delete visitor1;
    delete visitor2;
    return 0;
}
