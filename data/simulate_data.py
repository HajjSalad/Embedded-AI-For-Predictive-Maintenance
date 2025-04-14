import os
import random
import pandas as pd
from datetime import datetime

# Simulate temperature data
def generate_temp_data(machine_id, num_samples):
    if machine_id == 1:
        temp_range = (60, 100)      # Air Compressor
    elif machine_id == 2:
        temp_range = (150, 250)     # Steam Boiler
    elif machine_id == 3:
        temp_range = (60, 105)      # Electric Motor
    else:
        temp_range = (60, 100)

    # Generate simulated temp data
    temp_data = []
    for _ in range(num_samples):
        temp_value = random.uniform(*temp_range)                    # Gen
        timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        temp_data.append([timestamp, temp_value])

    # Create DataFrame
    df = pd.DataFrame(temp_data, columns=["timestamp", "temperature"])

    return df

# Simulate pressure data
def generate_pressure_data(machine_id, num_samples):
    if machine_id == 1:
        pressure_range = (72, 145)  
    elif machine_id == 2:
        pressure_range = (87, 360)  
    else:
        pressure_range = (70, 150)

    pressure_data = []
    for _ in range(num_samples):
        pressure_value = random.uniform(*pressure_range)
        timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        pressure_data.append([timestamp, pressure_value])

    df = pd.DataFrame(pressure_data, columns=["timestamp", "pressure"])
    return df

# Simulate vibration data
def generate_vibration_data(machine_id, num_samples):
    if machine_id == 1:
        vibration_range = (0.5, 2.0)
    else:
        vibration_range = (0.0, 1.5)

    vibration_data = []
    for _ in range(num_samples):
        vibration_value = random.uniform(*vibration_range)
        timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        vibration_data.append([timestamp, vibration_value])

    df = pd.DataFrame(vibration_data, columns=["timestamp", "vibration"])
    return df

# Simulate and store in CSV
def simulate_data():
    num_samples = 1000
    base_dir = "detection/data"

    # Machine 1 - Air Compressor
    machine_1_dir = os.path.join(base_dir, "machine_1")     # Join base_dir with machine_1 subdir
    os.makedirs(machine_1_dir, exist_ok=True)               # Create machine_1 dir, ok if it exists
    temp_df = generate_temp_data(1, num_samples)            # Generate temp simulated data
    # Save to CSV file
    temp_df.to_csv(os.path.join(machine_1_dir, "machine_1_temp.csv"), index=False)
    
    pressure_df = generate_pressure_data(1, num_samples)
    pressure_df.to_csv(os.path.join(machine_1_dir, "machine_1_pressure.csv"), index=False)
    
    vibration_df = generate_vibration_data(1, num_samples)
    vibration_df.to_csv(os.path.join(machine_1_dir, "machine_1_vibration.csv"), index=False)

    # Machine 2 - Steam Boiler
    machine_2_dir = os.path.join(base_dir, "machine_2")
    os.makedirs(machine_2_dir, exist_ok=True)

    temp_df = generate_temp_data(2, num_samples)
    temp_df.to_csv(os.path.join(machine_2_dir, "machine_2_temp.csv"), index=False)

    pressure_df = generate_pressure_data(2, num_samples)
    pressure_df.to_csv(os.path.join(machine_2_dir, "machine_2_pressure.csv"), index=False)

    # Machine 3 - Electric Motor
    machine_3_dir = os.path.join(base_dir, "machine_3")
    os.makedirs(machine_3_dir, exist_ok=True)

    temp_df = generate_temp_data(3, num_samples)
    temp_df.to_csv(os.path.join(machine_3_dir, "machine_3_temp.csv"), index=False)

    print("Data simulation complete!")

if __name__ == "__main__":
    simulate_data()


