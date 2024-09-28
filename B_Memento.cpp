/* Memento: Behavioural Design Pattern
    This lets you save and restore the previous state of an object without revealing the
    details of its implementation. This pattern delegates creating the state snapshots to
    the actual owner of that state, the originator object. The pattern suggests storing 
    the copy of objects's state in a special object called memento. The contents of memento
    aren't acessible to any other object except the one who produced it. Caretakers are the 
    objects that store mementos, works with it only via limited interface.
*/
#include <iostream>
#include <vector>
#include <time.h>

class Memento {
public:
    virtual ~Memento() {}
    virtual std::string GetName() const = 0;
    virtual std::string date() const = 0;
    virtual std::string state() const = 0;
};
class ConcreteMemento : public Memento {
private:
    std::string state_;
    std::string date_;
public:
    ConcreteMemento(std::string state) : state_(state) {
        std::time_t now = std::time(0);
        this->date_ = std::ctime(&now);
    }
    std::string state() const override {
        return this->state_;
    }
    std::string date() const override {
        return this->date_;
    }
    std::string GetName() const override {
        return this->date_ + " / (" + this->state_.substr(0, 9) + "...)";
    }
};
class Originator {
private:
    std::string state_;
    std::string GenerateRandomString(int length = 10) {
        const char alphanum[] = 
            "012345678"
            "abcdefghijklmnopqrstuvwxyz"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        int stringLength = sizeof(alphanum) - 1;
        std::string random_string;
        for (int i=0; i<length; i++) {
            random_string += alphanum[std::rand() % stringLength];
        }
        return random_string;
    }
public:
    Originator(std::string state) : state_(state) {
        std::cout << "Originator: My initial state is: " << this->state_ << "\n"; 
    }
    void DoSomething() {
        std::cout << "Originator: I'm doing something important.\n";
        this->state_ = this->GenerateRandomString(30);
        std::cout << "Originator: and my state has changed to: " << this->state_ << "\n";
    }
    Memento* Save() {
        return new ConcreteMemento(this->state_);
    }
    void Restore(Memento* memento) {
        this->state_ = memento->state();
        std::cout << "Originator: My state has changed to: " << this->state_ << "\n";
    }
};
class Caretaker {
private:
    std::vector<Memento*> mementos_;
    Originator* originator_;
public:
    Caretaker(Originator* originator) : originator_(originator) {}
    ~Caretaker() {
        for(auto m : mementos_)
            delete m;
    }
    void Backup() {
        std::cout << "\nCaretaker: Saving Originator's state...\n";
        this->mementos_.push_back(this->originator_->Save());
    }
    void Undo() {
        if(!this->mementos_.size())
            return;
        Memento* memento = this->mementos_.back();
        this->mementos_.pop_back();
        std::cout << "Caretaker: Restoring state to: " << memento->GetName() << "\n";
        try {
            this->originator_->Restore(memento);
        } catch (...) {
            this->Undo();
        }
    }
    void ShowHistory() const {
        std::cout << "Caretaker: Here's the list of mementos:\n";
        for (Memento* memento : this->mementos_) {
            std::cout << memento->GetName() << "\n";
        }
    }
};
void ClientCode() {
    Originator* originator = new Originator("Super-duper-super-puper-super.");
    Caretaker* caretaker = new Caretaker(originator);
    caretaker->Backup();
    originator->DoSomething();
    caretaker->Backup();
    originator->DoSomething();
    caretaker->Backup();
    originator->DoSomething();
    std::cout << "\n";
    caretaker->ShowHistory();
    std::cout << "\nClient: Now, let's rollback!\n\n";
    caretaker->Undo();
    std::cout << "\nClient: Once more!\n\n";
    caretaker->Undo();

    delete originator;
    delete caretaker;
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(NULL)));
    ClientCode();
    return 0;
}
