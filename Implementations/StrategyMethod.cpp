#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class DiscountStrategy {
public:
    virtual double applyDiscount(double price) = 0;  
};

class RegularCustomerDiscount : public DiscountStrategy {
public:
    double applyDiscount(double price) override {
        return price * 0.90; 
    }
};

class VIPCustomerDiscount : public DiscountStrategy {
public:
    double applyDiscount(double price) override {
        return price * 0.80; 
    }
};

class NoDiscount : public DiscountStrategy {
public:
    double applyDiscount(double price) override {
        return price; 
    }
};

class Store {
private:
    unique_ptr<DiscountStrategy> discountStrategy; 

public:
    void setDiscountStrategy(unique_ptr<DiscountStrategy> strategy) {
        discountStrategy = move(strategy);
    }

    double calculateFinalPrice(double price) {
        return discountStrategy->applyDiscount(price);
    }
};

int main() {
    Store store;

    store.setDiscountStrategy(make_unique<RegularCustomerDiscount>());
    cout << "Regular Customer Price: $" << store.calculateFinalPrice(100.0) << endl;  

    store.setDiscountStrategy(make_unique<VIPCustomerDiscount>());
    cout << "VIP Customer Price: $" << store.calculateFinalPrice(100.0) << endl; 
    store.setDiscountStrategy(make_unique<NoDiscount>());
    cout << "No Discount Price: $" << store.calculateFinalPrice(100.0) << endl;  

}
