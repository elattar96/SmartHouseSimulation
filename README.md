# SmartHousetSimulation

The system is a smart controlled house and is consisted of 4 Electronic control units (ECUs) (AVR/Atemga32). 
All Microcontrollers have drivers for Microcontroller Abstraction Layer (MCAL) such as: DIO & Serial Communication 
drivers, Electronic Control Unit Abstraction Layer (ECUAL) such as: LCD & Keypad, and finally Application Layer.

1-Remote-Control ECU (RC ECU): 
  - It is a handheld device. 
  - Provides human interface for access and security control. 
  - Wireless interface with the main ECU through Bluetooth interface.

2-Main Unit and Gateway ECU (MUGW ECU): 
  - Wireless interface with the Remote-Control ECU through Bluetooth. 
  - Security verification after request from the RC ECU. 
  - Passing different commands from the RC ECU to the SR and AD ECUs.
  - Containing latest configurations requested by the EC ECU. 

3-Sensor Reading ECU (SR ECU): 
  - Interfacing 3 LM35 temperature sensors (TEMP).
  - Driving 3 LEDs simulating Air Conditioner motors (A/C).
  - Interfacing 3 light sensors (LDR). 
  - Driving 3 LEDs simulation light control (L).

4-Actuator drive ECU (AD ECU): 
  - Driving 3 RGB LEDs (ROOM). 
  - Driving 3 LEDs Simulation Doors (LED). 

