# ESPUI WS2812FX Web Interface (Access Point Mode)

This project is the result of testing the ESPUI library to create a standalone web interface for controlling WS2812FX LED effects. The ESP32 runs in Access Point (AP) mode, allowing direct connection without a router.

Features

* Standalone ESP32 Access Point

* Web-based UI for selecting WS2812FX effects, brightness, speed, and color

* Built using the ESPUI library for simple, responsive controls

* No need for external server or internet connection


Ideal for offline light installations, quick demos, or portable LED projects.


## Screenshots

![Web Interface Screenshot - Smartphone](https://github.com/BlockThor/ESPUI-web-interace-for-WS2812FX-with-AccessPoint/blob/main/Screenshots/ESPUI-WS2812FX-WebAP%20-%20Phone.jpg?raw=true?text=App+Screenshot+Here)

![Web Interface Screenshot - Tab](https://github.com/BlockThor/ESPUI-web-interace-for-WS2812FX-with-AccessPoint/blob/main/Screenshots/ESPUI-WS2812FX-WebAP%20-%20Tab.jpg?raw=true?text=App+Screenshot+Here)


## ToDo

[ ] Timer for switch-off WiFi  
[ ] Time for On-Off LED (night mode???)   
[ ] Settings: IP Address   
[ ] Master/Slave (in case two sets)


## Tested with:
- ESP32 Matrix (ESP32S3 Dev Module), Pin 14 - Ok (keep bri at minimum for safety reason, can damage the pcb)
- TTGO T1 (ESP32-WROOM-DA Module) - Ok
- ESP32C3 - error, problem with AsyncWebServer / AsyncWebSocket.cpp  line: 832 return IPAddress(0U); ->> IPAddress(0UL);