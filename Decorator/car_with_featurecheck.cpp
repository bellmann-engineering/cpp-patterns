#include <string>
#include <iostream>
using namespace std;

class Car // Our Abstract base class
{
        protected:
                string _str;
        public:
                Car()
                {
                        _str = "Unknown Car";
                }
 
                virtual string getDescription() const
                {       
                        return _str;
                }
 
                virtual double getCost() = 0;
 
                virtual ~Car()
                {
                        cout << "~Car()\n";
                }

                virtual bool hasFeature(const string& feature) = 0 ;
};
 
 
class Car3er : public Car
{       
        public:
                Car3er()
                {
                        _str = "CarModel1";
                }
                virtual double getCost() override
                {
                        return 31000.23;
                }
 
                ~Car3er()
                {
                        cout<<"~CarModel1()\n";
                }

                bool hasFeature(const string& feature)  override
                {
                    return false;
                }
};


class OptionsDecorator : public Car //Decorator Base class
{
        public:
                virtual string getDescription() = 0;
 
                virtual ~OptionsDecorator()
                {
                        cout<<"~OptionsDecorator()\n";
                }        
};
 
 
class Navigation: public OptionsDecorator
{
        private:
                Car* _b;
        public:
                Navigation(Car* b)
                {
                        _b = b;
                }
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
                        delete _b;
                }

                bool hasFeature(const string& feature) override
                {
                    if (feature == "Navigation")
                        return true;
                    else
                        return _b->hasFeature(feature);
                }
};
 
class PremiumSoundSystem: public OptionsDecorator
{
        private:
                Car* _b;
        public:
                PremiumSoundSystem(Car* b)
                {
                        _b = b;
                }
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
                        delete _b;
                }

                bool hasFeature(const string& feature) override
                {
                    if (feature == "PremiumSoundSystem")
                        return true;
                    else
                        return _b->hasFeature(feature);
                }
};
 
class ManualTransmission: public OptionsDecorator
{
        private:
                Car* _b;
        public:
                ManualTransmission(Car *b)
                {
                        _b = b;
                }

                string getDescription()
                {
		        return _b->getDescription()+ ", ManualTransmission";
                }
 
                double getCost()
                {
                        return 0.30 + _b->getCost();
                }

                ~ManualTransmission()
                {
                        cout << "~ManualTransmission()\n";
                        delete _b;
                }

                bool hasFeature(const string& feature) override
                {
                    if (feature == "ManualTransmission")
                        return true;
                    else
                        return _b->hasFeature(feature);
                }
};
 
int main()
{
        // create our Car that we want to buy
        Car* mein3er = new Car3er();

        cout << "Base model of " << mein3er->getDescription() << " costs $" << mein3er->getCost() << "\n";  
            
        // let's add some more features
            
        mein3er = new Navigation(mein3er);
        cout << mein3er->getDescription() << " will cost you $" << mein3er->getCost() << "\n";
        mein3er = new PremiumSoundSystem(mein3er);
        mein3er = new ManualTransmission(mein3er);
        cout << mein3er->getDescription() << " will cost you $" << mein3er->getCost() << "\n";

        if (mein3er->hasFeature("Navigation"))
            cout << "The car has Navigation" << "\n";

        delete mein3er;

        return 0;
}
