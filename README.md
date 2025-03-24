# Nursery-Enviroscan
Nursery Enviroscan is a compact and intelligent environmental monitoring device designed to measure and display temperature, humidity, and ambient light levels in a room. It's ideal for maintaining optimal conditions in nurseries, greenhouses, or any other indoor spaces.

# Capabilities
Sensor Readings: The device reads sensors to display temperature, humidity, and light-dependent resistance values on the OLED display.
Out-of-Range Alerts: Beeps and blinks the LED if values are above or below predefined thresholds.
Data Upload to Google Forms: The device sends and uploads sensor readings to Google Forms, enabling the data to be stored in Google Sheets for analysis.
WhatsApp Notifications: Sends messages over WhatsApp to notify users if values are above or below predefined thresholds.

# Connections
SSD1306 128x64 OLED: Connected to I2C pins for displaying readings.
DHT22 Temperature and Humidity Sensor: Connected to D7.
Light Dependent Resistor (LDR): Connected to analog pin for ambient light measurement.
LED: Connected to D5 for visual warnings.
Buzzer: Connected to D6 for audible alerts.
The board is powered by a 5-volt power adapter.

# Libraries to Be Included
ESP8266Wifi
SPI
Wire
Adafruit GFX
Adafruit SSD1306
DHT
WifiUdp
NTPClient
Arduino.h
GoogleFormPost by John Mueller / Softplus

# Contributions
Contributions are welcome! Feel free to open issues or submit pull requests to improve Nursery Enviroscan.

# Copyright Information
The libraries used in the code are under the ownership of their respective creators.

# License
This project is open-source for further improvements or updates.
