 
#ifndef DRIVER_HPP
#define DRIVER_HPP

class Driver {
    public:
        Driver();
        ~Driver();
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
         * @return int Return code. TODO: Update w/ specifics
         */
        virtual int reset();
        /**
         * @brief Virtual function implemented by each driver. Deactivates the
         * driver and stops it from being used by the kernel.
         * 
         */
        virtual void deactivate();
};
    
#endif /* DRIVER_HPP */