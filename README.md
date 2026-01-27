# Fingerprint Vehicle Starter with Drug Sensing

## Abstract
This project introduces a "Fingerprint Vehicle Starter with Drug Sensing" system to improve road safety. It ensures that only authorized users can start the vehicle using a fingerprint sensor. Additionally, an alcohol detection sensor (MQ-3) checks the driver for alcohol consumption and prevents the ignition if alcohol is detected. The system reduces both vehicle theft and accidents caused by impaired driving.

## Hardware Requirements
- Arduino Nano
- R307 Fingerprint Sensor
- MQ-3 Alcohol Sensor
- 16x2 LCD Display with I2C
- 1-Channel Relay Module
- Push Button
- LEDZero PCB
- 9V Power Supply

## Software Requirements
- Arduino IDE

## Block Diagram
![Block Diagram](images/block_diagram.png)

## Hardware Setup
![Hardware Setup](images/hardware_setup.png)

## Working Principle
1. Power the system using a 9V supply.
2. Scan the fingerprint using the R307 sensor.
3. If the fingerprint matches an authorized user, the system checks alcohol levels via the MQ-3 sensor.
4. If alcohol is detected above the threshold, the ignition is disabled.
5. If the user is authorized and sober, the ignition is activated, allowing the vehicle to start.

## Result
- Only authorized users can start the vehicle.
- Alcohol consumption prevents the vehicle from starting.
- Helps prevent theft and reduce road accidents.

## Patent Information
Patent filed in 2024 for "Fingerprint Vehicle Starter with Drug Sensing System".

## Full Project Report
The detailed project report including team members, staff, and college logo can be downloaded here: [Report](Fingerprint_Vehicle_Starter_Report.docx)

## Future Enhancements
- GPS tracking integration
- Mobile app-based authentication
- Cloud storage for fingerprints
