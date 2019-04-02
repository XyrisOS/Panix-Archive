 
#ifndef DRIVER_HPP
#define DRIVER_HPP

class Driver {
    public:
        Driver();
        ~Driver();
        
        virtual void activate();
        virtual int reset();
        virtual void deactivate();
};
    
#endif /* DRIVER_HPP */