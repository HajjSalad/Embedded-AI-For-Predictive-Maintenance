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

💡**Usage Example**
```c
// Create a machine by providing the name and TYPE
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
[📡 Sensors] → [💻 STM32 (Zephyr RTOS)] → [🧠 TensorFlow Lite] → [⚠️ Anomaly Detection] → [📊 Logging/DFU]
```
### 🛠️ Tools and Software 
&nbsp;&nbsp;&nbsp;⎔ **VS Code** - Primary IDE for STM32 firmware development  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;• Extensions: Cortex-Debug, Zephyr IDE, CMake Tools  
&nbsp;&nbsp;&nbsp;⎔ **Zephyr RTOS** - Real-time operating system for resource-constrained devices  
&nbsp;&nbsp;&nbsp;⎔ **Tensflow Lite for MCUs** - On-device ML inference (quantized models)   
&nbsp;&nbsp;&nbsp;⎔ **CMake** - Build system for Zephyr projects  
&nbsp;&nbsp;&nbsp;⎔ **dfu-utils** - Firmware updates via USB DFU protocol           

---
### 📂 Project Code Structure
```
📁 Data-Logger-Predictive-Maintenance/   
│── 📁 src/                                   (Core application source)
│   ├── 📄 main.c                             (Zephyr application entry point)
│   ├── 📄 sensor.cpp / .h                    (Sensor base class + implementations)
│   ├── 📄 sensor_wrapper.cpp / .h            (C-compatible sensor interface)
│   ├── 📄 tflite_wrapper.cpp / .h            (TensorFlow Lite inference interface)
│   ├── 📄 autoencoder_model.cc / .h          (Embedded ML model definition)
│── 📁 CMakeLists.txt/                        (Build system configuration)
│── 📁 prj.conf/                              (Zephyr kernel config)
│── 📁 sample.yaml/                           
│── 📁 tflite-micro/
│   ├── 📄 tensorflow/                        
│   │   ├── 📄 lite                           (TensorFlow Lite for Microcontrollers) 
│── 📁 data/
│   ├── 📄 simulated_data.py                 (Sensor data simulator)
│   ├── 📄 simulated_data.zip                (Compressed simulated sensor data)
│   ├── 📄 autoencoder.tflite                (Quantized TF Lite model)                
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
│── 📄 README.md                             (Documentation)
```
