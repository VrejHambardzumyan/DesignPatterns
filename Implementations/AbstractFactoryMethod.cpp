#include <iostream>
#include <memory>
using namespace std;

class Button {
public:
    virtual void paint() = 0;
    virtual ~Button() = default;
};

class Checkbox {
public:
    virtual void paint() = 0;
    virtual ~Checkbox() = default;
};

class WindowsButton : public Button {
public:
    void paint() override {
        cout << "Rendering a Windows-style button" << endl;
    }
};

class WindowsCheckbox : public Checkbox {
public:
    void paint() override {
        cout << "Rendering a Windows-style checkbox" << endl;
    }
};


class MacOSButton : public Button {
public:
    void paint() override {
        cout << "Rendering a MacOS-style button" << endl;
    }
};

class MacOSCheckbox : public Checkbox {
public:
    void paint() override {
        cout << "Rendering a MacOS-style checkbox" << endl;
    }
};


class GUIFactory {
public:
    virtual unique_ptr<Button> createButton() = 0;
    virtual unique_ptr<Checkbox> createCheckbox() = 0;
    virtual ~GUIFactory() = default;
};


class WindowsFactory : public GUIFactory {
public:
    unique_ptr<Button> createButton() override {
        return make_unique<WindowsButton>();
    }

    unique_ptr<Checkbox> createCheckbox() override {
        return make_unique<WindowsCheckbox>();
    }
};

class MacOSFactory : public GUIFactory {
public:
    unique_ptr<Button> createButton() override {
        return make_unique<MacOSButton>();
    }

    unique_ptr<Checkbox> createCheckbox() override {
        return make_unique<MacOSCheckbox>();
    }
};

class Application {
private:
    unique_ptr<Button> button;
    unique_ptr<Checkbox> checkbox;

public:
    void createUI(GUIFactory& factory) {
        
        button = factory.createButton();
        checkbox = factory.createCheckbox();
    }

    void paint() {
        if (button) button->paint();
        if (checkbox) checkbox->paint();
    }
};

unique_ptr<GUIFactory> createOSSpecificFactory(const string& osType) {
    if (osType == "Windows") {
        return make_unique<WindowsFactory>();
    } else if (osType == "MacOS") {
        return make_unique<MacOSFactory>();
    }
    throw runtime_error("Unsupported operating system");
}

int main() {
    
    string currentOS[] = {"Windows", "MacOS"};

    for (const auto& os : currentOS) {
        cout << "Creating UI for " << os << " environment:" << endl;
        
        auto factory = createOSSpecificFactory(os);

        Application app;
        app.createUI(*factory);
        app.paint();
        
        cout << endl;
    }
}