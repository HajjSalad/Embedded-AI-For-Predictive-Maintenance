## Embedded AI Data Logger for Predictive Maintenance
This project implements a real-time predictive maintenance system on STM32 microcontrollers using Zephyr RTOS and TensorFlow Lite for Microcontrollers. The system collects sensor data, performs on-device anomaly detection, and enables early equipment failure prediction to minimize unplanned downtime.

---
### 🔧 Key Features
🏭 **Factory Method Pattern** for modular creation of machines and sensors
⏱ **Real-time data logging** on STM32 with Zephyr RTOS
🔍 **On-device anomaly detection** using TensorFlow Lite for Microcontrollers
⚡ **Early failure prediction** to reduce unplanned downtime

---
### 🧱 **Modular & Scalar Machine Creation with Factory Design Pattern**

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

⚙️ **Machine-Sensor Configuration**
`Machine Type`    |  Sensors  
------------------|---------
`AIR_COMPRESSOR`  | Temperature, Pressure, Vibration  
`STEAM_BOILER`    | Temperature, Pressure  
`ELECTRIC_MOTOR`  | Temperature  

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
