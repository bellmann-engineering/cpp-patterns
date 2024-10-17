#include <iostream>
#include <string>

// Car parts
class Wheel {
private:
    int size;
public:
    Wheel(int s) : size(s) {}

    int getSize() {
        return size;
    }
};

class Engine {
private:
    int ps;
public:
    Engine(int p) : ps(p) {}

    int getPs() {
        return ps;
    }
};

class Body {
private:
    std::string shape;
public:
    Body(std::string s) : shape(s) {}

    std::string getShape() {
        return shape;
    }
};

// Final product -- a car 
class Car {
private:
    Wheel* wheels[4];
    Engine* engine;
    Body* body;
public: 
    void setWheel(Wheel* ws, int index) {
        wheels[index] = ws;
    }
    void setEngine(Engine* e) {
        engine = e;
    }
    void setBody(Body* b) {
        body = b;
    }
    
    void display() {
        std::cout << "Body: " << body->getShape() << std::endl;
        std::cout << "Engine (PS): " << engine->getPs() << std::endl;
        std::cout << "Tire size: " << wheels[0]->getSize() << "'" << std::endl;
    }
};

// Builder Interface
class Builder {
public:
    virtual Wheel* buildWheel() = 0;
    virtual Engine* buildEngine() = 0;
    virtual Body* buildBody() = 0;

    // The Builder returns the constructed Car instead of the Director
    virtual Car* getCar() = 0;
};

// Concrete Builder for SUV cars 
class SUVBuilder : public Builder {
private:
    Car* car;

public:
    SUVBuilder() {
        car = new Car();
    }

    ~SUVBuilder() {
        delete car;
    }

    Wheel* buildWheel() override {
        Wheel* wheel = new Wheel(22);
        for (int i = 0; i < 4; i++) {
            car->setWheel(wheel, i);
        }
        return wheel;
    }

    Engine* buildEngine() override {
        Engine* engine = new Engine(400);
        car->setEngine(engine);
        return engine;
    }

    Body* buildBody() override {
        Body* body = new Body("SUV");
        car->setBody(body);
        return body;
    }

    Car* getCar() override {
        return car;
    }
};

// Concrete Builder for City cars 
class CityCarBuilder : public Builder {
private:
    Car* car;

public:
    CityCarBuilder() {
        car = new Car();
    }

    ~CityCarBuilder() {
        delete car;
    }

    Wheel* buildWheel() override {
        Wheel* wheel = new Wheel(16);
        for (int i = 0; i < 4; i++) {
            car->setWheel(wheel, i);
        }
        return wheel;
    }

    Engine* buildEngine() override {
        Engine* engine = new Engine(85);
        car->setEngine(engine);
        return engine;
    }

    Body* buildBody() override {
        Body* body = new Body("Hatchback");
        car->setBody(body);
        return body;
    }

    Car* getCar() override {
        return car;
    }
};

int main() {
    // Concrete builders
    SUVBuilder suvBuilder;
    CityCarBuilder ccBuilder;

    // Build an SUV
    std::cout << "SUV" << std::endl;
    suvBuilder.buildBody();
    suvBuilder.buildEngine();
    suvBuilder.buildWheel();
    Car* car1 = suvBuilder.getCar();
    car1->display();

    std::cout << std::endl;

    // Build a City Car
    std::cout << "City Car" << std::endl;
    ccBuilder.buildBody();
    ccBuilder.buildEngine();
    ccBuilder.buildWheel();
    Car* car2 = ccBuilder.getCar();
    car2->display();

    // Clean up
    delete car1;
    delete car2;

    return 0;
}
