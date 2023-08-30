#include <iostream>

// a class containing only pure virtual methods ≙ interface
class ThermoInterface
{
    public:
        virtual double getTempC() = 0;
        virtual ~ThermoInterface() {}; // important to avoid memory leak by ThermoAdapter
};


class CelciusThermo : public ThermoInterface
{
    public:
        double getTempC() override
        {
            return -20;
        }
    
};

// Lecacy component
class FahrenheitThermo
{
    public:
        double getFahrenheitTemperature() 
        {
            return -4; // -4 °F should be -20° C
        }
    
};

class ThermoAdapter : public ThermoInterface
{
    private:
        FahrenheitThermo* thermo;
    public:
        ThermoAdapter() 
        {
            thermo = new FahrenheitThermo();
        }
        ~ThermoAdapter() 
        {
			if(thermo != nullptr)
			{
				delete thermo;
				thermo = nullptr;
			}
        }
        double getTempC() override
        {
            return (thermo->getFahrenheitTemperature()-32.0) * (5.0/9.0);
        }
};

int main()
{
    ThermoInterface* ti = new ThermoAdapter();
    std::cout << ti->getTempC() << std::endl;

    if(ti != nullptr)
    {
        delete ti;
        ti = nullptr;
    }
}
