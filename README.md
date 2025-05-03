# # Air Quality Monitor

A real-time gas level monitoring system using STM32F4 microcontroller, MQ2 gas sensor, and NodeMCU ESP8266 with Blynk cloud integration.

## Project Overview

This project implements a portable, reliable, and cost-effective gas detection system that provides real-time feedback through cloud integration. The system detects combustible gases and smoke concentrations ranging from 300 to 10,000 ppm and visualizes the data on a customized Blynk dashboard.

## System Architecture

The system consists of three main components connected in a chain topology:

1. **Sensing Unit**: MQ2 gas sensor interfaced with STM32F4 microcontroller
2. **Processing Unit**: STM32F4 Nucleo board performing ADC conversion and UART communication
3. **Communication Unit**: NodeMCU ESP8266 providing Wi-Fi connectivity and cloud integration
4. **Visualization Platform**: Blynk cloud dashboard for real-time monitoring

## Hardware Requirements

- STM32F4 Nucleo development board
- MQ2 gas sensor
- NodeMCU ESP8266 Wi-Fi module
- Connecting wires
- Power supply (USB)

## Software Requirements

- Keil μVision IDE for STM32 programming
- Arduino IDE for ESP8266 programming
- STM32CubeMX for initial configuration
- Blynk IoT platform account and app

## Connection Details

### MQ2 Gas Sensor to STM32F4 Connections
| MQ2 Pin | STM32F4 Pin | Signal Type | Description |
|---------|-------------|-------------|-------------|
| Vin     | 3.3V        | Power       | 3.3V power supply for the sensor |
| GND     | GND         | Ground      | Common ground connection |
| A0      | PA0         | Analog      | Analog sensor output to ADC input |

### STM32F4 to NodeMCU ESP8266 Connections
| STM32F4 Pin    | NodeMCU Pin | Signal Type | Description |
|----------------|-------------|-------------|-------------|
| PD8 (UART3 TX) | D5 (RX)     | Digital     | Serial data transmission line |
| GND            | GND         | Ground      | Common ground connection |

## Setup Instructions

### Hardware Setup
1. Connect the MQ2 sensor to the STM32F4 according to the connection table
2. Connect the STM32F4 to the NodeMCU ESP8266 according to the connection table
3. Power both the STM32F4 and ESP8266 using appropriate USB connections

### STM32F4 Setup
1. Clone this repository
2. Open the project in Keil μVision IDE
3. Build and flash the code to the STM32F4 Nucleo board

### ESP8266 Setup
1. Install the Arduino IDE
2. Add ESP8266 board support to Arduino IDE
3. Install the Blynk library using the Arduino Library Manager
4. Update the Wi-Fi credentials and Blynk authentication token in the ESP8266 code
5. Upload the code to the NodeMCU ESP8266

### Blynk Setup
1. Download the Blynk app on your mobile device
2. Create a new project
3. Add a gauge widget and set it to Virtual Pin V1
4. Add a SuperChart widget for historical data visualization
5. Configure notification thresholds for high gas levels

## Usage

1. Power on both the STM32F4 and ESP8266
2. The system will automatically connect to the configured Wi-Fi network
3. Open the Blynk app to monitor gas levels in real-time
4. The system will send notifications when gas levels exceed the configured threshold

## Key Features

- Real-time gas level monitoring
- Cloud-based data visualization
- Alert notifications for high gas concentrations
- Historical data tracking and analysis
- Low power consumption for extended operation

## Customization

- Adjust the notification threshold in the ESP8266 code to change when alerts are triggered
- Modify the polling interval by changing the delay value in the STM32F4 code
- Add additional sensors by expanding the ADC and UART configuration

## Troubleshooting

- **No data in Blynk dashboard**: Check Wi-Fi connection and Blynk authentication token
- **Inaccurate readings**: Ensure proper calibration of the MQ2 sensor
- **Communication issues**: Verify UART connections and baud rate settings

- Hanwei Electronics for MQ2 sensor documentation
- Espressif Systems for ESP8266 documentation
- Blynk for IoT platform

## License

This project is open-source and available for educational and personal use.
