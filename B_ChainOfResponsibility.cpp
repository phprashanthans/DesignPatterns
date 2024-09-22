/* Chain Of Responsibility: Behavourial Design Pattern
    This lets you pass requests along a chain of handlers. Upon receiving a request,
    each handler decides either to process the request or to pass it to the next 
    handler in the chain. 
    COR relies on transforming particular behaviors into stand-alone objects called 
    handlers. The pattern suggests that you link these handlers into a chain. Each 
    linked handler has a field for storing a reference to the next handler in chain.
    The request travels along the chain until all handlers have had a chance to 
    process it. The handler can decide not to pass the request further down the chain
    and effectively stop any further processing.
*/

#include <iostream>
#include <vector>

// The Handler interface declares a method for building the chain of handlers.
// It also declares a method of executing a request.
class Handler {
public:
    virtual Handler* SetNext(Handler* handler) = 0;
    virtual std::string Handle(std::string request) = 0;
};
// Default behavior can be implemented inside an abstract handler
class AbstractHandler : public Handler {
private:
    Handler* next_handler_;
public:
    AbstractHandler() : next_handler_(nullptr) {}
    Handler* SetNext(Handler* handler) override {
        this->next_handler_ = handler;
        return handler;
    }
    std::string Handle(std::string request) override {
        if(this->next_handler_) {
            return this->next_handler_->Handle(request);
        }
        return {};
    }
};
// Concrete Handlers
class MonkeyHandler : public AbstractHandler {
public:
    std::string Handle(std::string request) override {
        if(request == "Banana") {
            return "Monkey: I'll eat the " + request + ".\n";
        } else {
            return AbstractHandler::Handle(request);
        }
    }
};
class SquirrelHandler : public AbstractHandler {
public:
    std::string Handle(std::string request) override {
        if(request == "Nut") {
            return "Squirrel: I'll eat the " + request + ".\n";
        } else {
            return AbstractHandler::Handle(request);
        }
    }
};
class DogHandler : public AbstractHandler {
public:
    std::string Handle(std::string request) override {
        if(request == "MeatBall") {
            return "Dog: I'll eat the " + request + ".\n";
        } else {
            return AbstractHandler::Handle(request);
        }
    }
};
void ClientCode(Handler& handler) {
    std::vector<std::string> food = {"Nut", "Banana", "Cup of coffee"};
    for (const std::string& f : food) {
        std::cout << "Client: Who wants a " << f << "?\n";
        const std::string result = handler.Handle(f);
        if(!result.empty()) {
            std::cout << " " << result;
        } else {
            std::cout << " " << f << " was left untouched.\n";
        }
    }
}
int main() {
    MonkeyHandler* monkey = new MonkeyHandler();
    SquirrelHandler* squirrel = new SquirrelHandler();
    DogHandler* dog = new DogHandler();
    monkey->SetNext(squirrel)->SetNext(dog);

    std::cout << "Chain: Monkey > Squirrel > Dog\n\n";
    ClientCode(*monkey);
    std::cout << "\n";
    std::cout << "SubChain: Squirrel > Dog\n\n";
    ClientCode(*squirrel);

    delete monkey;
    delete squirrel;
    delete dog;
    return 0;
}
