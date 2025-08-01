#include <iostream>
#include <vector>
#include <memory>
using namespace std;

// Forward declaration
class Observer;

// Subject interface
class Subject {
public:
    virtual void addObserver(shared_ptr<Observer> observer) = 0;
    virtual void removeObserver(shared_ptr<Observer> observer) = 0;
    virtual void notifyObservers() = 0;
    virtual ~Subject() = default;
};

// Observer interface
class Observer {
public:
    virtual void update(float temperature, float humidity) = 0;
    virtual ~Observer() = default;
};

// Concrete Subject: WeatherStation
class WeatherStation : public Subject {
private:
    vector<shared_ptr<Observer>> observers;
    float temperature = 0.0f;
    float humidity = 0.0f;

public:
    void setMeasurements(float temp, float hum) {
        temperature = temp;
        humidity = hum;
        notifyObservers();
    }

    void addObserver(shared_ptr<Observer> observer) override {
        observers.push_back(observer);
    }

    void removeObserver(shared_ptr<Observer> observer) override {
        observers.erase(
            remove(observers.begin(), observers.end(), observer),
            observers.end()
        );
    }

    void notifyObservers() override {
        for (const auto& obs : observers) {
            obs->update(temperature, humidity);
        }
    }
};

// Concrete Observer: Display
class Display : public Observer {
public:
    void update(float temperature, float humidity) override {
        cout << "[Display] Temperature: " << temperature
             << "°C, Humidity: " << humidity << "%\n";
    }
};

// Concrete Observer: Logger
class Logger : public Observer {
public:
    void update(float temperature, float humidity) override {
        cout << "[Logger] Weather update - Temp: " << temperature
             << "°C, Hum: " << humidity << "%\n";
    }
};

int main() {
    auto station = make_shared<WeatherStation>();
    auto display = make_shared<Display>();
    auto logger = make_shared<Logger>();

    station->addObserver(display);
    station->addObserver(logger);

    station->setMeasurements(22.5f, 60.0f);
    station->setMeasurements(24.0f, 55.0f);

    return 0;
}
