/* Template: Behavioral Design Pattern
    It defines the skeleton of an algorithm in the superclass but let 
    subclasses override specific steps of the algorithm without changing
    its structure. It suggests that you break down an algorithm into a series
    of steps, turn these steps into methods and put a series of calls to these
    methods inside a single template method. The steps may either be abstract or 
    have some default implementation
*/
#include <iostream>
class AbstractClass {
public:
    void TemplateMethod() const {
        this->BaseOperation1();
        this->RequiredOperation1();
        this->BaseOperation2();
        this->Hook1();
        this->RequiredOperation2();
        this->BaseOperation3();
        this->Hook2();
    }
protected:
    // Base Operations already have their implementation
    void BaseOperation1() const {
        std::cout << "AbstractClass says: I am doing the bulk of the work\n";
    }
    void BaseOperation2() const {
        std::cout << "AbstractClass says: But I let subclasses override some operations\n";
    }
    void BaseOperation3() const {
        std::cout << "AbstractClass says: But I am doing the bulk of the work anyway\n";
    }
    // Required Operations have to be implemented in subclasses
    virtual void RequiredOperation1() const = 0;
    virtual void RequiredOperation2() const = 0;
    // Hooks may or may not be overridden by subclasses
    virtual void Hook1() const {};
    virtual void Hook2() const {};
};
class ConcreteClass1 : public AbstractClass {
protected:
    void RequiredOperation1() const override {
        std::cout << "ConcreteClass1 says: Implemented Operation1\n"; 
    }
    void RequiredOperation2() const override {
        std::cout << "ConcreteClass1 says: Implemented Operation2\n"; 
    }
};
class ConcreteClass2 : public AbstractClass {
protected:
    void RequiredOperation1() const override {
        std::cout << "ConcreteClass2 says: Implemented Operation1\n"; 
    }
    void RequiredOperation2() const override {
        std::cout << "ConcreteClass2 says: Implemented Operation2\n"; 
    }
    void Hook1() const override {
        std::cout << "ConcreteClass2 says: Overridden Hook1\n";
    }
};
void ClientCode(AbstractClass* class_) {
    //-----//
    class_->TemplateMethod();
    //-----//
}
int main() {
    std::cout << "Same Client code can work with different subclasses:\n";
    ConcreteClass1* concreteClass1 = new ConcreteClass1();
    ClientCode(concreteClass1);
    std::cout << "\n";
    std::cout << "Same Client code can work with different subclasses:\n";
    ConcreteClass2* concreteClass2 = new ConcreteClass2();
    ClientCode(concreteClass2);
    delete concreteClass1;
    delete concreteClass2;
    return 0;
}
