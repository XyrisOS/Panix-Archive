/**
 * @file PCI.hpp
 * @author Keeton Feavel (keetonfeavel@cedarville.edu)
 * @brief 
 * @version 0.1
 * @date 2019-09-26
 * 
 * @copyright Copyright Keeton Feavel (c) 2019
 * 
 */
#ifndef PANIX_PCI_HPP
#define PANIX_PCI_HPP
// TODO: PCI needs some serious documentation. Refer to https://youtu.be/GE7iO2vlLD4 and https://youtu.be/yqjDYF4NCXg for info.
#include <types.hpp>
#include <cpu/port/Port.hpp>
#include <cpu/interrupts/InterruptHandler.hpp>
#include <drivers/Driver.hpp>
#include <drivers/DriverManager.hpp>
#include <libc/kprint.hpp>

#define PCI_COMMAND_PORT 0xCF8
#define PCI_DATA_PORT 0xCFC

/**
 * @brief Base address register type definition
 * 
 */
enum BaseAddressRegisterType {
    // Identifies if a PCI device uses memory mapped or port based I/O
    MemoryMapping = 0,
    InputOutput = 1
};
/**
 * @brief Base address register definition
 * 
 */
class BaseAddressRegister {
    public:
        // Base address Registers (or BARs) can be used to hold memory
        // addresses used by the device, or offsets for port addresses.
        // Typically, memory address BARs need to be located in physical
        // ram while I/O space BARs can reside at any memory address
        // (even beyond physical memory). To distinguish between them,
        // you can check the value of the lowest bit.
        // (https://wiki.osdev.org/Pci#Base_Address_Registers)
        uint32_t size;                  // Size of the BAR (not part of the BAR specs)
        uint8_t* address;               // 16-Byte Aligned Base Address
        bool prefetchable;              // See GetBaseAddressRegister()
        BaseAddressRegisterType type;   // See above enum
};
/**
 * @brief PCI Device Descriptor Class
 * 
 */
class PeripheralComponentInterconnectDeviceDescriptor : public Driver {
    public:
        /* Declare all of the PCI interface information types */
        // These don't exactly line up with what OSDev has in their table
        // but I did my best to reorder them according to what the bits
        // actually mean in the order they occur

        // The Class Code, Subclass, and Prog IF registers are used to 
        // identify the device's type, the device's function, and the 
        // device's register-level programming interface, respectively.
        // (https://wiki.osdev.org/Pci#Class_Codes)
        uint16_t vendor_id;     // Vendor identifier
        uint16_t device_id;     // Device identifier
        uint8_t  revision;      // Device revision
        uint8_t  interface_id;  // Interface identifier
        uint8_t  subclass_id;   // Subclass identifier
        uint8_t  class_id;      // Class identifier
        uint16_t bus;           // PCI bus number
        uint32_t portBase;      // PCI CPU port value
        uint32_t interrupt;     // IRQ associated with device
        uint16_t device;        // Device type value (see table)
        uint16_t function;      // Function value (see table)
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
 * @brief PCI Controller Class
 * 
 */
class PeripheralComponentInterconnectController : public Driver {
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
         * @brief Reads a long (32 bit) value from a PCI device based on the provided information
         * 
         * @param bus PCI bus index value
         * @param device Device identifier
         * @param function Device function code
         * @param registeroffset PCI device register offset value
         * @return uint32_t Long (32 bit) value read from the PCI device
         */
        uint32_t read(uint16_t bus, uint16_t device, uint16_t function, uint32_t registeroffset);
        /**
         * @brief Writes a given long (32 bit) value to the PCI device based on the provided information
         * 
         * @param bus PCI bus index value
         * @param device Device identifier
         * @param function Device function code
         * @param registeroffset PCI device register offset value
         * @param value Long (32 bit) value to be written to PCI device bus
         */
        void write(uint16_t bus, uint16_t device, uint16_t function, uint32_t registeroffset, uint32_t value);
        /**
         * @brief Checks if a PCI device identifies as having a given function
         * 
         * @param bus PCI bus index value
         * @param device Device identifier
         * @return true Device does identify as having requested function
         * @return false Device does not identify as having requested function
         */
        bool DeviceHasFunctions(uint16_t bus, uint16_t device);
        /**
         * @brief Selects a driver for a given PCI device (assuming it exists)
         * 
         * @param driverManager Current active kernel driver manager
         * @param interrupts Current active kernel interrupt manager
         */
        void SelectDrivers(DriverManager* driverManager, InterruptManager* interrupts);
        /**
         * @brief Gets the Driver object for a given PCI device
         * 
         * @param dev Requested PCI device descriptor
         * @param interrupts Current active kernel interrupt manager
         * @return Driver* Returned driver associated with the requested PCI device
         */
        Driver* GetDriver(PeripheralComponentInterconnectDeviceDescriptor dev, InterruptManager* interrupts);
        /**
         * @brief Gets the Device Descriptor object based on the provided information
         * 
         * @param bus PCI bus index value
         * @param device Device identifier
         * @param function Device function code
         * @return PeripheralComponentInterconnectDeviceDescriptor Returned PCI Device associated Descriptor
         */
        PeripheralComponentInterconnectDeviceDescriptor GetDeviceDescriptor(uint16_t bus, uint16_t device, uint16_t function);
        /**
         * @brief Get the Base Address Register object based on the provided information
         * 
         * @param bus PCI bus index value
         * @param device Device identifier
         * @param function Device function code
         * @param bar PCI Base Address Register value
         * @return BaseAddressRegister Returned associated PCI device BAR object
         */
        BaseAddressRegister GetBaseAddressRegister(uint16_t bus, uint16_t device, uint16_t function, uint16_t bar);
};

#endif /* PANIX_PCI_HPP */