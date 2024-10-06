/* Strategy: Behavorial Design Pattern
    This lets you define a family of algorithms, put each of them into a separate 
    class, and make their objects intercahngeable. It suggests that you take a class 
    that does something specific in a lot of different ways and extract all of these 
    algorithms into separate classes called strategies. 
    The original class, called context, must have a field for storing a reference to
    one of the strategies. The context delegates the work to linked strategy object.
    The client passes the desired strategy to the context. This way context becomes
    independent of concrete strategies, so you can add new algorithms or modify 
    existing ones without changing the code of context or other strategies.
*/

#include <iostream>
#include <algorithm>
#include <string_view>
#include <memory>

class Strategy {
public:
    virtual ~Strategy() = default;
    virtual std::string doAlgorithm(std::string_view data) const = 0;
};
class Context {
private:
    std::unique_ptr<Strategy> strategy_;
public:
    explicit Context(std::unique_ptr<Strategy> &&strategy = {}) : strategy_(std::move(strategy)) {}
    void setStrategy(std::unique_ptr<Strategy> && strategy) {
        strategy_ = std::move(strategy);
    }
    void doSomeBusinessLogic() const {
        if(strategy_) {
            std::cout << "Context: Sorting data using the strategy\n";
            std::string result = strategy_->doAlgorithm("aecbd");
            std::cout << result << "\n";
        } else {
            std::cout << "Context: Strategy isn't set\n"; 
        }
    }
};
class ConcreteStrategyA: public Strategy {
public:
    std::string doAlgorithm(std::string_view data) const override {
        std::string result(data);
        std::sort(std::begin(result), std::end(result));
        return result;
    }
};
class ConcreteStrategyB: public Strategy {
public:
    std::string doAlgorithm(std::string_view data) const override {
        std::string result(data);
        std::sort(std::begin(result), std::end(result), std::greater<>());
        return result;
    }
};
void ClientCode() {
    Context context(std::make_unique<ConcreteStrategyA>());
    std::cout << "Client: Strategy is set to normal sorting.\n";
    context.doSomeBusinessLogic();
    std::cout << "\n";
    std::cout << "Client: Strategy is set to reverse sorting.\n";
    context.setStrategy(std::make_unique<ConcreteStrategyB>());
    context.doSomeBusinessLogic();
}
int main() {
    ClientCode();
    return 0;
}
