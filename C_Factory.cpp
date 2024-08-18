// Factory Design Pattern : The design pattern suggests that you replace direct object construction calls 
// (using the new operator) with calls to a special factory method. Objects are returned by the factory method
// The idea is that you can override the factory method in a subclass and change the class of products being 
// created by the method.
// One limitation is that subclasses may return different types of products only if these products have a 
// common base class or interface.

#include <iostream>

// Abstract Product Interface
class Product {
    public:
        virtual ~Product() {}
        virtual std::string operation() const = 0;
};
// Concrete Product implementing Abstarct Product
class ConcreteProduct1 : public Product {
    public:
        std::string operation() const override {
            return "{Result of operation from ConcreteProduct1}";
        }
};
class ConcreteProduct2 : public Product {
    public:
        std::string operation() const override {
            return "{Result of operation from ConcreteProduct2}";
        }
};
// Creator class : declares the factory method that is supposed to return 
// an object of a Product class
class Creator {
    public:
        virtual ~Creator() {}
        virtual Product* FactoryMethod() const = 0;
        std::string SomeOperation() const {
            Product* product = this->FactoryMethod();
            std::string result = "Creator: This is common Creator's code and ";
            result += product->operation();
            delete product;
            return result;
        }
};
class ConcreteCreator1 : public Creator {
    public:
        Product* FactoryMethod() const override {
            return new ConcreteProduct1();
        }
};
class ConcreteCreator2 : public Creator {
    public:
        Product* FactoryMethod() const override {
            return new ConcreteProduct2();
        }
};
void ClientCode(const Creator& creator) {
    //...
    std::cout << "Client calling: " << creator.SomeOperation() << std::endl;
    //...
}

int main() {
    std::cout << "App: Launced with ConcreteCreator1.\n";
    Creator* creator1 = new ConcreteCreator1();
    ClientCode(*creator1);
    std::cout << std::endl;

    std::cout << "App: Launced with ConcreteCreator2.\n";
    Creator* creator2 = new ConcreteCreator2();
    ClientCode(*creator2);
    std::cout << std::endl;

    delete creator1;
    delete creator2;
    return 0;
}
