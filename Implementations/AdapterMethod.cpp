#include <iostream>
using namespace std;

class NewSystem {
public:
    virtual void newRequest() = 0; 
};

class OldSystem {
public:
    void oldRequest() {
        cout << "Old system request." << endl;
    }
};

class Adapter : public NewSystem {
private:
    OldSystem* oldSystem;

public:
    Adapter(OldSystem* oldSys) : oldSystem(oldSys) {}

    void newRequest() override {
        oldSystem->oldRequest(); 
    }
};

int main() {

    OldSystem* oldSystem = new OldSystem();

    NewSystem* newSystem = new Adapter(oldSystem);

    newSystem->newRequest();  


    delete oldSystem;
    delete newSystem;

}
