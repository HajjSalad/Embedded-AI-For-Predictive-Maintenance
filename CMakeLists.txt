# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(detection)

# Add the tflite-micro module
set(TFLITE_MICRO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tflite-micro)
add_subdirectory(${TFLITE_MICRO_DIR})

# Add TensorFlow Lite Micro headers to include path
target_include_directories(app PRIVATE
    ${TFLITE_MICRO_DIR}
    ${TFLITE_MICRO_DIR}/tensorflow
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/flatbuffers/include  
)

# Add source files
target_sources(app PRIVATE src/main.c src/demo.cpp src/sensor.cpp src/sensor_wrapper.cpp src/tflite_wrapper.cpp src/autoencoder_model.cc)

target_sources(app PRIVATE
    # Core Micro runtime
    ${TFLITE_MICRO_DIR}/tensorflow/lite/micro/micro_interpreter.cc
    ${TFLITE_MICRO_DIR}/tensorflow/lite/micro/micro_allocator.cc
    ${TFLITE_MICRO_DIR}/tensorflow/lite/micro/debug_log.cc
    ${TFLITE_MICRO_DIR}/tensorflow/lite/micro/micro_profiler.cc
    ${TFLITE_MICRO_DIR}/tensorflow/lite/micro/memory_helpers.cc

    ${TFLITE_MICRO_DIR}/tensorflow/lite/array.cc

    # Kernel utilities
    ${TFLITE_MICRO_DIR}/tensorflow/lite/kernels/kernel_util.cc
)

# Include directories
target_include_directories(app PRIVATE include)

# Add model files to the app
target_sources(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/data/autoencoder.tflite)

# Enable C++ support
set(Zephyr_EXTRA_MODULES app)

# Specify the C++ standard library
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # Disable compiler-specific extensions for portability

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# Enable C++ exception handling
set(CMAKE_EXE_LINKER_FLAGS "-lgcc -lc -lstdc++")

target_link_libraries(app PRIVATE -lstdc++)

# Optionally, set specific compiler flags if necessary
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

