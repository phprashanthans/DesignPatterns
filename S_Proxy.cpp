// Proxy is a structural design pattern that lets you provide a substitute or placeholder for another object.
// A proxy controls access to the original object, allowing you to perform something (access control, caching etc.)
// either before or after the request gets through to the original object.
// A credit card is a proxy for a bank account, which is a proxy for a bundle of cash. 
// Both implement the same interface: they can be used for making a payment.

#include <iostream>

// The subject interface declares common operations for both RealSubject and the Proxy.
class Subject {
    public:
        virtual void Request() const = 0;
};
class RealSubject : public Subject {
    public:
        void Request() const override {
            std::cout << "RealSubject: Handling Request\n";
        }
};
// The Proxy has an interface identical to the RealSubject
class Proxy : public Subject {
    private:
        RealSubject* real_subject_;
        bool CheckAccess() const {
            std::cout << "Proxy: Checking access prior to firing a real request!\n";
            return true;
        }
        void LogAccess() const {
            std::cout << "Proxy: Logging the time of request!\n";
        }
    public:
        // The proxy maintains a refernece to an object of RealSubject Class. 
        // It can either be lazy-loaded or passed to the Proxy by the client.
        Proxy(RealSubject* real_subject) : real_subject_(new RealSubject(*real_subject)) {}
        ~Proxy() {
            delete real_subject_;
        }
        // The common application of Proxy pattern are lazy loading, caching,
        // controlling the access, logging etc.
        void Request() const override {
            if (this->CheckAccess()) {
                this->real_subject_->Request();
                this->LogAccess();
            }
        }
};
// Client code is supposed to work with all objects (subject and proxy)
void ClientCode(const Subject& subject) {
    subject.Request();
}

int main() {
    std::cout << "Client: Executing the client code with a real subject:\n";
    RealSubject* real_subject = new RealSubject();
    ClientCode(*real_subject);
    std::cout << "\n";
    std::cout << "Client: Executing the same client code with a proxy:\n";
    Proxy* proxy = new Proxy(real_subject);
    ClientCode(*proxy);
    delete real_subject;
    delete proxy;
    return 0;
}
