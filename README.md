# Sensor Management System

## Overview

The **Sensor Management System** is designed to manage and analyze various types of sensors, including **Tire Sensors** and **Power Management Units (PMUs)**. The system allows users to store, manipulate, and evaluate sensor data, providing information such as tire pressure, temperature, wear level, and the power status of power management units. The system supports operations on these sensors, such as checking their status, computing performance scores, and ensuring battery health.

## Features

- **Tire Sensors**:
  - Measure tire pressure, temperature, wear level, and performance score.
  - Perform operations like checking pressure, temperature, wear level, and performance score.

- **Power Management Units (PMUs)**:
  - Monitor voltage, current, power consumption, energy storage, and energy regeneration.
  - Perform operations like computing power output, regenerating energy, and checking battery health.

- **Operations**:
  - **Tire Sensors**:
    - `tire_pressure_status`: Checks if the tire has normal, high, low, or abnormal pressure.
    - `tire_temperature_status`: Checks if the tire temperature is within normal limits.
    - `tire_wear_level_status`: Displays the wear level status of the tire.
    - `tire_performance_score`: Calculates and displays the tire's performance score based on pressure, temperature, and wear level.
  
  - **PMUs**:
    - `pmu_compute_power`: Computes and displays the power output based on voltage and current.
    - `pmu_regenerate_energy`: Regenerates energy in the battery and updates the energy storage.
    - `pmu_get_energy_usage`: Displays the energy usage based on power consumption.
    - `pmu_is_battery_healthy`: Checks if the battery's voltage, current, power consumption, energy regeneration, and storage are within safe ranges.

## Implementation Details

The system uses **sensor types** and **sensor data structures** to manage the data for both Tire Sensors and Power Management Units:

- **Sensor Type**: 
  - **TIRE**: Represents a tire sensor.
  - **PMU**: Represents a power management unit sensor.

- **Sensor Data Structures**:
  - **Tire Sensor**: Stores data related to tire pressure, temperature, wear level, and performance score.
  - **Power Management Unit**: Stores data related to voltage, current, power consumption, energy storage, and energy regeneration.

The system supports a variety of operations that are executed dynamically. For instance, the tire performance score is calculated based on tire pressure, temperature, and wear level, while the PMU energy regeneration and power computation are essential for managing the power system health.

## File Structure

- **`structs.h`**: Contains data structures and enumerations for sensor types and sensor data.
- **`operations.h`**: Declares functions for various operations that can be performed on sensors.
- **`operations.c`**: Implements the sensor operations (e.g., checking tire pressure, computing power for PMUs).
- **`main.c`**: Manages sensor input, processes operations, and handles user commands.
