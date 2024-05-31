# Multithreaded-Order-Processing-System

## Overview
This project is a sophisticated C++ application designed to manage customer orders through multithreading. It efficiently processes orders across various workstations, ensuring synchronized and concurrent execution to enhance performance.

## Features
- Modular, object-oriented system architecture.
- Concurrent order processing using C++ standard threading library.
- Robust thread safety and synchronization mechanisms.
- Performance optimization and profiling.
- Comprehensive unit tests for validation.

## Project Structure
The project consists of the following key components:

- **CustomerOrder**: Manages customer orders, tracking details and fulfillment status.
- **Station**: Represents individual workstations in the production line.
- **Workstation**: Extends `Station` with task-specific processing logic.
- **LineManager**: Coordinates the overall order processing, assigning tasks to workstations.
- **Utilities**: Provides utility functions for parsing and validating input data.

## Files
- `main.cpp`: Main driver file.
- `CustomerOrder.cpp` and `CustomerOrder.h`: Implementation of customer order management.
- `LineManager.cpp` and `LineManager.h`: Implementation of the line manager.
- `Station.cpp` and `Station.h`: Implementation of workstations.
- `Utilities.cpp` and `Utilities.h`: Implementation of utility functions.
- `Workstation.cpp`: Implementation of task-specific workstation logic.
- `AssemblyLine.txt`: Configuration file for the assembly line.
- `CustomerOrders.txt`: Input file for customer orders.
- `Stations1.txt` and `Stations2.txt`: Input files for station details.
- `output_ms3_prof.txt`: Sample output file for reference.

## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/multithreaded-order-processing.git
   ```
2. Navigate to the project directory:
   ```bash
   cd multithreaded-order-processing
   ```
3. Compile the project:
   ```bash
   g++ -std=c++11 main.cpp CustomerOrder.cpp LineManager.cpp Station.cpp Utilities.cpp Workstation.cpp -o main -lpthread
   ```

## Usage
1. Ensure all input files (`Stations1.txt`, `Stations2.txt`, `CustomerOrders.txt`, `AssemblyLine.txt`) are in the project directory.
2. Run the compiled program:
   ```bash
   ./main Stations1.txt Stations2.txt CustomerOrders.txt AssemblyLine.txt
   ```
3. Check the output to verify correct processing.

## Output
The program will produce an output detailing the status of each order and the remaining inventory in each workstation. A sample output is provided in `output_ms3_prof.txt`.

## License
This project is licensed under the MIT License. See the `LICENSE` file for more details.

---
