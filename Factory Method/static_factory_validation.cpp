#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <regex>

class GPS {
private:
    double latitude;
    double longitude;

    // Private constructor
    GPS(double lat, double lng) : latitude(lat), longitude(lng) {}

    // Helper function to validate latitude and longitude ranges
    static void validateCoordinates(double lat, double lng) {
        if (lat < -90.0 || lat > 90.0) {
            throw std::out_of_range("Latitude must be between -90 and 90 degrees.");
        }
        if (lng < -180.0 || lng > 180.0) {
            throw std::out_of_range("Longitude must be between -180 and 180 degrees.");
        }
    }

public:
    // Static factory method to create a GPS object from a string
    static GPS fromString(const std::string& coordinates) {
        double lat, lng;
        char delimiter;

        std::istringstream stream(coordinates);

        // Assuming the format is "lat,lng" (e.g., "49.4521,11.0767")
        if (stream >> lat >> delimiter >> lng && delimiter == ',') {
            validateCoordinates(lat, lng); // Validate ranges
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
    try {
        // Valid input
        GPS gps = GPS::fromString("12.345,-67.890");
        gps.display();

        // Invalid input: out of range
        GPS invalidGPS = GPS::fromString("91.000,-67.890");
        invalidGPS.display();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    try {
        // Invalid input: wrong format
        GPS invalidFormatGPS = GPS::fromString("12.345|-67.890");
        invalidFormatGPS.display();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
