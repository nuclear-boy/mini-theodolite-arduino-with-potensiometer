# mini-theodolite-arduino-with-potensiometer
Inspired by the conventional theodolite used for measuring building heights, this device operates by converting ADC values from a potentiometer into angular measurements. By applying fundamental trigonometric principles, it calculates the height of the targeted object.

# necessary tools and tool kits
To make a potentiometer, we need several devices such as:
1. Arduino as a microcontroler
2. Potensiometer as an angle genetor
3. LCD 12X6 + I2C MODUL as a display devices

* I recommend that you connect all components via PCB. Here, I am not using jumper cables.

# series of devices
![alt text](?raw=true)

Step 1: Gather Tools and Components Before you start soldering, ensure you have all the necessary items on your workbench. You will need a soldering iron, solder wire, wire cutters, and a multimeter. For the components, prepare your Arduino (Nano/Uno), the LCD screen with the I2C module attached, a 10k Ohm potentiometer, and the PCB board.

Step 2: Solder the Power Connections (5V and GND) Start by creating the power distribution lines on your PCB. Solder a connection from the Arduino's 5V pin to the VCC pin on the LCD and the Left Leg of the potentiometer. Next, solder a connection from the Arduino's GND pin to the GND pin on the LCD and the Right Leg of the potentiometer. This ensures both components receive power.

Step 3: Connect the LCD Data Lines Now, connect the communication wires between the Arduino and the screen. Solder a wire from Arduino Pin A4 to the SDA pin on the LCD module. Then, solder a wire from Arduino Pin A5 to the SCL pin on the LCD module. These two wires allow the Arduino to send text and numbers to the display.

Step 4: Connect the Potentiometer Signal This is the most critical step for measuring angles. Solder the Middle Pin (Wiper) of the potentiometer directly to Arduino Pin A0. This specific pin allows the Arduino to read the analog voltage changes when you turn the knob.

Step 5: Safety Check with Multimeter Do not skip this step. Before plugging in the USB cable, use your multimeter in "continuity mode" (beep mode). Touch one probe to the 5V line and the other to the GND line. If it beeps, you have a short circuit; find the solder bridge and fix it. If it remains silent, your connections are safe.

Step 6: Upload the Code Connect the Arduino to your computer using a USB cable. Open the Arduino IDE software, copy the code provided earlier, and click the "Upload" button. Wait until you see the message "Done uploading" at the bottom of the screen.

Step 7: Final Adjustment Once the code is uploaded, the LCD should light up. If the screen is glowing but shows no text, locate the small blue box (trimpot) on the back of the LCD I2C module. Use a small screwdriver to gently turn it until the text "TheoLite Mini" or the angle numbers appear clearly. Your device is now ready to use.
