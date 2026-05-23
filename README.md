
# ASPS – Automated Smart Parking System

> A smart parking system prototype integrating embedded systems, automation, and access control.

![ASPS Smart Parking System](assets/prototype/hero_prototype.jpeg)

---

## Problem Statement

Manual parking management systems face several challenges:

- **Inefficient space utilization** – drivers waste time searching for available slots  
- **No access control** – unauthorized vehicles can enter restricted areas  
- **Safety concerns** – lack of collision detection and emergency response  
- **No real-time monitoring** – parking availability is not communicated effectively  

ASPS addresses these challenges by integrating sensor-based automation, RFID authentication, and real-time status display into a unified parking management prototype.

---

## System Overview

ASPS is a dual-Arduino automated smart parking system that manages vehicle entry, parking slots, VIP access, and safety alerts using real sensors and actuators.

The architecture uses two Arduino Uno microcontrollers working in tandem:

- **Gate Access Controller** – Manages vehicle entry/exit, RFID authentication, gate operation, and slot occupancy tracking  
- **Parking Safety Controller** – Handles collision prevention, fire detection, and automatic lighting  

This dual-controller design enables modular operation and independent functionality while contributing to the overall parking automation workflow.

### Architectural Note

This project uses two Arduino Uno boards. Some functionalities (such as slot state awareness and LCD status display) appear in both controller sketches by design to simplify deployment, testing, and standalone operation of each controller during academic evaluation.

**Project Context:** University engineering project – ELE212 – Electrical Measurements & Measuring Instruments.

**Live Demo:** [Companion Web Interface](https://easy-park-tech.lovable.app)

---

## Hardware Components

| Component | Quantity | Purpose |
|---|---|---|
| Arduino Uno | 2 | Main microcontrollers (gate control + safety) |
| MFRC522 RFID Module | 1 | VIP access authentication |
| IR Sensors | 5 | Vehicle detection (entry, exit, 3 parking slots) |
| Ultrasonic Sensor (HC-SR04) | 1 | Anti-collision distance measurement |
| Servo Motors | 3 | Gate control (entry, exit, VIP) |
| LCD Display (16x2 I2C) | 1 | Real-time parking information |
| Flame Sensor | 1 | Fire detection |
| LDR Sensor | 1 | Ambient light measurement |
| Active Buzzer | 1 | Safety alerts and warnings |
| LED Indicators | 3+ | Slot occupancy status |
| Relay Module | 1 | Power switching control |

---

## How the System Works

### Parking Workflow

```text
1. Vehicle approaches entry gate
   ↓
2. IR sensor detects vehicle presence
   ↓
3. System checks available slots
   ↓
4a. Regular parking: gate opens automatically
4b. VIP access: RFID authentication → gate opens
   ↓
5. Servo motor operates the entry gate
   ↓
6. Vehicle enters the parking area
   ↓
7. Slot sensors update availability status
   ↓
8. LCD displays real-time parking information
   ↓
9. Exit gate opens automatically when vehicle detected
   ↓
10. System resets for the next vehicle
````

### Safety Monitoring (Continuous)

* **Collision Prevention:** Ultrasonic sensor monitors distance and triggers buzzer alerts at warning and danger thresholds
* **Fire Detection:** Flame sensor triggers an immediate alarm using a high-frequency buzzer tone
* **Auto Lighting:** LDR sensor activates LEDs when ambient light falls below a defined threshold

---

## Live Prototype Images

### Physical Hardware Implementation

![Complete Prototype Setup](assets/prototype/complete_prototype_setup.jpeg)

*Complete ASPS prototype showing dual Arduino controllers, servo gates, LCD display, RFID module, and parking slot sensors.*

### System Components

![Prototype Overview](assets/prototype/prototype_overview.jpeg)

*Detailed view of embedded components including Arduino boards, breadboard wiring, servo actuators, and sensor array.*

### Gate Mechanism

![Entry Gate Detail](assets/prototype/entry_gate_detail.jpeg)

*Servo-operated entry gate with IR sensor detection.*

![Exit Gate Detail](assets/prototype/exit_gate_detail.jpeg)

*Exit gate mechanism with automated operation.*

---

## Circuit Design

The system uses a distributed wiring architecture connecting two Arduino controllers to various sensors and actuators.

### Gate Access Controller Connections

* RFID module → SPI communication
* Servo motors → PWM control
* IR sensors → Digital input
* LCD display → I2C communication

### Safety Controller Connections

* Flame sensor → Digital input
* Ultrasonic sensor → Digital I/O
* Buzzer → PWM output
* LDR sensor → Analog input
* LED indicators → Digital outputs

### Communication Flow

```text
Sensors → Arduino (Processing Logic) → Actuators (Gates / LEDs / Buzzer)
                                    ↓
                               LCD Display (Status Output)
```

---

## Companion Website

This project includes a web-based companion platform as a conceptual interface for smart parking management.

🌐 **Live Website:** [https://easy-park-tech.lovable.app](https://easy-park-tech.lovable.app)

The web interface demonstrates how the physical prototype could integrate with a digital platform for:

* Remote monitoring of parking availability
* User-friendly visualization of slot occupancy
* Future remote parking monitoring extensions

---

## Project Structure

```text
ASPS_Arduino/
├── README.md
├── src/
│   ├── gate_access_controller.ino
│   └── parking_safety_controller.ino
└── assets/
    ├── prototype/
    │   ├── hero_prototype.jpeg
    │   ├── complete_prototype_setup.jpeg
    │   ├── prototype_overview.jpeg
    │   ├── entry_gate_detail.jpeg
    │   └── exit_gate_detail.jpeg
    ├── renders/
    └── diagrams/
```

### Source Code

#### `src/gate_access_controller.ino`

Handles:

* vehicle entry/exit automation
* RFID authentication
* gate servo control
* slot occupancy tracking
* LCD display updates

#### `src/parking_safety_controller.ino`

Handles:

* collision prevention
* fire detection
* automatic lighting control
* buzzer alarm system

> Note on architecture: The project intentionally uses two separate Arduino Uno boards with some overlapping functionality to simplify deployment, testing, and standalone subsystem operation during academic evaluation.

---

## Technologies Used

| Category  | Technologies                                     |
| --------- | ------------------------------------------------ |
| Hardware  | Arduino Uno, RFID, IR sensors, ultrasonic sensor |
| Actuation | Servo motors, relay module, buzzer, LEDs         |
| Interface | 16x2 I2C LCD display                             |
| Software  | C/C++ (Arduino Framework), Arduino IDE           |
| Protocols | SPI, I2C, PWM, Digital/Analog I/O                |
| Website   | Lovable companion web interface                  |

---

## Project Notes

### Academic Context

This project was developed as part of **ELE212 – Electrical Measurements & Measuring Instruments**, demonstrating practical application of:

* sensor integration
* real-time embedded programming
* actuator control
* modular system design

### Design Considerations

* Modular architecture allows independent testing of subsystems
* Non-blocking logic enables continuous sensor monitoring
* State-based control manages gate operations and safety alerts
* Threshold-triggered responses handle collision and fire events

### Future Enhancements

* Add Wi-Fi or Bluetooth connectivity for remote monitoring
* Implement direct controller communication (I2C/SPI)
* Extend notifications through a lightweight mobile/web interface

---

### Author
* **Mark Amgad Nassief Botros Mekhaiel**
  * *Artificial Intelligence Engineering Student*
  * *Faculty of Computer Science and Engineering*
  * *New Mansoura University*
