#ifndef PCI_HPP
#define PCI_HPP
// TODO: PCI needs some serious documentation. Refer to https://youtu.be/GE7iO2vlLD4 and https://youtu.be/yqjDYF4NCXg for info.
#include <types.hpp>
#include <cpu/Port/Port.hpp>
#include <cpu/interrupts/InterruptHandler.hpp>
#include <drivers/Driver.hpp>
#include <drivers/DriverManager.hpp>
#include <libc/kprint.hpp>
/**
 * @brief 
 * 
 */
enum BaseAddressRegisterType
{
    MemoryMapping = 0,
    InputOutput = 1
};
/**
 * @brief 
 * 
 */
class BaseAddressRegister {
    public:
        bool prefetchable;
        uint8_t* address;
        uint32_t size;
        BaseAddressRegisterType type;
};
/**
 * @brief 
 * 
 */
class PeripheralComponentInterconnectDeviceDescriptor : public Driver {
    public:
        /* Declare all of the PCI interface information types */
        uint32_t portBase;
        uint32_t interrupt;
        uint16_t bus;
        uint16_t device;
        uint16_t function;
        uint16_t vendor_id;
        uint16_t device_id;
        uint8_t  class_id;
        uint8_t  subclass_id;
        uint8_t  interface_id;
        uint8_t  revision;
        /**
         * @brief Construct a new Peripheral Component Interconnect Device Descriptor object
         * 
         */
        PeripheralComponentInterconnectDeviceDescriptor();
        /**
         * @brief Destroy the Peripheral Component Interconnect Device Descriptor object
         * 
         */
        ~PeripheralComponentInterconnectDeviceDescriptor();

};
/**
 * @brief 
 * 
 */
class PeripheralComponentInterconnectController : public Driver {
        Port32Bit dataPort;
        Port32Bit commandPort;
    public:
        /**
         * @brief Construct a new Peripheral Component Interconnect Controller object
         * 
         */
        PeripheralComponentInterconnectController();
        /**
         * @brief Destroy the Peripheral Component Interconnect Controller object
         * 
         */
        ~PeripheralComponentInterconnectController();
        /**
         * @brief 
         * 
         * @param bus 
         * @param device 
         * @param function 
         * @param registeroffset 
         * @return uint32_t 
         */
        uint32_t read(uint16_t bus, uint16_t device, uint16_t function, uint32_t registeroffset);
        /**
         * @brief 
         * 
         * @param bus 
         * @param device 
         * @param function 
         * @param registeroffset 
         * @param value 
         */
        void write(uint16_t bus, uint16_t device, uint16_t function, uint32_t registeroffset, uint32_t value);
        /**
         * @brief 
         * 
         * @param bus 
         * @param device 
         * @return true 
         * @return false 
         */
        bool DeviceHasFunctions(uint16_t bus, uint16_t device);
        /**
         * @brief 
         * 
         * @param driverManager 
         * @param interrupts 
         */
        void SelectDrivers(DriverManager* driverManager, InterruptManager* interrupts);
        /**
         * @brief Get the Driver object
         * 
         * @param dev 
         * @param interrupts 
         * @return Driver* 
         */
        Driver* GetDriver(PeripheralComponentInterconnectDeviceDescriptor dev, InterruptManager* interrupts);
        /**
         * @brief Get the Device Descriptor object
         * 
         * @param bus 
         * @param device 
         * @param function 
         * @return PeripheralComponentInterconnectDeviceDescriptor 
         */
        PeripheralComponentInterconnectDeviceDescriptor GetDeviceDescriptor(uint16_t bus, uint16_t device, uint16_t function);
        /**
         * @brief Get the Base Address Register object
         * 
         * @param bus 
         * @param device 
         * @param function 
         * @param bar 
         * @return BaseAddressRegister 
         */
        BaseAddressRegister GetBaseAddressRegister(uint16_t bus, uint16_t device, uint16_t function, uint16_t bar);
};

#endif /* PCI_HPP */