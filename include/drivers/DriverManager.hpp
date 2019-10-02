/**
 * @file DriverManager.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright Keeton Feavel (c) 2019
 * 
 */
#ifndef PANIX_DRIVER_MANAGER_HPP
#define PANIX_DRIVER_MANAGER_HPP

#include <lib/string.hpp>
#include <drivers/Driver.hpp>

class DriverManager {
    private:
        Driver* drivers[265];
        int numberOfDrivers;
        
    public:
        /**
         * @brief Construct a new Driver Manager object.
         * 
         */
        DriverManager();
        /**
         * @brief Adds a driver to the driver manager.
         * 
         * @param driver Driver to be added.
         */
        void addDriver(Driver* driver);
        /**
         * @brief Activates all drivers in the manager.
         * 
         */
        void activateAll();
        /**
         * @brief Activates the last driver added to the manager.
         * 
         */
        void activateLast();
        /**
         * @brief Returns a pointer to a driver which has been added
         * to the driver manager and returns the given tag which has
         * been requested.
         * 
         * @param tag Driver tag
         */
        Driver* getDriverWithTag(char* tag);
};  

#endif /* PANIX_DRIVER_MANAGER_HPP */