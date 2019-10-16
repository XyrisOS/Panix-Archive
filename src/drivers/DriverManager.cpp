/**
 * @file DriverManager.cpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright Keeton Feavel (c) 2019
 * 
 */
#include <drivers/DriverManager.hpp>

DriverManager* DriverManager::activeDriverManager = nullptr;

DriverManager::DriverManager() {
    // Set the active DriverManager pointer if necessary
    if (activeDriverManager == nullptr) {
        kprint("Setting active driver manager...\n");
        activeDriverManager = this;
    }
    numberOfDrivers = 0;
}

void DriverManager::addDriver(Driver* driver) {
    drivers[numberOfDrivers] = driver;
    numberOfDrivers++;
}

void DriverManager::activateAll() {
    kprint("Activating drivers...\n");
    for (int i = 0; i < numberOfDrivers; i++) {
        drivers[i]->activate();
    }
}

void DriverManager::activateLast() {
    int index = numberOfDrivers - 1;
    drivers[index]->activate();
}

Driver* DriverManager::getDriverWithTag(char* tag) {
    // Cycle through the drivers which have been added
    kprint("Number of drivers to search: ");
    char numString[5];
    intToString(numberOfDrivers, numString);
    kprint(numString);
    kprint("\n");
    kprint("Looking for driver...\n");
    for (uint8_t i = 0; i < numberOfDrivers; i++) {
        // If we find a matching tag
        if (drivers[i] != nullptr) {
            if (strcmp(drivers[i]->getDriverTypeTag(), tag) == 0) {
                // Return the associated driver
                kprint("Got driver.\n");
                return drivers[i];
            } else {
                //kprint("Searching... Got ");
                //kprint(drivers[i]->getDriverTypeTag());
                //kprint("\n");
                char currNum[5];
                intToString(i, currNum);
                kprint(currNum);
                kprint(" ");
            }
        }
    }
    // Nothing was found.
    kprint("No such driver exists.\n");
    return nullptr;
}