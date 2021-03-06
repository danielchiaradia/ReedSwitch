# ReedSwitch
Simple Door/Window contact with low quiescence current of around 5µA (according to my cheap multimeter ...). There is quite some power loss on the ESP development board caused by the regulator, serial converter and other components. However, it will only be powered for a short amount time, so it's not worth going the hard naked ESP way here.

# BOM
- Wemos D1 Mini or any other ESP development board
- Attiny85
- Li-ion or aN alternative power supply with a voltage of 3-5V
- 3K3 Ohm resistor
- 680 Ohm resistor
- 410 µF capacitor
- Reed Switch with two terminals or alternatively a normally closed reed switch.
- 1xP-Channel MOSFET (e.g.NDP6020P)

# How it works
The attiny will be turned on by the reed switch and then turns the ESP via the MOSFET on. The ESP sends the current state of the reed switch to a REST service. After sending the data, the ESP pulls the MOSFET gate high and turns itself off.

# Schematic
![Schematic](https://github.com/danielchiaradia/ReedSwitch/blob/main/assets/Schematic.PNG)

# Quiescence current
![Current](https://github.com/danielchiaradia/ReedSwitch/blob/main/assets/consumption.jpg)

# Enclosure
![Enclosure](https://github.com/danielchiaradia/ReedSwitch/blob/main/assets/enclosure.jpg)
