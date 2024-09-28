/* Observer: Behavourial Design Pattern
    This lets you define a subscription mechanism to notify multiple objects
    about any events that happen to the object they're observing. 
    The object that has some interesting state is often called a subject, also
    can be referred as publisher. All other objects that want to track changes 
    to the publisher's stae are called subscribers.
*/
#include <iostream>
#include <list>
#include <string>

class IObserver {
public:
    virtual ~IObserver() {}
    virtual void Update(const std::string& message_from_subject) = 0;
};
class ISubject {
public:
    virtual ~ISubject() {}
    virtual void Attach(IObserver* observer) = 0;
    virtual void Detach(IObserver* observer) = 0;
    virtual void Notify() = 0;
};
class Subject : public ISubject {
public:
    virtual ~Subject() {
        std::cout << "GoodBye, I was the Subject.\n";
    }
    void Attach(IObserver* observer) override {
        list_observer_.push_back(observer);
    }
    void Detach(IObserver* observer) override {
        list_observer_.remove(observer);
    }
    void Notify() override {
        std::list<IObserver*>::iterator itr = list_observer_.begin();
        std::cout << "There are " << list_observer_.size() << " observers in the list.\n";
        while(itr != list_observer_.end()) {
            (*itr)->Update(message_);
            itr++;
        }
    }
    void CreateMessage(std::string message = "EMPTY") {
        this->message_ = message;
        Notify();
    }
    void SomeBusinessLogic() {
        this->message_ = "change message message";
        Notify();
        std::cout << "I am about to do something important\n";
    }
private:
    std::list<IObserver*> list_observer_;
    std::string message_;
};
class Observer : public IObserver {
public:
    Observer(Subject& subject) : subject_(subject) {
        this->subject_.Attach(this);
        std::cout << "Hi, I am the observer \"" << ++Observer::static_number_ << "\".\n";
        this->number_ = Observer::static_number_;
    }
    virtual ~Observer() {
        std::cout << "Goodbye, I was the Observer \"" << this->number_ << "\".\n";
    }
    void Update(const std::string& message_from_subject) override {
        message_from_subject_ = message_from_subject;
        PrintInfo();
    }
    void RemoveMefromList() {
        subject_.Detach(this);
        std::cout << "Observer \"" << number_ << "\" removed from the list.\n";
    }
    void PrintInfo() {
        std::cout << "Observer \"" << this->number_ << "\": a message is available --> "
                  << this->message_from_subject_ << "\n";
    }
private:
    Subject& subject_;
    static int static_number_;
    int number_;
    std::string message_from_subject_;
};
int Observer::static_number_ = 0;
void ClientCode() {
    Subject* subject = new Subject();
    Observer* observer1 = new Observer(*subject);
    Observer* observer2 = new Observer(*subject);
    Observer* observer3 = new Observer(*subject);
    Observer* observer4;
    Observer* observer5;

    subject->CreateMessage("Hello World! :D");
    observer3->RemoveMefromList();
    subject->CreateMessage("The weather is hot today! :P");
    observer4 = new Observer(*subject);
    observer2->RemoveMefromList();
    observer5 = new Observer(*subject);
    subject->CreateMessage("My new car is great! ;)");
    observer5->RemoveMefromList();
    observer4->RemoveMefromList();
    observer1->RemoveMefromList();

    delete observer5;
    delete observer4;
    delete observer3;
    delete observer2;
    delete observer1;
    delete subject;
}
int main() {
    ClientCode();
    return 0;
}
