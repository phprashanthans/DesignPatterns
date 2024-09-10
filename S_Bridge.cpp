// Bridge : Structural Design Pattern
// It lets you split a large class or a set of closely related classes
// into two different hierarchies , "abstraction and implementation"
// which can be developed independently of each other 
// One of the hierarchy is called Abstraction will get a refernece 
// to an object of the second hierarchy (Implementation).

#include <iostream>

class Implementation {
    public:
        virtual ~Implementation() {}
        virtual std::string Operation() const = 0;
};
class ConcreteImplementationA : public Implementation {
    public:
        std::string Operation() const override {
            return "ConcreteImplementationA: Here's the result on the platform A.\n";
        }
};
class ConcreteImplementationB : public Implementation {
    public:
        std::string Operation() const override {
            return "ConcreteImplementationB: Here's the result on the platform B.\n";
        }
};
class Abstraction {
    protected:
        Implementation* implementation_;
    public:
        Abstraction(Implementation* implementation) :
            implementation_(implementation) {
        }
        virtual ~Abstraction() {}
        virtual std::string Operation() const {
            return "Abstraction: Base operation with:\n" +
                this->implementation_->Operation();
        }
};
class ExtendedAbstraction : public Abstraction {
    public:
        ExtendedAbstraction(Implementation* implementation) :
            Abstraction(implementation) {
        }
        std::string Operation() const override {
            return "ExtendedAbstraction: Extended operation with\n" +
                this->implementation_->Operation();
        }
};
void ClientCode(const Abstraction& abstraction) {
    std::cout << abstraction.Operation();
}

int main() {
    Implementation* implementation = new ConcreteImplementationA();
    Abstraction* abstraction = new Abstraction(implementation);
    ClientCode(*abstraction);
    std::cout << std::endl;
    delete implementation;
    delete abstraction;

    implementation = new ConcreteImplementationB();
    abstraction = new ExtendedAbstraction(implementation);
    ClientCode(*abstraction);
    delete implementation;
    delete abstraction;
    
    return 0;
}
