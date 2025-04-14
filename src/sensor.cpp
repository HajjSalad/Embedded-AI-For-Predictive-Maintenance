/*
//  sensor.cpp - Sensor Base class that all sensors inherit from it
*/

#include "sensor.h"
#include <string>
#include <stdio.h>

#include <memory>
#include <vector>
#include <iostream>

// Sensor implementations
void TempSensor::setValue(float value) { Value = value; }
float TempSensor::readValue() { return Value; }
std::string TempSensor::getType() { return "Temperature"; }

void PressureSensor::setValue(float value) { Value = value; }
float PressureSensor::readValue() { return Value; }
std::string PressureSensor::getType() { return "Pressure"; }

void VibrationSensor::setValue(float value) { Value = value; }
float VibrationSensor::readValue() { return Value; }
std::string VibrationSensor::getType() { return "Vibration"; }

// SensorFactory implementation
std::unique_ptr<Sensor> SensorFactory::createSensor(const std::string& type) {
    if (type == "Temperature") {
        return std::unique_ptr<Sensor>(new TempSensor());
    } else if (type == "Pressure") {
        return std::unique_ptr<Sensor>(new PressureSensor());
    } else if (type == "Vibration") {
        return std::unique_ptr<Sensor>(new VibrationSensor());
    }
    return nullptr;
}

// Machine implementation
Machine::Machine(const std::string& machineName, const std::vector<std::string>& sensorTypes, MachineType machineType) 
    : type(machineType), name(machineName)  {
    for (const auto& type : sensorTypes) {
        auto sensor = SensorFactory::createSensor(type);
        if (sensor) {
            sensors.push_back(std::move(sensor));
        }
    }
}

void Machine::display() const {
    std::cout << "Machine: " << name << std::endl;
    for (const auto& sensor : sensors) {
        std::cout << "  - Sensor Type: " << sensor->getType() << std::endl;
    }
}

void Machine::setSensorValue(const std::string& type, float value) {
    for (auto& sensor : sensors) {
        if (sensor->getType() == type) {
            sensor->setValue(value);
            return;
        }
    }
    std::cout << "Sensor type " << type << " not found in machine " << name << std::endl;
}

float Machine::getSensorValue(const std::string& type) {
    for (const auto& sensor : sensors) {
        if (sensor->getType() == type) {
            return sensor->readValue();
        }
    }
    std::cout << "Sensor type " << type << " not found in machine " << name << std::endl;
    return -1.0f;
}



// /*
// //  sensor.cpp - Sensor Base class that all sensors inherit from it
// */

// #include "sensor.h"
// #include <string>
// #include <stdio.h>

// #include <memory>
// #include <vector>
// #include <iostream>

// // *** Sensor Base Implementation ***
// void Sensor::setValue(float value) {
//     Value = value;
// }

// // *** TempSensor Implementation ***
// void TempSensor::setValue(float value) {
//     Value = value;
// }
// float TempSensor::readValue() {
//     return Value;
// }
// std::string TempSensor::getType() {
//     return "Temperature";
// }

// // *** PressureSensor Implementation ***
// void PressureSensor::setValue(float value) {
//     Value = value;
// }
// float PressureSensor::readValue() {
//     return Value;
// }
// std::string PressureSensor::getType() {
//     return "Pressure";
// }

// // *** VibrationSensor Implementation ***
// void VibrationSensor::setValue(float value) {
//     Value = value;
// }
// float VibrationSensor::readValue() {
//     return Value;
// }
// std::string VibrationSensor::getType() {
//     return "Vibration";
// }

// // *** SensorFactory Implementation ***
// std::unique_ptr<Sensor> SensorFactory::createSensor(const std::string& type) {
//     if (type == "Temperature") {
//         return std::unique_ptr<Sensor>(new TempSensor());
//     } else if (type == "Pressure") {
//         return std::unique_ptr<Sensor>(new PressureSensor());
//     } else if (type == "Vibration") {
//         return std::unique_ptr<Sensor>(new VibrationSensor());
//     } else {
//         return nullptr;
//     }
// }

// // *** Machine Implementation ***
// Machine::Machine(const std::string& machineName, const std::vector<std::string>& sensorTypes) {
//     name = machineName;
//     for (const auto& type : sensorTypes) {
//         auto sensor = SensorFactory::createSensor(type);
//         if (sensor) {
//             sensors.push_back(std::move(sensor));
//         }
//     }
// }

// void Machine::display() const {
//     std::cout << "Machine: " << name << std::endl;
//     for (const auto& sensor : sensors) {
//         std::cout << "  - Sensor Type: " << sensor->getType() << std::endl;
//     }
// }

// void Machine::setSensorValue(const std::string& type, float value) {
//     for (auto& sensor : sensors) {
//         if (sensor->getType() == type) {
//             sensor->setValue(value);
//             return;
//         }
//     }
//     std::cout << "Sensor type " << type << " not found in machine " << name << std::endl;
// }

// float Machine::getSensorValue(const std::string& type) {
//     for (const auto& sensor : sensors) {
//         if (sensor->getType() == type) {
//             return sensor->readValue();
//         }
//     }
//     std::cout << "Sensor type " << type << " not found in machine " << name << std::endl;
//     return -1;
// }



