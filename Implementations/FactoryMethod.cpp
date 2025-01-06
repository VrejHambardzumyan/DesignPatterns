#include <iostream>
#include <memory>

using namespace std;
class Pizza {
public:
    virtual void prepare() = 0;
    virtual void bake() = 0;
    virtual void cut() = 0;
    virtual void box() = 0;
    virtual ~Pizza() = default;
};


class CheesePizza : public Pizza {
public:
    void prepare() override {
        std::cout << "Preparing Cheese Pizza" << std::endl;
    }
    void bake() override {
        std::cout << "Baking Cheese Pizza" << std::endl;
    }
    void cut() override {
        std::cout << "Cutting Cheese Pizza" << std::endl;
    }
    void box() override {
        std::cout << "Boxing Cheese Pizza" << std::endl;
    }
};

class PepperoniPizza : public Pizza {
public:
    void prepare() override {
       cout << "Preparing Pepperoni Pizza" << endl;
    }
    void bake() override {
        cout << "Baking Pepperoni Pizza" << endl;
    }
    void cut() override {
        cout << "Cutting Pepperoni Pizza" << endl;
    }
    void box() override {
        cout << "Boxing Pepperoni Pizza" << endl;
    }
};


class PizzaStore {
public:
   
    virtual unique_ptr<Pizza> createPizza() = 0;


    unique_ptr<Pizza> orderPizza() {
        unique_ptr<Pizza> pizza = createPizza();
        
        pizza->prepare();
        pizza->bake();
        pizza->cut();
        pizza->box();
        
        return pizza;
    }

    virtual ~PizzaStore() = default;
};


class CheesePizzaStore : public PizzaStore {
public:
    unique_ptr<Pizza> createPizza() override {
        return make_unique<CheesePizza>();
    }
};

class PepperoniPizzaStore : public PizzaStore {
public:
    unique_ptr<Pizza> createPizza() override {
        return make_unique<PepperoniPizza>();
    }
};


int main() {

    unique_ptr<PizzaStore> cheesePizzaStore = make_unique<CheesePizzaStore>();
    unique_ptr<PizzaStore> pepperoniPizzaStore = make_unique<PepperoniPizzaStore>();

    cout << "Ordering from Cheese Pizza Store:" << endl;
    auto cheesePizza = cheesePizzaStore->orderPizza();

    cout << "\nOrdering from Pepperoni Pizza Store:" << endl;
    auto pepperoniPizza = pepperoniPizzaStore->orderPizza();

}