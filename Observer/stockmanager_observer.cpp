#include <iostream>
#include <vector>
#include <string>

// Forward declaration of Observer interface
class Observer;

// Subject interface
class Subject {
public:
    virtual ~Subject() {}
    virtual void registerObserver(Observer* observer) = 0;
    virtual void removeObserver(Observer* observer) = 0;
    virtual void notifyObservers() = 0;
};

// Observer interface
class Observer {
public:
    virtual ~Observer() {}
    virtual void update(const std::string& productName) = 0;
};

// Concrete Subject class
class StockManager : public Subject {
private:
    std::vector<Observer*> observers;
    bool productInStock;

public:
    StockManager() : productInStock(false) {}

    void registerObserver(Observer* observer) override {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) override {
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end()) {
            observers.erase(it);
        }
    }

    void notifyObservers() override {
        for (Observer* observer : observers) {
            observer->update("Product A"); // Notify with product name
        }
    }

    void setStockStatus(bool inStock) {
        if (productInStock != inStock) {
            productInStock = inStock;
            notifyObservers();
        }
    }
};

// Concrete Observer class
class Customer : public Observer {
private:
    std::string name;

public:
    Customer(const std::string& name) : name(name) {}

    void update(const std::string& productName) override {
        std::cout << "Notification for " << name << ": " << productName << " is back in stock!" << std::endl;
    }
};

int main() {
    // Create subject
    StockManager stockManager;

    // Create observers (customers)
    Customer customer1("Customer 1");
    Customer customer2("Customer 2");

    // Register observers
    stockManager.registerObserver(&customer1);
    stockManager.registerObserver(&customer2);

    // Notify observers when product is back in stock
    stockManager.setStockStatus(true);

    return 0;
}
