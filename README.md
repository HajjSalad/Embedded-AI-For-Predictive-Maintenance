## Embedded AI Data Logger for Predictive Maintenance
This project implements a **real-time predictive maintenance system** on **STM32** microcontrollers using **Zephyr RTOS** and **TensorFlow Lite** for Microcontrollers. The system collects sensor data, performs on-device anomaly detection, and enables early equipment failure prediction to minimize unplanned downtime.

---
### 🔧 Key Features
🏭 **Factory Method Pattern** for modular creation of machines and sensors  
⏱ **Real-time data logging** on STM32 with Zephyr RTOS  
🔍 **On-device anomaly detection** using TensorFlow Lite for Microcontrollers  
⚡ **Early failure prediction** to reduce unplanned downtime  

---
### 🧱 **Modular & Scalar Machine Creation with Factory Design Pattern**

⚙️ **Machine-Sensor Configuration**  
Each industrial machine is equipped with specific sensors for predictive maintenance: 

1️⃣ **`AIR_COMPRESSOR`**  
&nbsp;&nbsp;&nbsp;&nbsp;📊 **Temperature**: `60-100°C` • 📏 **Pressure**: `72-145 psi` • 📳 **Vibration**: `0.5-2.0 mm/s`   
&nbsp;&nbsp;&nbsp;&nbsp;_Monitors overheating, pressure fluctuations, and mechanical wear_ 
 
2️⃣ **`STEAM_BOILER`**  
&nbsp;&nbsp;&nbsp;&nbsp;📊 **Temperature**: `150-250°C` • 📏 **Pressure**: `87-360 psi`     
&nbsp;&nbsp;&nbsp;&nbsp;_Tracks thermal efficiency and safety thresholds_

3️⃣ **`ELECTRIC_MOTOR`**   
&nbsp;&nbsp;&nbsp;&nbsp;📊 **Temperature**: `60-105°C`      
&nbsp;&nbsp;&nbsp;&nbsp;_Winding insulation safety range_  

🧩 **Factory Structure**
```
                        ┌────────────────────┐
                        │   SensorFactory    │ ← Abstract Creator
                        └────────────────────┘
                                  ▲
                                  │
                ┌─────────────────┴─────────────────┐
                │                                   │
       ┌─────────────────┐                ┌──────────────────┐
       │  createSensor() │                │ Machine Creation │
       └─────────────────┘                └──────────────────┘
      Creates sensor objects              Uses factory to build
    (Temp, Pressure, Vibration)            complete machines
```

**Sensor Hierarchy** (`sensor.h`)
```cpp
class Sensor {  // Abstract Product
    virtual void setValue(float) = 0;
    virtual float readValue() = 0;
    virtual std::string getType() = 0;
};

class TempSensor : public Sensor { /*...*/ };     // Concrete Products
class PressureSensor : public Sensor { /*...*/ };
class VibrationSensor : public Sensor { /*...*/ };
```

**Sensor Factory** (`sensor.h`)
```cpp
class SensorFactory {  // Creator
public:
    static std::unique_ptr<Sensor> createSensor(const std::string& type) {
        if (type == "Temperature") return make_unique<TempSensor>();
        if (type == "Pressure") return make_unique<PressureSensor>();
        if (type == "Vibration") return make_unique<VibrationSensor>();
        return nullptr;
    }
};
```

**Machine Integration** (`sensor.h`)
```cpp
class Machine {
    MachineType type;
    vector<unique_ptr<Sensor>> sensors;
    
public:
    Machine(const string& name, 
            const vector<string>& sensorTypes,
            MachineType machineType) {
        // Uses SensorFactory to populate sensors
        for (const auto& type : sensorTypes) {
            sensors.push_back(SensorFactory::createSensor(type));
        }
    }
};
```

💡**Usage Example**
```c
// Create a machine with appropriate sensors
MachineHandle handle = create_machine("Compressor1", AIR_COMPRESSOR);

// Set and read sensor values
set_sensor_value(handle, "Temperature", 42.5f);
float temp = get_sensor_value(handle, "Temperature");

// Clean up
destroy_machine(handle);
```

---
### 🏗 System Architecture
```
[Sensors] → 
```
### 🛠️ Tools and Software
𐂷 **Sensor Node**  
&nbsp;&nbsp;&nbsp;⎔ **VS Code** - Code editor for STM32 firmware development       
&nbsp;&nbsp;&nbsp;⎔ dfu-utils -        
&nbsp;&nbsp;&nbsp;⎔ CMake -   

---
### 📂 Project Code Structure
```
📁 Data-Logger-Predictive-Maintenance/
│── 📁 src/
│   ├── 📄 main.c                             (Entry point of the program)
│   ├── 📄 sensor.cpp / .h                    ()
│   ├── 📄 sensor_wrapper.cpp / .h            ()
│   ├── 📄 tflite_wrapper.cpp / .h            ()
│   ├── 📄 autoencoder_model.cc               ()
│── 📁 CMakeLists.txt/
│── 📁 prj.conf/
│── 📁 sample.yaml/
│── 📁 tflite-micro/
│   ├── 📄 tensorflow/                        ()
│   │   ├── 📄 lite                           () 
│── 📁 data/
│   ├── 📄 simulated_data.py                 (Python script to simulate sensor data)
│   ├── 📄 simulated_data.zip                (Compressed simulated sensor data)
│   ├── 📄 autoencoder.tflite                
│   ├── 📄 simulated_data                    
│   │   ├── 📄 machine_1                     (Machine type 1: Air Compressor)
│   │   │   ├── 📄 machine_1_temp.csv        (Temp sensor values)
│   │   │   ├── 📄 machine_1_pressure.csv    (Pressure sensor values)
│   │   │   ├── 📄 machine_1_vibration.csv   (Vibration sensor values)
│   │   ├── 📄 machine_2                     (Machine type 2: Steam Boiler)
│   │   │   ├── 📄 machine_2_temp.csv        (Temp sensor values)
│   │   │   ├── 📄 machine_2_pressure.csv    (Pressure sensor values)
│   │   ├── 📄 machine_3                     (Machine type 3: Electric Motor)
│   │   │   ├── 📄 machine_3_temp.csv        (Temp sensor values)
│── 📄 README.md  (Documentation)
```
