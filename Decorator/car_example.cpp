#include <string>
#include <iostream>
using namespace std;

class Car // Abstract base class
{
public:
    virtual string getDescription() = 0; // pure virtual function for description
    virtual double getCost() = 0;        // pure virtual function for cost

    virtual ~Car()
    {
        cout << "~Car()\n";
    }
};

class OptionsDecorator : public Car // Decorator Base class
{
protected:
    Car *_b;  // pointer to the wrapped car
public:
    OptionsDecorator(Car *b) : _b(b) {}  // associate OptionsDecorator with a Car

    virtual string getDescription() = 0;

    virtual ~OptionsDecorator()
    {
        cout << "~OptionsDecorator()\n";
        delete _b;  // safely delete the wrapped car
    }
};

class CarModel1 : public Car
{       
public:
    string getDescription()
    {
        return "CarModel1";
    }

    double getCost()
    {
        return 31000.23;
    }

    ~CarModel1()
    {
        cout << "~CarModel1()\n";
    }
};

class Navigation : public OptionsDecorator
{
public:
    Navigation(Car *b) : OptionsDecorator(b) {}  // initialize with the Car pointer

    string getDescription()
    {
        return _b->getDescription() + ", Navigation";
    }

    double getCost()
    {
        return 300.56 + _b->getCost();
    }

    ~Navigation()
    {
        cout << "~Navigation()\n";
    }
};

class PremiumSoundSystem : public OptionsDecorator
{
public:
    PremiumSoundSystem(Car *b) : OptionsDecorator(b) {}  // initialize with the Car pointer

    string getDescription()
    {
        return _b->getDescription() + ", PremiumSoundSystem";
    }

    double getCost()
    {
        return 0.30 + _b->getCost();
    }

    ~PremiumSoundSystem()
    {
        cout << "~PremiumSoundSystem()\n";
    }
};

class ManualTransmission : public OptionsDecorator
{
public:
    ManualTransmission(Car *b) : OptionsDecorator(b) {}  // initialize with the Car pointer

    string getDescription()
    {
        return _b->getDescription() + ", ManualTransmission";
    }

    double getCost()
    {
        return 0.30 + _b->getCost();
    }

    ~ManualTransmission()
    {
        cout << "~ManualTransmission()\n";
    }
};

int main()
{
    // create our Car that we want to buy
    Car *b = new CarModel1();

    cout << "Base model of " << b->getDescription() << " costs $" << b->getCost() << "\n";  
        
    // let's add some more features
    b = new Navigation(b);
    cout << b->getDescription() << " will cost you $" << b->getCost() << "\n";
    
    b = new PremiumSoundSystem(b);
    b = new ManualTransmission(b);
    cout << b->getDescription() << " will cost you $" << b->getCost() << "\n";

    delete b;

    return 0;
}
