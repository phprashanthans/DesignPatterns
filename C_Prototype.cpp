// Prototype : Creational Design Pattern
// It allows you copy existing objects without making your code
// dependent on their classes. In general, Not all objects can be 
// copied because some of the object’s fields may be private and 
// not visible from outside of the object itself.
// The Prototype pattern delegates the cloning process to the 
// actual objects that are being cloned. 
// You craete a set of objects, configured in various ways. 
// When you need an object like the one you've configured, you just
// clone a prototype instead of constructing new object from scratch.

#include <iostream>
#include <unordered_map>

enum Type {
    PROTOTYPE_1,
    PROTOTYPE_2
};
// Abstract Prototype Interface
class Prototype {
    protected:
        std::string prototype_name_;
        float prototype_field_;
    public:
        Prototype() {}
        Prototype(std::string prototype_name) :
            prototype_name_(prototype_name) {
        }
        virtual ~Prototype() {}
        virtual Prototype* Clone() const = 0;
        virtual void Method(float prototype_field) {
            this->prototype_field_ = prototype_field;
            std::cout << "Call method from " << prototype_name_ 
            << " with field: " << prototype_field_ << std::endl;
        }
};
// Concrete Prototype Interface
class ConcretePrototype1 : public Prototype {
    private:
        float concrete_prototype_field_;
    public:
        ConcretePrototype1(std::string prototype_name, float concrete_prototype_field)
            : Prototype(prototype_name), concrete_prototype_field_(concrete_prototype_field) {
        }
        Prototype* Clone() const override {
            return new ConcretePrototype1(*this);
        }
};
class ConcretePrototype2 : public Prototype {
    private:
        float concrete_prototype_field_;
    public:
        ConcretePrototype2(std::string prototype_name, float concrete_prototype_field)
            : Prototype(prototype_name), concrete_prototype_field_(concrete_prototype_field) {
        }
        Prototype* Clone() const override {
            return new ConcretePrototype2(*this);
        }
};
// Prototype Factory
class PrototypeFactory {
    private:
        std::unordered_map<Type, Prototype*, std::hash<int>> prototypes_;
    public:
        PrototypeFactory() {
            prototypes_[Type::PROTOTYPE_1] = new ConcretePrototype1("PROTOTYPE_1", 50.0f);
            prototypes_[Type::PROTOTYPE_2] = new ConcretePrototype2("PROTOTYPE_2", 70.0f);
        }
        ~PrototypeFactory() {
            delete prototypes_[Type::PROTOTYPE_1];
            delete prototypes_[Type::PROTOTYPE_2];
        }
        Prototype* CreatePrototype(Type type) {
            return prototypes_[type]->Clone();
        }
};
void ClientCode(PrototypeFactory& prototype_factory) {
    std::cout << "Let's Create a Prototype1:\n";
    Prototype* prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_1);
    prototype->Method(90);
    delete prototype;
    std::cout << "\n";
    std::cout << "Let's Create a Prototype2:\n";
    prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_2);
    prototype->Method(10);
    delete prototype;
}

int main() {
    PrototypeFactory* prototype_factory = new PrototypeFactory();
    ClientCode(*prototype_factory);
    delete prototype_factory;
    return 0;
}
