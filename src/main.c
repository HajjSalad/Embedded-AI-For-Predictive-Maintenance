/*
// main.c - Entry point and main flow of program
*/

#include "demo.h"
#include "sensor_wrapper.h"
#include "tflite_wrapper.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/__assert.h>

#define PRIORITY             7
#define STACKSIZE           1024
#define NUM_MACHINES         3

#define LED0_NODE DT_ALIAS(led0)     // The devicetree node identifier for the "led0" alias

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

MachineHandle machines[NUM_MACHINES];

static const MachineConfig machine_configs[] = 
{
    {   "Air Compressor",
        {   {"Temperature", 60.0f, 100.0f},         // 60 - 100°C
            {"Pressure", 72.0f, 145.0f},            // 72 - 145 psi
            {"Vibration", 0.5f, 2.0f} },            // 0.5 - 2.0 mm/s
        3
    },
    {   "Steam Boiler",
        {   {"Temperature", 150.0f, 250.0f},        // 150 - 250°C
            {"Pressure", 87.0f, 360.0f},            // 87 - 360 psi
            {"", 0.0f, 0.0f} },                     // Leave these empty
        2
    },
    {   "Electric Motor",
        {   {"Temperature", 60.0f, 105.0f},         // 60 - 105°C
            {"", 0.0f, 0.0f},                       // Leave empty
            {"", 0.0f, 0.0f} },                     // Leave empty
        1
    }
};

void generate_machines() 
{
    //   To create and add machine:
    //   1. Increment NUM_MACHINES
    //   2. Create machine instance   

    // Create a Machine instance with specified sensors
    machines[0] = create_machine("Air_Compressor_1", AIR_COMPRESSOR);
    machines[1] = create_machine("Steam_Boiler_1", STEAM_BOILER);
    machines[2] = create_machine("Electric_Motor_1", ELECTRIC_MOTOR);

    // Print Machine details - name, sensors
    for (int i=0; i<NUM_MACHINES; i++) {
        describe_machine(machines[i]);
    }
}

// Thread to blink led0
void blink0(void) {
    int ret;

    // Check if the GPIO is ready 
    if (!gpio_is_ready_dt(&led)) { printk("Error: GPIO device not ready.\n"); return; }

    // Configure the LED pin as an output
    ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) { printk("Error: Failed to configure GPIO pin.\n"); return; }

    while (1) {
        // Toggle the LED state
        ret = gpio_pin_toggle_dt(&led);
        if (ret < 0) { printk("Error: Failed to toggle GPIO pin.\n"); return; }

        k_msleep(1000);        
    }    
}

// Thread to read the sensor data into the machines
void set_data(void) 
{
    while (1)
    {
        printf("\nSet machines values:\n");
        for (int i=0; i<NUM_MACHINES; i++)              // Set values for all the sensors in each machine
        {
            MachineType type = get_machine_type(machines[i]);
            if (type < 0 || type >= (sizeof(machine_configs) / sizeof(machine_configs[0]))) {
                printf("Error: Invalid machine type %d\n", type);
                continue;
            }

            const MachineConfig* config = &machine_configs[type];           // Use MachineType to index into machine_configs 

            printf("%s:", config->name);
            for (int s=0; s < config->num_sensors; s++) {
                const SensorConfig* sensor = &config->sensors[s];
                
                if (strlen(sensor->name) == 0) continue;                    // Skip invalid sensors

                float range = sensor->max_value - sensor->min_value;
                float value = sensor->min_value + (rand() / (float)RAND_MAX) * range;

                set_sensor_value(machines[i], sensor->name, value);
                if (s == 0) {
                    printf(" %s = %.2f  [range %.1f-%.1f]\n",  
                        sensor->name, (double)value, (double)sensor->min_value, (double)sensor->max_value);
                } else {
                    printf("                %s = %.2f  [range %.1f-%.1f]\n",  
                        sensor->name, (double)value, (double)sensor->min_value, (double)sensor->max_value);
                }
            }
        }
        printf("\n");
        k_msleep(5000);  // Sleep for 3 seconds before printing again
    }
} 

// Thread to print sensor values of each machine
void print_data(void) 
{
    while (1) 
    {
        printf("\nGet machines values:\n");
        for (int i=0; i<NUM_MACHINES; i++)              
        {
            MachineType type = get_machine_type(machines[i]);
            if (type < 0 || type >= (sizeof(machine_configs) / sizeof(machine_configs[0]))) {
                printf("Error: Invalid machine type %d\n", type);
                continue;
            }

            const MachineConfig* config = &machine_configs[type];        // Use MachineType to index into machine_configs 

            printf("%s:", config->name);
            for (int s=0; s < config->num_sensors; s++) {
                const SensorConfig* sensor = &config->sensors[s];
                
                if (strlen(sensor->name) == 0) continue;                 // Skip invalid sensors

                float value = get_sensor_value(machines[i], sensor->name);
                if (s == 0) {
                    printf(" %s = %.2f\n",  
                        sensor->name, value);
                } else {
                    printf("                %s = %.2f\n",  
                        sensor->name, value);
                }
            }
        }
        printf("\n");
        k_msleep(5000);  // Sleep for 5 seconds before printing again
    }
}

// Start the threads
K_THREAD_DEFINE(blink0_id, STACKSIZE, blink0, NULL, NULL, NULL, PRIORITY, 0, 0);                    // Confirm the program is alive
K_THREAD_DEFINE(set_data_id, STACKSIZE, set_data, NULL, NULL, NULL, PRIORITY + 1, 0, 0);            // Read the sensor data into the machines
K_THREAD_DEFINE(print_data_id, STACKSIZE, print_data, NULL, NULL, NULL, PRIORITY + 2, 0, 0);        // Print the machine sensor values

int main(void) {
    
    printk("\n*** Program Start ***\n");                 // Program Start
    demo_init();                                         // Initialize the demo
    printk("Demo Message: %s\n", demo_get_message());    // Make sure C++ is working
    
    srand(time(NULL));          // Seed random number generator
    //generate_machines();        // Generate the machines

    tflite_setup();
    tflite_run_inference();

    while (1) {
        k_sleep(K_SECONDS(5));
        tflite_run_inference();
    }
    
    return 0;
}
