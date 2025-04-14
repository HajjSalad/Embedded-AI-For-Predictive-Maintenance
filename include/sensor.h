#ifndef SENSOR_H
#define SENSOR_H

#include "sensor_wrapper.h"
#include <stdint.h>
#include <string>
#include <stdio.h>

#include <memory>
#include <vector>
#include <iostream>

class Sensor {
protected:
    float Value;
public:
    virtual void setValue(float value) = 0;
    virtual float readValue() = 0;
    virtual std::string getType() = 0;
    virtual ~Sensor() {}
};

class TempSensor : public Sensor {
public:
    void setValue(float value) override;
    float readValue() override;
    std::string getType() override;
};

class PressureSensor : public Sensor {
public:
    void setValue(float value) override;
    float readValue() override;
    std::string getType() override;
};

class VibrationSensor : public Sensor {
public:
    void setValue(float value) override;
    float readValue() override;
    std::string getType() override;
};

class SensorFactory {
public:
    static std::unique_ptr<Sensor> createSensor(const std::string& type);
};

// class Machine {
// public:
//     std::string name;
//     std::vector<std::unique_ptr<Sensor>> sensors;

//     Machine(const std::string& machineName, const std::vector<std::string>& sensorTypes);
//     void display() const;
//     void setSensorValue(const std::string& type, float value);
//     float getSensorValue(const std::string& type);
// };

class Machine {
private:
    MachineType type;  

public:
    std::string name;
    std::vector<std::unique_ptr<Sensor>> sensors;

    Machine(const std::string& machineName, const std::vector<std::string>& sensorTypes, MachineType machineType);
    
    void display() const;
    void setSensorValue(const std::string& type, float value);
    float getSensorValue(const std::string& type);
    MachineType getType() const { return type; }
};
    

#endif // SENSOR_H



// #ifndef SENSOR_H
// #define SENSOR_H

// #include <stdint.h>
// #include <string>
// #include <stdio.h>

// #include <memory>
// #include <vector>
// #include <iostream>


// // Base class Sensor
// class Sensor {
// protected:
//     float Value;
// public:
//     virtual void setValue(float value);
//     virtual float readValue() = 0;
//     virtual std::string getType() = 0;
//     virtual ~Sensor() {}
// };

// // Derived class TempSensor
// class TempSensor : public Sensor {
// public:
//     void setValue(float value) override;
//     float readValue() override;
//     std::string getType() override;
// };

// // Derived class PressureSensor
// class PressureSensor : public Sensor {
// public:
//     void setValue(float value) override;
//     float readValue() override;
//     std::string getType() override;
// };

// // Derived class VibrationSensor
// class VibrationSensor : public Sensor {
// public:
//     void setValue(float value) override;
//     float readValue() override;
//     std::string getType() override;
// };

// // class SensorFactory
// class SensorFactory {
// public:
//     static std::unique_ptr<Sensor> createSensor(const std::string& type);
// };

// // class Machine
// class Machine {
// public:
//     std::string name;
//     std::vector<std::unique_ptr<Sensor>> sensors;

//     Machine(const std::string& machineName, const std::vector<std::string>& sensorTypes);
//     void display() const;
//     void setSensorValue(const std::string& type, float value);
//     float getSensorValue(const std::string& type);
// };
    
// #endif // SENSOR_H
