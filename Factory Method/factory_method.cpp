#include <iostream>
#include <memory>

// Transport interface (base class)
class Transport {
public:
    virtual void deliver() const = 0;
    virtual ~Transport() = default;
};

// Truck class (implements Transport)
class Truck : public Transport {
public:
    void deliver() const override {
        std::cout << "Deliver by land in a truck.\n";
    }
};

// Ship class (implements Transport)
class Ship : public Transport {
public:
    void deliver() const override {
        std::cout << "Deliver by sea in a ship.\n";
    }
};

// Abstract Logistics class (factory method class)
class Logistics {
public:
    virtual std::unique_ptr<Transport> createTransport() const = 0;

    void planDelivery() const {
        auto transport = createTransport();
        transport->deliver();
    }

    virtual ~Logistics() = default;
};

// RoadLogistics class (implements Logistics)
class RoadLogistics : public Logistics {
public:
    std::unique_ptr<Transport> createTransport() const override {
        return std::make_unique<Truck>();
    }
};

// SeaLogistics class (implements Logistics)
class SeaLogistics : public Logistics {
public:
    std::unique_ptr<Transport> createTransport() const override {
        return std::make_unique<Ship>();
    }
};

// Main function
int main() {
    std::unique_ptr<Logistics> logistics;

    // Create road logistics
    logistics = std::make_unique<RoadLogistics>();
    logistics->planDelivery();

    // Create sea logistics
    logistics = std::make_unique<SeaLogistics>();
    logistics->planDelivery();

    return 0;
}
