// Singleton : Creational Design Pattern
// It ensures that only one object of its kind exists and provides a
// single point of global access to it for any other code. The shared 
// resource could be a databse or a file. It protects that instance
// from being overriden by other code unlike global variables.

#include <iostream>
#include <thread>
#include <chrono>

class Singleton {
    private:
        static Singleton* singleton_;
        static std::mutex mutex_;
    protected:
        Singleton(const std::string value)
            : value_(value) {
        }
        ~Singleton() {}
        std::string value_;
    public:
        Singleton(Singleton& other) = delete;
        void operator=(const Singleton&) = delete;
        static Singleton* GetInstance(const std::string& value);
        void SomeBusinessLogic() {
            //-----
        }
        std::string GetValue() const {
            return value_;
        }
};
Singleton* Singleton::singleton_{nullptr};
std::mutex Singleton::mutex_;
Singleton* Singleton::GetInstance(const std::string& value) {
    std::lock_guard<std::mutex> lock(mutex_);
    if(singleton_ == nullptr) {
        singleton_ = new Singleton(value);
    }
    return singleton_;
}
void ThreadFoo() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::GetInstance("FOO");
    std::cout << singleton->GetValue() << "\n";
}
void ThreadBar() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::GetInstance("BAR");
    std::cout << singleton->GetValue() << "\n";
}

int main() {
    std::thread t1(ThreadFoo);
    std::thread t2(ThreadBar);
    t1.join();
    t2.join();
    // Output depends on mutex locks
    // If you see the same value, then singleton was reused (yay!)
    // If you see different values, then 2 singletons were created (booo!!)
    return 0;
}
