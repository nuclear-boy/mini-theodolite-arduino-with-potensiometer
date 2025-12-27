## mini-theodolite-arduino-with-potensiometer
Inspired by the conventional theodolite used for measuring building heights, this device operates by converting ADC values from a potentiometer into angular measurements. By applying fundamental trigonometric principles, it calculates the height of the targeted object.

# necessary tools and tool kits
To make a potentiometer, we need several devices such as:
1. Arduino as a microcontroler
2. Potensiometer as an angle genetor
3. LCD 12X6 + I2C MODUL as a display devices
4. push button as a substitute for calculation logic

* I recommend that you connect all components via PCB. Here, I am not using jumper cables.

## Mathematical Model

![alt text](https://github.com/nuclear-boy/mini-theodolite-arduino-with-potensiometer/blob/main/the%20mathematical%20operation%20of%20the%20device.png?raw=true)

This project uses trigonometry to calculate the total height of an object ($h_2$) based on the fixed height of the measuring device ($h_1$) and two measured angles.

### Parameters
* **$h_1$**: The height of the device from the ground (Known constant).
* **$\theta_1$**: The angle of depression (from the horizontal line to the bottom of the object).
* **$\theta_2$**: The angle of elevation (from the horizontal line to the top of the object).
* **$d$**: The horizontal distance between the device and the object (Calculated).
* **$h_2$**: The total height of the object (Target variable).

### Calculation Logic

**1. Calculate Horizontal Distance ($d$)**
Using the bottom triangle and the known device height ($h_1$), we first determine the distance to the object:

$$
d = \frac{h_1}{\tan(\theta_1)}
$$

**2. Calculate Total Height ($h_2$)**
Once $d$ is known, we calculate the upper portion of the object and add it to the device's height:

$$
h_2 = h_1 + (d \cdot \tan(\theta_2))
$$

**Combined Formula:**
The entire operation can be expressed in a single equation:

$$
h_2 = h_1 \left( 1 + \frac{\tan(\theta_2)}{\tan(\theta_1)} \right)
$$

# Hardware Assembly Guide: Mini Theodolite Arduino
![alt text](https://github.com/nuclear-boy/mini-theodolite-arduino-with-potensiometer/blob/main/interconnection%20between%20devices.png?raw=true)

Step 1: Gather Tools and Components Before you begin, ensure your workbench is organized. You will need a soldering iron, solder wire, wire cutters, and a multimeter. For the components, prepare your Arduino (Nano/Uno), the LCD screen (with I2C module), a 10k Ohm potentiometer, a tactile push button, and the PCB board.

Step 2: Solder the Power Connections (5V and GND) Begin by establishing the power distribution lines on your PCB. Solder a connection from the Arduino's 5V pin to the VCC pin on the LCD and the Left Leg of the potentiometer. Next, solder a connection from the Arduino's GND pin to the GND pin on the LCD and the Right Leg of the potentiometer. This ensures all sensors and displays receive power.

Step 3: Connect the LCD Data Lines Connect the communication wires between the Arduino and the screen. Solder a wire from Arduino Pin A4 to the SDA pin on the LCD module. Then, solder a wire from Arduino Pin A5 to the SCL pin on the LCD module. These I2C connections allow the Arduino to transmit text and numerical data to the display.

Step 4: Connect the Potentiometer Signal This step is critical for angle measurement. Solder the Middle Pin (Wiper) of the potentiometer directly to Arduino Pin A0. This analog connection allows the Arduino to read voltage changes as you turn the knob, which translates into angle readings.

Step 5: Install the Logic Control Button (New Step) To enable mode switching and resetting calculations, install the push button. Solder one leg of the button to Arduino Digital Pin D2. Solder the diagonally opposite leg of the button directly to GND. (Note: Pin D2 is recommended as it supports interrupts, ensuring the device responds immediately when the button is pressed).

Step 6: Safety Check with Multimeter Do not skip this step. Before plugging in the USB cable, set your multimeter to "Continuity Mode" (beep mode). Touch one probe to the 5V line and the other to the GND line. If it beeps, you have a short circuit; locate the solder bridge and fix it. If it remains silent, your connections are safe.

Step 7: Upload the Code Connect the Arduino to your computer via USB. Open the Arduino IDE, copy the provided code, and click the "Upload" button. Wait until the status bar at the bottom displays "Done uploading."

Step 8: Final Adjustment and Calibration Once the code is uploaded, the LCD should illuminate. If the screen glows but shows no text, locate the small blue potentiometer (trimpot) on the back of the LCD I2C module. Use a small screwdriver to gently adjust it until the text "TheoLite Mini" or the angle data appears clearly. Your device is now fully operational.
