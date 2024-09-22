/* Command : Behavorial Design Pattern
    It converts a request into a stand-alone object that contains all information about the request.
    The conversion allows deferred or remote execution of commands, storing command, history etc.
    Also used for queuing tasks, tracking operations history etc.
*/

#include <iostream>
#include <vector>

// Interface declaring a method for executing a command
class Command {
public:
    virtual ~Command() {}
    virtual void Execute() const = 0;
};
// Actual Commands, could be simple or complex
class SimpleCommand : public Command {
private:
    std::string pay_load_;
public:
    explicit SimpleCommand(std::string pay_load) : pay_load_(pay_load) {}
    void Execute() const override {
        std::cout << "SimpleCommand: See, I can do simple things like printing (" << this->pay_load_ << ")\n";
    }
};
// Receiver classes contain some important business logic. They know how to
// perform all kinds of operations, associated with carrying out a request.
// Analogus to any electronic device.
class Receiver {
public:
    void DoSomething(const std::string& a) {
        std::cout << "Receiver: Working on (" << a << ".)\n";
    }
    void DoSomethingElse(const std::string& b) {
        std::cout << "Receiver: Also working on (" << b << ".)\n";
    }
};
// Complex commands can delegate operations to other objects like receivers.
class ComplexCommand : public Command {
private:
    Receiver* receiver_;
    std::string a_;
    std::string b_;
public:
    ComplexCommand(Receiver* receiver, std::string a, std::string b) :
        receiver_(receiver), a_(a), b_(b) {}
    void Execute() const override {
        std::cout << "ComplexCommand: Complex stuff should be done by a receiver object.\n";
        this->receiver_->DoSomething(this->a_);
        this->receiver_->DoSomethingElse(this->b_);
    }
};
// Invoker is associated with one or several commands. It sends a request to command;
class Invoker {
private:
    Command* on_start_;
    Command* on_finish_;
public:
    ~Invoker() {
        delete on_start_;
        delete on_finish_;
    }
    void SetOnStart(Command* command) {
        this->on_start_ = command;
    }
    void SetOnFinish(Command* command) {
        this->on_finish_ = command;
    }
    // The invoker doesn't depend on concrete command or receiver classes. The 
    // invoker passes a request to a receiver indirectly, by executing a command.
    void DoSomethingImportant() {
        std::cout << "Invoker: Does anybody want something done before I begin?\n";
        if(this->on_start_) {
            this->on_start_->Execute();
        }
        std::cout << "Invoker: ...doing something really important...\n";
        std::cout << "Invoker: Does anybody want really something done before I finish?\n";
        if(this->on_finish_) {
            this->on_finish_->Execute();
        }
    }
};
int main() {
    Invoker* invoker = new Invoker();
    invoker->SetOnStart(new SimpleCommand("Say Hi!"));
    Receiver* receiver = new Receiver();
    invoker->SetOnFinish(new ComplexCommand(receiver, "Send Email", "Save Report"));
    invoker->DoSomethingImportant();

    delete invoker;
    delete receiver;
    return 0;
}
