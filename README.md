# ASPS – Automated Smart Parking System

> A smart parking system prototype integrating embedded systems, automation, and access control.

![Smart Parking System Concept](WhatsApp%20Image%202026-01-26%20at%203.25.31%20AM%20(1).jpeg)
*Conceptual visualization of the ASPS smart parking automation system*

---

## Overview

**Automated Smart Parking System (ASPS)** is an embedded systems engineering prototype that automates vehicle entry, parking slot management, VIP access control, and real-time safety monitoring. Built using dual Arduino microcontrollers with RFID authentication, infrared sensors, and servo actuators, this project demonstrates practical implementation of sensor integration and automation logic.

**Project Context:** University engineering project – ELE212 (Embedded Systems & Automation)  
**Live Demo:** [Companion Web Interface](https://easy-park-tech.lovable.app)

---

## Problem Statement

Manual parking management systems face several challenges:
- **Inefficient space utilization** – drivers waste time searching for available slots
- **No access control** – unauthorized vehicles can enter restricted areas
- **Safety concerns** – lack of collision detection and emergency response
- **No real-time monitoring** – parking availability is not communicated effectively

**ASPS addresses these challenges** by integrating sensor-based automation, RFID authentication, and real-time status display into a unified parking management prototype.

---

## System Overview

The ASPS architecture uses **two Arduino Uno microcontrollers** working in tandem:

1. **Gate Access Controller** – Manages vehicle entry/exit, RFID authentication, gate operation, and slot occupancy tracking
2. **Parking Safety Controller** – Handles collision prevention, fire detection, and automatic lighting

This dual-controller design ensures **modular operation** and **independent functionality**, allowing each subsystem to operate autonomously while contributing to the overall parking automation workflow.

### Key Features

✓ **RFID-based VIP access control** with authorized card authentication  
✓ **Automated gate operation** using servo motors (entry, exit, VIP)  
✓ **Real-time slot occupancy detection** via infrared sensors  
✓ **Collision prevention system** with ultrasonic distance measurement  
✓ **Fire detection and alarm** with buzzer notification  
✓ **Automatic lighting control** based on ambient light conditions  
✓ **LCD status display** showing available slots and gate status  
✓ **Visual indicators** (LEDs) for parking slot states  

---

## System Workflow

```
Vehicle Approaches Entry Gate
         ↓
RFID Card Authentication
         ↓
System Checks Slot Availability
         ↓
   ┌─────┴─────┐
   ↓           ↓
Regular     VIP Access
Parking     (RFID Auth)
   ↓           ↓
Gate Opens via Servo Motor
         ↓
Vehicle Enters Parking Area
         ↓
IR Sensors Detect Occupancy
         ↓
LCD Updates Available Slots
         ↓
LEDs Indicate Slot Status
         ↓
Exit Gate Opens on Detection
         ↓
System State Updates
```

### Safety Monitoring (Continuous)

- **Collision Prevention:** Ultrasonic sensor monitors distance; buzzer alerts at warning (<10cm) and danger (<2cm) thresholds
- **Fire Detection:** Flame sensor triggers immediate alarm with 2500Hz buzzer tone
- **Auto Lighting:** LDR sensor activates LEDs when ambient light falls below threshold

---

## Live Prototype

**Real hardware implementation** – from concept to physical prototype.

### Complete System Setup

![Complete Prototype Setup](WhatsApp%20Image%202026-01-26%20at%203.25.31%20AM%20(1).jpeg)
*Physical ASPS prototype showing dual Arduino controllers, servo gates, LCD display, RFID module, and parking slot sensors*

### Embedded Components

![Prototype Components](WhatsApp%20Image%202026-01-26%20at%203.25.31%20AM.jpeg)
*Detailed view of embedded components: Arduino boards, breadboard wiring, servo actuators, and sensor array*

### Gate Mechanisms

![Entry Gate](WhatsApp%20Image%202026-02-11%20at%204.23.41%20AM.jpeg)
*Servo-operated entry gate with IR sensor detection*

![Exit Gate](WhatsApp%20Image%202026-02-11%20at%204.36.09%20AM.jpeg)
*Exit gate mechanism with automated operation*

---

## Hardware Components

| Component | Quantity | Purpose |
|-----------|----------|---------|
| Arduino Uno | 2 | Main microcontrollers (gate control + safety) |
| MFRC522 RFID Module | 1 | Vehicle/user authentication |
| IR Sensors | 5 | Vehicle detection (entry, exit, 3 slots) |
| Ultrasonic Sensor (HC-SR04) | 1 | Anti-collision distance measurement |
| Servo Motors | 3 | Automatic gate control (entry, exit, VIP) |
| LCD Display (16x2 I2C) | 1 | Parking information display |
| Flame Sensor | 1 | Fire detection |
| LDR Sensor | 1 | Ambient light measurement |
| Active Buzzer | 1 | Status and alerts |
| LED Indicators | 3+ | Slot occupancy status |
| Relay Module | 1 | Power switching control |

---

## Circuit Design

The system uses a distributed wiring architecture connecting two Arduino controllers to various sensors and actuators:

### Gate Access Controller Connections
- **RFID Module:** SPI communication (pins 9, 10)
- **Servo Motors:** PWM control (pins 2, 3, 8)
- **IR Sensors:** Digital input (pins 4, 5, A1, A2, A3)
- **LCD Display:** I2C communication

### Safety Controller Connections
- **Flame Sensor:** Digital input (pin 2)
- **Ultrasonic Sensor:** Digital I/O (pins 3, 4)
- **Buzzer:** PWM output (pin 5)
- **LDR Sensor:** Analog input (pin A0)
- **LED Indicators:** Digital output (pin 7)

### Communication Flow
```
Sensors → Arduino (Processing Logic) → Actuators (Gates/LEDs/Buzzer)
                                    ↓
                                 LCD Display (Status Output)
```

The dual-controller architecture ensures each subsystem maintains independent operation while sharing critical state information (slot occupancy, gate status) for coordinated system behavior.

---

## Companion Website

This project also includes a **web-based companion platform** that serves as a conceptual interface for smart parking management:

🌐 **Live Website:** [https://easy-park-tech.lovable.app](https://easy-park-tech.lovable.app)

The web interface demonstrates how the physical prototype could integrate with a digital platform for:
- Remote monitoring of parking availability
- User-friendly visualization of slot occupancy
- Potential expansion to full IoT parking management system

---

## Project Structure

```
ASPS_Github/
├── README.md                          # Project documentation
├── src/
│   ├── gate_access_controller.ino     # Arduino sketch: entry/exit gates, RFID, slot tracking
│   ├── parking_safety_controller.ino  # Arduino sketch: collision, fire detection, auto lighting
│   └── README.md                      # Source code overview
├── WhatsApp Image 2026-01-26 at 3.25.31 AM (1).jpeg  # Complete prototype photo
├── WhatsApp Image 2026-01-26 at 3.25.31 AM.jpeg      # Component detail photo
├── WhatsApp Image 2026-02-11 at 4.23.41 AM.jpeg      # Entry gate detail
── WhatsApp Image 2026-02-11 at 4.36.09 AM.jpeg      # Exit gate detail
```

### Source Code

**[gate_access_controller.ino](src/gate_access_controller.ino)**  
Handles vehicle entry/exit automation, RFID authentication, gate servo control, slot occupancy tracking, and LCD display updates.

**[parking_safety_controller.ino](src/parking_safety_controller.ino)**  
Manages collision prevention via ultrasonic sensor, fire detection with flame sensor, automatic lighting control using LDR, and buzzer alarm system.

> **Note on Architecture:** This project intentionally uses two separate Arduino Uno boards with some overlapping functionality (such as slot state awareness). This design choice was made to simplify deployment, testing, and standalone operation of each controller during the academic evaluation phase. Each controller can operate independently while contributing to the overall system.

---

## Project Notes

### Academic Context
This project was developed as part of **ELE212 – Embedded Systems & Automation**, demonstrating practical application of:
- Sensor integration and signal processing
- Real-time embedded system programming
- Actuator control and feedback systems
- System architecture and modular design

### Design Considerations
- **Modular architecture** allows independent testing of subsystems
- **Non-blocking code** structure ensures continuous sensor monitoring
- **State machine logic** manages gate operations and safety alerts
- **Threshold-based triggering** for collision prevention and fire detection

### Future Enhancements
Potential improvements for production-scale deployment:
- IoT connectivity (Wi-Fi/Bluetooth) for cloud integration
- Multi-board communication (I2C/SPI between controllers)
- Advanced RFID database management
- Camera-based license plate recognition
- Mobile app integration for real-time notifications
- Database logging for usage analytics

---

## Author

**Mark Amgad Nassief Botros Mekhaiel**  
*Artificial Intelligence Engineering Student*  
Faculty of Computer Science and Engineering  
New Mansoura University

---

**Built with Arduino • Designed for Smart Parking Automation • Engineered for Real-World Application**
