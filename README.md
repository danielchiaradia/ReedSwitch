# ReedSwitch
Simple Door/Window contact with low quiescence current of around 5µA (according to my cheap multimeter ...). There is quite some power loss on the ESP development board caused by the regulator, serial converter and other components. However, it will only be powered for a short amount time, so it's not worth going the hard naked ESP way here.

# BOM
- ESP01
- Attiny85
- LiFePO4 Battery
- 2 x 3K3 Ohm resistor
- 410 µF capacitor
- Reed Switch with two terminals or alternatively a normally closed reed switch.
- 1xP-Channel MOSFET (e.g.NDP6020P)

# How it works
The attiny will be turned on by the reed switch and then turns the ESP via the MOSFET on. The ESP sends the current state of the reed switch to a REST service. After sending the data, the ESP signals to the attiny to turn of the power.

# Quiescence current
Around 5-10 µA with closed reed switch. Open switch will cause around 20-30 µA current (probably the closed terminal draws some current)
