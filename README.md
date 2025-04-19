## Embedded AI Data Logger for Predictive Maintenance

---
### 📌 Project Overview

---
### 🔧 Key Features
✅ **Modular & Scalable Design**  
&nbsp;&nbsp;&nbsp;🔹 **Factory Design Pattern** in C++ for dynamic creation of Machines.  
&nbsp;&nbsp;&nbsp;🔹 **Plug-and-play expandability**: Add more Machines for larger deployments.  

✅ **Multi-Sensor Monitoring**   
&nbsp;&nbsp;&nbsp;🔥**Air Compressor**: Temperature, Pressure, Vibration     
&nbsp;&nbsp;&nbsp;💧**Steam Boiler**: Temperature, Pressure
&nbsp;&nbsp;&nbsp;♨️**Electric Motor**: Tempearture    
&nbsp;&nbsp;&nbsp;*( )*   

✅ **On-Device Detection**   
 


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
