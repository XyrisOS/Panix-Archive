#ifndef PCI_HPP
#define PCI_HPP

#include <types.hpp>
#include <cpu/Port/Port.hpp>
#include <cpu/interrupts/InterruptHandler.hpp>
#include <drivers/Driver.hpp>
#include <drivers/DriverManager.hpp>
#include <libc/printf.hpp>

class PeripheralComponentInterconnectDeviceDescriptor : public Driver {
    public:

        uint32_t portBase;
        uint32_t interrupt;

        uint16_t bus;
        uint16_t device;
        uint16_t function;

        uint16_t vendor_id;
        uint16_t device_id;

        uint8_t class_id;
        uint8_t subclass_id;
        uint8_t interface_id;

        uint8_t revision;

        PeripheralComponentInterconnectDeviceDescriptor();
        ~PeripheralComponentInterconnectDeviceDescriptor();

    };

    class PeripheralComponentInterconnectController : public Driver {
            Port32Bit dataPort;
            Port32Bit commandPort;
        public:
            PeripheralComponentInterconnectController();
            ~PeripheralComponentInterconnectController();

            uint32_t read(uint16_t bus, uint16_t device, uint16_t function, uint32_t registeroffset);
            void write(uint16_t bus, uint16_t device, uint16_t function, uint32_t registeroffset, uint32_t value);
            bool DeviceHasFunctions(uint16_t bus, uint16_t device);

            void SelectDrivers(DriverManager* driverManager);
            PeripheralComponentInterconnectDeviceDescriptor GetDeviceDescriptor(uint16_t bus, uint16_t device, uint16_t function);
    };

#endif /* PCI_HPP */