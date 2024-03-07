#include <iostream>
#include <cmath>

struct CartesianCoordinates {
    double x;
    double y;
    double z;
};

struct GPSCoordinates {
    double latitude;
    double longitude;
    double altitude;
};

const double WGS84_a = 6378137.0; // Semi-major axis in meters
const double WGS84_f = 1.0 / 298.257223563; // Flattening

GPSCoordinates convertCartesianToGPS(const CartesianCoordinates& cartesian) {
    GPSCoordinates gps;

    double p = sqrt(cartesian.x * cartesian.x + cartesian.y * cartesian.y);

    // Calculate longitude
    gps.longitude = atan2(cartesian.y, cartesian.x);

    // Calculate latitude
    double e2 = WGS84_f * (2.0 - WGS84_f);
    double phi = atan2(cartesian.z, p * (1.0 - e2));
    double phi_prev;
    do {
        phi_prev = phi;
        double N = WGS84_a / sqrt(1.0 - e2 * sin(phi_prev) * sin(phi_prev));
        phi = atan2(cartesian.z + e2 * N * sin(phi_prev), p);
    } while (fabs(phi - phi_prev) > 1e-8);

    gps.latitude = phi;

    // Calculate altitude
    gps.altitude = p / cos(phi) - N;

    // Convert radians to degrees
    gps.latitude = gps.latitude * 180.0 / M_PI;
    gps.longitude = gps.longitude * 180.0 / M_PI;

    return gps;
}

int main() {
    CartesianCoordinates cartesian;
    std::cout << "Enter Cartesian coordinates (x y z): ";
    std::cin >> cartesian.x >> cartesian.y >> cartesian.z;

    GPSCoordinates gps = convertCartesianToGPS(cartesian);

    std::cout << "Converted GPS coordinates:" << std::endl;
    std::cout << "Latitude: " << gps.latitude << "°" << std::endl;
    std::cout << "Longitude: " << gps.longitude << "°" << std::endl;
    std::cout << "Altitude: " << gps.altitude << " meters" << std::endl;

    return 0;
}