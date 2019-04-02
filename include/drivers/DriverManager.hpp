#ifndef DRIVER_MANAGER_HPP
#define DRIVER_MANAGER_HPP

#include <drivers/Driver.hpp>

/* Forward declaration */
class Driver;

class DriverManager {
    private:
        Driver* drivers[265];
        int numberOfDrivers;
        
    public:
        DriverManager();
        void addDriver(Driver* driver);
        void activateAll();
};  

#endif /* DRIVER_MANAGER_HPP */