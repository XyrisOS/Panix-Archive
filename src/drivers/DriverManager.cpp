/**
 * @file DriverManager.cpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */
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
