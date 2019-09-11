 
#ifndef PANIX_DRIVER_HPP
#define PANIX_DRIVER_HPP

class Driver {
    public:
        Driver();
        ~Driver(); // TODO: Eventually needs to be virtual once delete is implemented
        /**
         * @brief Virtual function implemented by each driver. Used to
         * actually activate the driver for usage.
         * 
         */
        virtual void activate();
        /**
         * @brief Virtual function implemented by each driver.
         * Resets the driver. Used in the event of a catastropic error.
         * 
         * @return int Return code. Always 0 right now.
         */
        virtual int reset();
        /**
         * @brief Virtual function implemented by each driver. Deactivates the
         * driver and stops it from being used by the kernel.
         * 
         */
        virtual void deactivate();
};
    
#endif /* PANIX_DRIVER_HPP */