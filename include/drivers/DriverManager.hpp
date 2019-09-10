#ifndef PANIX_DRIVER_MANAGER_HPP
#define PANIX_DRIVER_MANAGER_HPP

#include <drivers/Driver.hpp>

/* Forward declaration */
class Driver;

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
};  

#endif /* PANIX_DRIVER_MANAGER_HPP */