// // // Base class Sensor
// // class Sensor {
// // protected:
// //     float Value;
// // public:
// //     virtual void setValue(float value) { Value = value; }
// //     virtual float readValue() = 0;
// //     virtual std::string getType() = 0;
// //     virtual ~Sensor() {}
// // };
    
// // // class TempSensor
// // class TempSensor : public Sensor {
// // public:
// //     void setValue(float value) override { Value = value; }
// //     float readValue() override { return Value; }
// //     std::string getType() override { return "Temperature"; }
// // };

// // // class PressureSensor
// // class PressureSensor : public Sensor {
// // public:
// //     void setValue(float value) override { Value = value; }
// //     float readValue() override { return Value; }
// //     std::string getType() override { return "Pressure"; }
// // };
    
// // // class VibrationSensor
// // class VibrationSensor : public Sensor {
// // public:
// //     void setValue(float value) override { Value = value; }
// //     float readValue() override { return Value; }
// //     std::string getType() override { return "Vibration"; }
// // };

// // // Create sensor based on string identifier
// // class SensorFactory {
// // public:
// //     // Return std::unique_ptr to corresponding Sensor object.
// //     static std::unique_ptr<Sensor> createSensor(const std::string& type) {
// //         if (type == "Temperature") {
// //             return std::make_unique<TempSensor>();
// //         } else if (type == "Pressure") {
// //             return std::make_unique<PressureSensor>();
// //         } else if (type == "Vibration") {
// //             return std::make_unique<VibrationSensor>();
// //         } else {
// //             return nullptr; // Invalid type
// //         }
// //     }
// // };

// // // A Machine has a set of sensors
// // class Machine {
// // public:
// //     std::string name;               // Name of the machine

// //     // Vector to hold unique pointers to Sensor objects
// //     std::vector<std::unique_ptr<Sensor>> sensors;

// //     // Constructor creates the corresponding Sensor objects
// //     Machine(const std::string& machineName, const std::vector<std::string>& sensorTypes) {
// //         name = machineName;

// //         // Loop through each sensor type string provided
// //         for (const auto& type : sensorTypes) {
// //             // Create the sensor
// //             auto sensor = SensorFactory::createSensor(type);

// //             // If sensor creation was successful, add it to the vector
// //             if (sensor) {
// //                 sensors.push_back(std::move(sensor));
// //             }
// //         }
// //     }
// // }
























// // // Base class Sensor
// // class Sensor {
// // protected:
// //     float Value;
// // public:
// //     virtual void setValue(float value) {
// //         Value = value;
// //     }
// //     virtual float readValue() = 0;      
// //     virtual std::string getType() = 0;
// //     virtual ~Sensor() {}                // Virtual destructor for polymorphism
// // };

// // // class TempSensor
// // class TempSensor : public Sensor {
// // public:
// //     void setValue(float value) override {
// //         Value = value;
// //     }
// //     float readValue() override {
// //         return Value;
// //     }
// //     std::string getType() override {
// //         return "Temperature"
// //     }
// // };

// // // class PressureSensor
// // class PressureSensor : public Sensor {
// // public:
// //     void setValue(float value) override {
// //         Value = value;
// //     }
// //     float readValue() override {
// //         return Value;
// //     }
// //     std::string getType() override {
// //         return "Pressure"
// //     }
// // };

// // // class VibrationSensor
// // class VibrationSensor : public Sensor {
// // public:
// //     void setValue(float value) override {
// //         Value = value;
// //     }
// //     float readValue() override {
// //         return Value;
// //     }
// //     std::string getType() override {
// //         return "Vibration"
// //     }
// // };
    
// // // class SensorFactory
// // class SensorFactory {
// // public:
// //     static std::unique_ptr<Sensor> createSensor(const std::string& type) {
// //         if (type == "Temperature") {
// //             return std::make_unique<TemperatureSensor>();
// //         } else if (type == "Pressure") {
// //             return std::make_unique<PressureSensor>();
// //         } else if (type == "Vibration") {
// //             return std::make_unique<VibrationSensor>();
// //         } else {
// //             return nullptr;  // Invalid type
// //         }
// //     }
// // };
    
// // // class Machine
// // class Machine {
// // private:
// //     std::vector<std::unique_ptr<Sensor>> sensors;
// //     std::string name;

// // public:
// //     Machine(const std::string& machineName, const std::vector<std::string>& sensorType : name(machineName)) {
// //         for (const auto& type : sensorType) {
// //             auto sensor = SensorFactory::createSensor(type);
// //             if (sensor) sensors.push_back(std::move(sensor));
// //         }
// //     }
// // };

// // // C-compatible wrapper functions
// // extern "C" {
// //     typedef void* MachineHandle;

// //     MachineHandle create_machine(const char* machine_name, const char* sensor_types[], int num_sensors) {
// //         std::vector<std::string> sensorTypeVec;
// //         for (int i = 0; i < num_sensors; ++i) {
// //             sensorTypeVec.push_back(sensor_types[i]);
// //         }
// //         Machine* machine = new Machine(machine_name, sensorTypeVec);
// //         return reinterpret_cast<MachineHandle>(machine);
// //     }

// //     void display_machine(MachineHandle handle) {
// //         Machine* machine = reinterpret_cast<Machine*>(handle);
// //         machine->display();
// //     }

// //     void delete_machine(MachineHandle handle) {
// //         Machine* machine = reinterpret_cast<Machine*>(handle);
// //         delete machine;
// //     }
// // };