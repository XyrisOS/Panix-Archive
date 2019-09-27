/**
 * @file DriverManager.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef PANIX_DRIVER_MANAGER_HPP
#define PANIX_DRIVER_MANAGER_HPP

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
};  

#endif /* PANIX_DRIVER_MANAGER_HPP */