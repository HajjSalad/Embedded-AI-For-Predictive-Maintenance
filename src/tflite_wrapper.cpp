#include <stdio.h>
#include <stdlib.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/__assert.h>

#include "autoencoder_model.h"
#include <tensorflow/lite/micro/micro_interpreter.h>
#include <tensorflow/lite/micro/micro_op_resolver.h>
#include <tensorflow/lite/micro/micro_mutable_op_resolver.h>
#include <tensorflow/lite/schema/schema_generated.h>

#define TENSOR_ARENA_SIZE       10 * 1024

static uint8_t tensor_arena[TENSOR_ARENA_SIZE];

const tflite::Model* model = NULL;
tflite::MicroInterpreter* interpreter = NULL;
TfLiteTensor* input = NULL;
TfLiteTensor* output = NULL;

extern "C" void tflite_setup()
{
    // Load model
    model = tflite::GetModel(autoencoder_model_tflite);
    if (model->version() != TFLITE_SCHEMA_VERSION) {
        printk("Model schema mismatch!\n");
        return;
    }

    // Set up operator resolver (includes all ops)
    static tflite::MicroMutableOpResolver<5> resolver;
    resolver.AddFullyConnected();
    resolver.AddRelu();
    resolver.AddReshape();
    resolver.AddSoftmax();

    // Set up interpreter
    static tflite::MicroInterpreter static_interpreter(
        model, resolver, tensor_arena, TENSOR_ARENA_SIZE);
    interpreter = &static_interpreter;

    // Allocate tensor buffers
    TfLiteStatus allocate_status = interpreter->AllocateTensors();
    if (allocate_status != kTfLiteOk) {
        printk("AllocateTensors() failed\n");
        return;
    }

    // Get input/output tensors
    input = interpreter->input(0);
    output = interpreter->output(0);

    printk("TFLite Micro setup complete!\n");
}

extern "C" void tflite_run_inference() 
{
    // Example: Fill input with dummy data (e.g., all 0.5)
    for (int i = 0; i < input->bytes / sizeof(float); i++) {
        input->data.f[i] = 0.5f;
    }

    // Run inference
    TfLiteStatus invoke_status = interpreter->Invoke();
    if (invoke_status != kTfLiteOk) {
        printk("Invoke failed!\n");
        return;
    }

    // Print output
    for (int i = 0; i < output->bytes / sizeof(float); i++) {
        printk("Output[%d]: %f\n", i, output->data.f[i]);
    }
}