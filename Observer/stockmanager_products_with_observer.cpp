#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

// Forward declaration of Observer interface
class Observer;

// Subject interface
class Subject {
public:
    virtual ~Subject() {}
    virtual void registerObserver(Observer* observer) = 0;
    virtual void removeObserver(Observer* observer) = 0;
    virtual void notifyObservers(const std::string& productName) = 0;
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

    void notifyObservers(const std::string& productName) override {
        for (Observer* observer : observers) {
            observer->update(productName); // Notify with product name
        }
    }

    void setStockStatus(bool inStock, const std::string& productName) {
        if (productInStock != inStock) {
            productInStock = inStock;
            notifyObservers(productName);
        }
    }
};

// Concrete Observer class
class Customer : public Observer {
private:
    std::string name;
    std::unordered_set<std::string> interests; // Products customer is interested in

public:
    Customer(const std::string& name) : name(name) {}

    // Add interest in a product
    void addInterest(const std::string& productName) {
        interests.insert(productName);
    }

    // Update method checks if the notification is for an interested product
    void update(const std::string& productName) override {
        if (interests.find(productName) != interests.end()) {
            std::cout << "Notification for " << name << ": " << productName << " is back in stock!" << std::endl;
        }
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

    // Set interests for customers
    customer1.addInterest("Product A");
    customer2.addInterest("Product B");

    // Notify observers when product is back in stock
    stockManager.setStockStatus(true, "Product A");
    stockManager.setStockStatus(true, "Product B");

    return 0;
}
