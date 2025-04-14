#include "sensor.h"
#include "sensor_wrapper.h"
#include <vector>
#include <string>
#include <cstring>

// Define sensor types for each machine type
const std::vector<std::string> air_compressor_sensors = {"Temperature", "Pressure", "Vibration"};
const std::vector<std::string> steam_boiler_sensors = {"Temperature", "Pressure"};
const std::vector<std::string> electric_motor_sensors = {"Temperature"};

MachineHandle create_machine(const char* machine_name, MachineType type) {
    std::vector<std::string> sensors;
    
    switch(type) {
        case AIR_COMPRESSOR:
            sensors = air_compressor_sensors;
            break;
        case STEAM_BOILER:
            sensors = steam_boiler_sensors;
            break;
        case ELECTRIC_MOTOR:
            sensors = electric_motor_sensors;
            break;
    }
    
    Machine* machine = new Machine(std::string(machine_name), sensors, type);
    return reinterpret_cast<MachineHandle>(machine);
}

void destroy_machine(MachineHandle handle) {
    Machine* machine = reinterpret_cast<Machine*>(handle);
    delete machine;
}

void describe_machine(MachineHandle handle) {
    Machine* machine = reinterpret_cast<Machine*>(handle);
    machine->display();
}

void set_sensor_value(MachineHandle handle, const char* sensor_type, float value) {
    Machine* machine = reinterpret_cast<Machine*>(handle);
    machine->setSensorValue(sensor_type, value);
}

float get_sensor_value(MachineHandle handle, const char* sensor_type) {
    Machine* machine = reinterpret_cast<Machine*>(handle);
    return machine->getSensorValue(sensor_type);
}

const char* get_machine_type_string(MachineType type) {
    switch (type) {
        case AIR_COMPRESSOR: return "Air Compressor";
        case STEAM_BOILER: return "Steam Boiler";
        case ELECTRIC_MOTOR: return "Electric Motor";
        default: return "Unknown Type";
    }
}

MachineType get_machine_type(MachineHandle handle) {
    Machine* machine = reinterpret_cast<Machine*>(handle);
    return machine->getType();
}



// #include "sensor.h"
// #include "wrapper.h"

// #include <stdint.h>
// #include <string>
// #include <stdio.h>

// #include <memory>
// #include <vector>
// #include <iostream>
// #include <cstddef>
// #include <cstdlib>
// #include <cstring>
// #include <stdlib.h>
// #include <new>

// // Wrapper function to create a Machine instance
// MachineHandle create_machine(const char* machine_name, const char* sensor_types[], int num_sensors, MachineType type) {
//     // Create a new Machine object dynamically
//     MachineStruct* machine = new MachineStruct;
    
//     // Set machine name
//     strncpy(machine->name, machine_name, sizeof(machine->name) - 1);
    
//     // Set machine type
//     machine->type = type;
    
//     // Set number of sensors
//     machine->num_sensors = num_sensors;

//     // Store the sensor types in a vector
//     for (int i = 0; i < num_sensors; ++i) {
//         machine->sensor_types.push_back(sensor_types[i]);
//     }

//     // Return machine handle (casting Machine pointer to MachineHandle)
//     return reinterpret_cast<MachineHandle>(machine);
//     // std::vector<std::string> sensorTypeVec;
//     // for (int i = 0; i < num_sensors; ++i) {
//     //     sensorTypeVec.push_back(sensor_types[i]);
//     // }
//     // Machine* machine = new Machine(machine_name, sensorTypeVec);
//     // return reinterpret_cast<MachineHandle>(machine);
// }

// // Wrapper function to destroy the Machine instance
// void destroy_machine(MachineHandle handle) {
//     MachineStruct* machine = reinterpret_cast<Machine*>(handle);
//     delete machine;
// }

// // Wrapper function to describe the Machine (e.g., list its sensors)
// void describe_machine(MachineHandle handle) {
//     MachineStruct* machine = reinterpret_cast<Machine*>(handle);
//     machine->display();
// }

// // Wrapper function to set a specific sensor value in the Machine
// void set_sensor_value(MachineHandle handle, const char* sensor_type, float value) {
//     MachineStruct* machine = reinterpret_cast<Machine*>(handle);
//     machine->setSensorValue(sensor_type, value);
// }

// // Wrapper function to get a specific sensor value from the Machine
// float get_sensor_value(MachineHandle handle, const char* sensor_type) {
//     MachineStruct* machine = reinterpret_cast<Machine*>(handle);
//     return machine->getSensorValue(sensor_type);
// }

// // Get string representation of MachineType
// const char* get_machine_type_string(MachineType type) {
//     switch (type) {
//         case AIR_COMPRESSOR:
//             return "Air Compressor";
//         case STEAM_BOILER:
//             return "Steam Boiler";
//         case ELECTRIC_MOTOR:
//             return "Electric Motor";
//         default:
//             return "Unknown Type";
//     }
// }
