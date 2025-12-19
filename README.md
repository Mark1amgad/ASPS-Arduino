# Automated Smart Parking System (ASPS)

University engineering project – real hardware implementation.

## Project Description
ASPS is a dual-Arduino automated smart parking system designed to manage vehicle entry, parking slots, VIP access, and safety alerts using real sensors and actuators.

## Architectural Note
This project uses two Arduino Uno boards. Some functionalities (such as slot state awareness and LCD status display) may appear in both controller sketches. This overlap is intentional and was done to simplify deployment, testing, and standalone operation of each controller during the academic evaluation phase. It does not represent a design error or incomplete separation.

## Hardware Overview
- 2 × Arduino Uno
- IR sensors (entry, exit, 3 slots)
- Ultrasonic sensor (anti-collision)
- RFID module (VIP access)
- Servo motors (gates)
- LCD display
- Buzzer
- LDR sensor
- Flame sensor

## Repository Structure
- src/ → Arduino source code

## Project Type
Hardware-based system (no cloud, no mobile app)
