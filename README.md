# analog-switch-hardware-validation
Analog switch test circuit design and hardware validation for an embedded control application

Project Overview

Capstone project required us to investigatw replacing mechanical relays with an analog switch that routes the manual vehicle signals and PS5 controller inputs to control the car. My part of the project so far has been developing a hardware testing approach to evaluate the functionality of SN3257 analog switches intended for a drive-by-wire system.
The tests are designed to simulate relevant operating conditions without requiring connection to an actual vehicle, allowing switching behavior to be evaluated before integration.

Test Design

I designed a test circuit and methodology using:

- Potentiometer: Simulates variable analog inputs from the vehicle's manual controls.
- Periodic LED blinking: Simulates PS5-generated control activity for testing purposes.
- ESP32 microcontroller: Provides control logic for selecting between manual and automated input paths.
- SN3257 analog switches: Route the selected analog input signals to the output.

Hardware Validation

I developed a phased testing approach to validate the analog switching circuitry before integration into the complete drive-by-wire system.
Initial testing uses a potentiometer to simulate variable analog signals from the vehicle's manual controls, while continuous periodic LED blinking serves as a simplified representation of PS5 control activity. This allows the switching circuitry to be evaluated under controlled conditions without introducing the additional complexity of the complete controller interface.

In parallel, I am investigating a supercapacitor-based power-loss mitigation solution proposed by a teammate to determine how the analog switches behave during power interruptions and whether the circuit can maintain the required functionality long enough to support manual operation.
Testing was performed across multiple channels to verify that the selected analog signals were correctly routed.
The testing also helped identify unexpected component behavior and potential hardware faults before system integration.


Tools and Skills
Altium Designer, ESP32, analog circuit testing, schematic design, datasheet interpretation, voltage measurements, hardware troubleshooting, and test procedure development.

Future works
- The next phase will incorporate the actual PS5 controller to evaluate signal routing and manual takeover behavior under more representative operating conditions.
- Drawing up a schematic for the new system with SN3257 instead of relays and routing the PCB, pending approval of our project mentor/client
