/* Decorator: Structural Design Pattern
It lets you attach new behaviours to objects by placing these objects inside
special wrapper objects that contain the behaviors. Alternate name for this 
pattern is wrapper pattern. It allows adding new behaviors to objects
dynamically. The wrapper and target object would have same type of interfaces.
*/

#include <iostream>

class Component {
    public:
        virtual ~Component() {}
        virtual std::string Operation() const = 0;
};
class ConcreteComponent : public Component {
    public:
        std::string Operation() const override {
            return "ConcreteComponent";
        }
};
class Decorator : public Component {
    protected:
        Component* component_;
    public:
        Decorator(Component* component) : component_(component) {
        }
        std::string Operation() const override {
            return this->component_->Operation();
        }
};
class ConcreteDecoratorA : public Decorator {
    public:
        ConcreteDecoratorA(Component* Component) :
            Decorator(Component) {}
        std::string Operation() const override {
            return "ConcreteDecoratorA(" + Decorator::Operation() + ")";
        }
};
class ConcreteDecoratorB : public Decorator {
    public:
        ConcreteDecoratorB(Component* Component) :
            Decorator(Component) {}
        std::string Operation() const override {
            return "ConcreteDecoratorB(" + Decorator::Operation() + ")";
        }
};
void ClientCode(Component* component) {
    std::cout << "Result:" << component->Operation();
}

int main() {
    Component* simple = new ConcreteComponent();
    std::cout << "Client: I have got a simple component:\n";
    ClientCode(simple);
    std::cout << "\n\n";

    Component* decorator1 = new ConcreteDecoratorA(simple);
    Component* decorator2 = new ConcreteDecoratorB(decorator1);
    std::cout << "Client: This is a decorated component:\n";
    ClientCode(decorator2);
    std::cout << "\n";

    delete simple;
    delete decorator1;
    delete decorator2;
    return 0;
}
