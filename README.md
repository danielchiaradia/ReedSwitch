# ReedSwitch
Simple Door/Window contact with low quiescence current of around 5µA. 
BOM:
- Wemos D1 Mini or alternative ESP development board (you can build the box with a much lower profile by using ESP01).
- Attiny85
- Li-ion or any alternative with a supply voltage of 3-5V
- 3K3 Ohm resistor
- 680 Ohm resistor
- 410 µF capacitor
- Reed Switch with two terminals or alternatively a closed open reed switch.
- 1xP-Channel MOSFET (e.g.NDP6020P)

The attiny will be turned on by the reed switch and then turns the ESP via the MOSFET on. The ESP sends the current state of the reed switch to a REST service. After sending the data, the ESP pulls the MOSFET gate high and turns itself off.

Schematic:
![Schematic](https://github.com/danielchiaradia/ReedSwitch/blob/main/assets/Schematic.PNG)

Quiescence current:
![Current](https://github.com/danielchiaradia/ReedSwitch/blob/main/assets/consumption.jpg)

Enclosure
![Enclosure](https://github.com/danielchiaradia/ReedSwitch/blob/main/assets/enclosure.jpg)
