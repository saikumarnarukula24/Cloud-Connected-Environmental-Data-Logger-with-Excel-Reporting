# Cloud-Connected-Environmental-Data-Logger-with-Excel-Reporting
The Cloud-Connected Environmental Data Logger with Excel Reporting is an embedded system that monitors temperature, humidity, and gas levels using sensors. The data is uploaded to the cloud for remote access and stored in Excel reports for analysis, helping in real-time environmental monitoring and easy data management.

# Description

This project is implemented using the LPC2148 ARM7 microcontroller and integrates multiple peripherals including ADC, RTC, UART, I2C EEPROM, LCD, keypad, gas sensor, temperature sensor, and ESP01 Wi-Fi module.

The LM35 sensor is used to measure temperature, while the MQ-2 sensor detects gas or smoke leakage conditions. The LPC2148 processes all sensor data and displays live information on a 16x2 LCD.

Using the ESP01 Wi-Fi module, the system uploads environmental data to the ThingSpeak cloud platform for remote monitoring. The system also supports threshold-based alerts using a buzzer whenever abnormal environmental conditions are detected.

User-configurable temperature set points are stored inside EEPROM to retain values even during power failures. The project also supports RTC editing through a keypad interface for flexible date and time management.

This project demonstrates real-time embedded monitoring, cloud connectivity, EEPROM data management, and IoT-based environmental logging in a single integrated system.

# Block diagram
<img width="890" height="603" alt="block" src="https://github.com/user-attachments/assets/e87c6f77-3b51-40ba-90ad-68a07c44c8f6" />

# Components Used

* LPC2148 Microcontroller
* ESP01 Wi-Fi Module
* LM35 Temperature Sensor
* MQ2 Gas Sensor
* LCD Display
* EEPROM
* Power Supply Unit
* Embedded C Programming

# System connections
<img width="1280" height="572" alt="connections" src="https://github.com/user-attachments/assets/05cf4e96-6dc9-48c4-ad3a-882fdc3dac7a" />

# Working Principle

1. Sensors continuously collect environmental data.
2. The microcontroller processes the sensor readings.
3. Data is displayed on the LCD screen.
4. ESP01 sends the data to the cloud platform.
5. Logged data is stored and exported into Excel reports for analysis.

# Importance of the Project

Environmental monitoring plays an important role in maintaining safety, health, and industrial efficiency. Manual monitoring methods are time-consuming and less accurate. This project provides an automated and smart monitoring system that offers:

* Continuous real-time monitoring
* Fast detection of harmful environmental changes
* Improved workplace and public safety
* Easy maintenance of historical data
* Remote accessibility through cloud technology
* Accurate data analysis using Excel reports

The project is highly useful in modern IoT and smart monitoring applications where real-time environmental tracking is required.

# Project outputs
## Hardware
<img width="1600" height="1200" alt="output" src="https://github.com/user-attachments/assets/5103d9a1-0a84-4427-84c1-10520eb83cbe" />

## Output

### Normal Monitoring Mode


06:50:26  T:30°C

11/03/26  SMOKE:0


- Real-time clock and date displayed using RTC

- Live temperature displayed from LM35 sensor

- Smoke detection status displayed from MQ-2 sensor

---

### Temperature Alert Mode


Warning...

Temp>Set Point


- Alert message displayed when temperature exceeds predefined threshold

- Buzzer indication activated during warning condition

- Alert information uploaded to cloud platform

---

### Cloud Output

Temperature values and smoke detection status are uploaded to ThingSpeak cloud for remote monitoring and Excel-based reporting.

---

### Alert Condition


\\\[ALERT] High Temperature Warning

\\\[ALERT] Gas Leakage Detected


## Cloud 
<img width="1281" height="832" alt="cloud" src="https://github.com/user-attachments/assets/f8dc4e13-01b3-430e-b847-528d20354ca8" />

## clould excel sheet

<img width="991" height="664" alt="excel" src="https://github.com/user-attachments/assets/c46d5e91-4d73-4aae-b2ad-9d50855d0645" />

# Applications

* Smart Environment Monitoring
* Industrial Safety Systems
* Weather Monitoring Stations
* Air Quality Monitoring
* IoT-based Monitoring Systems

# Real-Time Applications

This project can be used in many real-world applications such as:

## Industrial Monitoring:
Used in factories and industries to monitor temperature, humidity, and gas leakage for worker safety and equipment protection.

## Smart Agriculture:
Helps farmers monitor environmental conditions inside farms and greenhouses for better crop growth.

## Weather Monitoring Stations:
Used for collecting and analyzing weather-related environmental data.

## Air Quality Monitoring:
Monitors harmful gases and pollution levels in urban and industrial areas.

## Laboratories and Hospitals:
Maintains controlled environmental conditions for sensitive equipment and medicines.

## Smart Homes and Smart Cities:
Used in IoT-based automation systems for environmental safety and intelligent monitoring.

## Data Centers and Server Rooms:
Monitors temperature and humidity to protect electronic devices from overheating.

# Technologies Used

* Embedded C
* IoT
* UART Communication
* Cloud Integration
* Excel Data Logging

# Advantages
* Low power consumption
* Remote monitoring capability
* Automatic report generation
* Accurate and reliable data collection
* Easy to implement and maintain
* Cost-effective monitoring solution

# Features

* Real-time environmental monitoring
* Temperature, humidity, and gas detection
* Cloud connectivity using Wi-Fi module
* Automatic data logging
* Excel report generation
* Remote data access and monitoring
* User-friendly embedded system design

# Future Enhancements

* Mobile Application Integration
* Real-time Alerts and Notifications
* Advanced Data Analytics
* AI-based Environmental Prediction

# Conclusion

The Cloud-Connected Environmental Data Logger with Excel Reporting is an efficient IoT-based monitoring system that provides real-time environmental data collection, cloud storage, and report generation. The project demonstrates the practical implementation of embedded systems, IoT communication, and cloud technologies in solving real-world environmental monitoring challenges.
  


