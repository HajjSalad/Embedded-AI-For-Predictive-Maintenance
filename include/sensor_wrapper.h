#ifndef SENSOR_WRAPPER_H
#define SENSOR_WRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    AIR_COMPRESSOR,
    STEAM_BOILER,
    ELECTRIC_MOTOR
} MachineType;

typedef struct {
    const char* name;
    float min_value;
    float max_value;
} SensorConfig;

typedef struct {
    const char* name;
    SensorConfig sensors[3];
    int num_sensors;
} MachineConfig;

typedef void* MachineHandle;

MachineHandle create_machine(const char* machine_name, MachineType type);
void destroy_machine(MachineHandle handle);
void describe_machine(MachineHandle handle);
void set_sensor_value(MachineHandle handle, const char* sensor_type, float value);
float get_sensor_value(MachineHandle handle, const char* sensor_type);
const char* get_machine_type_string(MachineType type);
MachineType get_machine_type(MachineHandle handle);

#ifdef __cplusplus
}
#endif

#endif // SENSOR_WRAPPER_H


// #ifndef WRAPPER_H
// #define WRAPPER_H

// #ifdef __cplusplus
// extern "C" {
// #endif

// #include <stdlib.h>

// // 3 Types of Machines
// typedef enum {
//     AIR_COMPRESSOR,
//     STEAM_BOILER,
//     ELECTRIC_MOTOR
// } MachineType;

// // Machine Structure
// typedef struct {
//     char name[50];
//     MachineType type;                           // Type of the machine
//     int num_sensors;
// } MachineStruct;

// // Define the handle type for a Machine instance
// typedef void* MachineHandle;

// // Create a Machine instance
// MachineHandle create_machine(const char* machine_name, const char* sensor_types[], int num_sensors, MachineType type);

// // Destroy Machine instance
// void destroy_machine(MachineHandle handle);

// // Describe the Machine (e.g., list its sensors)
// void describe_machine(MachineHandle handle);

// // Set the value of a specific sensor in the Machine
// void set_sensor_value(MachineHandle handle, const char* sensor_type, float value);

// // Get the value of a specific sensor in the Machine
// float get_sensor_value(MachineHandle handle, const char* sensor_type);

// // Get string representation of MachineType
// const char* get_machine_type_string(MachineType type);

// #ifdef __cplusplus
// }
// #endif

// #endif // WRAPPER_H
