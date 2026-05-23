
# ASPS – Automated Smart Parking System

> A smart parking system prototype integrating embedded systems, automation, and access control using Arduino-based hardware and real-time sensor interaction.

![ASPS Smart Parking System](assets/prototype/hero_prototype.jpeg)

---

## Problem Statement

Traditional parking systems suffer from inefficient space management, lack of automated monitoring, and weak access control mechanisms. Drivers waste time searching for available parking spaces, while parking operators struggle to track occupancy and maintain safety.

ASPS addresses these challenges through an embedded systems prototype that combines automated gate control, RFID authentication, parking occupancy detection, and real-time status monitoring.

---

## System Overview

ASPS is a dual-Arduino automated smart parking prototype designed to simulate intelligent parking management using real sensors, actuators, and embedded control systems.

The system is divided into two independent subsystems:

- **Gate Access Controller**  
  Handles vehicle entry and exit, RFID authentication, parking slot tracking, LCD status updates, and servo gate operation.

- **Parking Safety Controller**  
  Handles collision prevention, fire detection, automatic lighting, and emergency alerts using sensors and actuators.

This modular architecture allows each subsystem to operate independently while contributing to the overall parking automation workflow.

**Project Context:**  
University engineering project developed for:

**ELE212 – Electrical Measurements & Measuring Instruments**

🌐 **Companion Website:**  
https://easy-park-tech.lovable.app

---

## Hardware Overview

- 2 × Arduino Uno
- RFID module
- IR sensors
- Ultrasonic sensor
- Servo motors
- LCD display
- Flame sensor
- LDR sensor
- Buzzer
- LEDs
- Relay module

---

## Hardware Components

| Component | Purpose |
|---|---|
| Arduino Uno | Main microcontrollers |
| RFID Module | Vehicle / VIP authentication |
| IR Sensors | Vehicle and slot detection |
| Ultrasonic Sensor | Collision prevention |
| Servo Motors | Automatic gate control |
| LCD Display | Real-time parking information |
| Flame Sensor | Fire detection |
| LDR Sensor | Automatic lighting control |
| Buzzer | Safety alerts |
| LEDs | Parking status indication |
| Relay Module | Power switching control |

---

## System Workflow

```text
Vehicle Detection
        ↓
RFID Authentication
        ↓
Gate Opens via Servo Motor
        ↓
Vehicle Enters Parking Area
        ↓
IR Sensors Update Slot Occupancy
        ↓
LCD Displays Available Spaces
        ↓
Safety System Monitors Environment
````

### Safety Monitoring

* Ultrasonic sensor monitors nearby obstacles and activates warning alerts
* Flame sensor triggers emergency buzzer notifications
* LDR sensor enables automatic lighting under low-light conditions

---

## Live Prototype Images

### Physical Hardware Implementation

![Real Hardware Implementation](assets/prototype/real_implementation.jpeg)

---

## Circuit Design

![Circuit Diagram](assets/diagrams/circuit_diagram.jpeg)

The system wiring integrates two Arduino Uno controllers with multiple sensors and actuators using digital, analog, PWM, SPI, and I2C communication.

### Gate Access Controller

Handles:

* RFID authentication
* gate servo control
* parking slot monitoring
* LCD updates

### Parking Safety Controller

Handles:

* collision prevention
* fire detection
* lighting automation
* buzzer alerts

---

## Companion Website

The project also includes a companion web interface concept for smart parking management and visualization.

🌐 [https://easy-park-tech.lovable.app](https://easy-park-tech.lovable.app)

The website demonstrates how the embedded prototype could integrate with a lightweight digital parking management platform.

---

## Project Structure

```text
ASPS-Arduino/
├── README.md
├── .gitignore
│
├── src/
│   ├── gate_access_controller.ino
│   └── parking_safety_controller.ino
│
└── assets/
    ├── prototype/
    │   ├── hero_prototype.jpeg
    │   └── real_implementation.jpeg
    │
    ├── renders/
    │   └── smart_parking_render.jpeg
    │
    └── diagrams/
        └── circuit_diagram.jpeg
```

---

## Source Code

### `src/gate_access_controller.ino`

Responsible for:

* vehicle entry and exit automation
* RFID authentication
* servo-controlled gates
* parking slot tracking
* LCD status display

### `src/parking_safety_controller.ino`

Responsible for:

* collision detection
* fire alerts
* automatic lighting
* environmental safety monitoring

---

## Technologies Used

| Category      | Technologies                                     |
| ------------- | ------------------------------------------------ |
| Hardware      | Arduino Uno, RFID, IR sensors, ultrasonic sensor |
| Actuation     | Servo motors, relay module, buzzer, LEDs         |
| Interface     | 16x2 LCD Display                                 |
| Software      | Arduino IDE, Embedded C/C++                      |
| Communication | SPI, I2C, PWM, Digital & Analog I/O              |
| Website       | Lovable                                          |

---

## Project Notes

* Modular dual-controller architecture simplifies subsystem testing and deployment
* Embedded workflow focuses on automation and real-time sensor interaction
* Designed as a practical engineering prototype rather than a production parking infrastructure system

### Possible Future Extensions

* Wi-Fi or Bluetooth remote monitoring
* Mobile notifications
* Centralized controller communication

---

## Team Project

This project was developed as a university engineering team project as part of the ELE212 course.

---

### Author
* **Mark Amgad Nassief Botros Mekhaiel**
  * *Artificial Intelligence Engineering Student*
  * *Faculty of Computer Science and Engineering*
  * *New Mansoura University*
