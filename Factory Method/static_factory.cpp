#include <iostream>
#include <sstream>
#include <string>

class GPS {
private:
    double latitude;
    double longitude;

    // Private constructor
    GPS(double lat, double lng) : latitude(lat), longitude(lng) {}

public:
    // Static factory method to create a GPS object from a string
    static GPS fromString(const std::string& coordinates) {
        double lat, lng;
        char delimiter;

        std::istringstream stream(coordinates);

        // Assuming the format is "lat,lng" (e.g., ""49.4521,11.0767"")
        if (stream >> lat >> delimiter >> lng && delimiter == ',') {
            return GPS(lat, lng);
        } else {
            throw std::invalid_argument("Invalid coordinates format. Expected format: 'lat,lng'");
        }
    }

    // Method to display the GPS coordinates
    void display() const {
        std::cout << "Latitude: " << latitude << ", Longitude: " << longitude << std::endl;
    }
};

int main() {
    GPS gps = GPS::fromString("12.345,-67.890");
    gps.display();

    return 0;
}
