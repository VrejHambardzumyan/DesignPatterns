#include <iostream>
using namespace std;

class Singleton {
private:
    static Singleton* instance;

    Singleton() {
        cout << "Singleton instance created!" << endl;
    }

public:
    static Singleton* getInstance() {
        if (instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    }

    void showMessage() {
        cout << "Hello from Singleton!" << endl;
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};

Singleton* Singleton::instance = nullptr;

int main() {

    Singleton* singleton1 = Singleton::getInstance();
    singleton1->showMessage();

    Singleton* singleton2 = Singleton::getInstance();
    singleton2->showMessage();

    if (singleton1 == singleton2) {
        cout << "Both instances are the same!" << endl;
    }

}
