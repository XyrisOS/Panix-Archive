#include <drivers/DriverManager.hpp>

DriverManager::DriverManager() {
    numberOfDrivers = 0;
}

void DriverManager::addDriver(Driver* driver) {
    drivers[numberOfDrivers] = driver;
    numberOfDrivers++;
}

void DriverManager::activateAll() {
    for (int i = 0; i < numberOfDrivers; i++) {
        drivers[i]->activate();
    }
}
