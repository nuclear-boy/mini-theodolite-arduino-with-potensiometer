#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize I2C LCD 16x2
LiquidCrystal_I2C lcd(0x27, 16, 2); // Change 0x27 to your LCD address if different

// Pin Definitions
const int pinPot = A0;
const int pinButton = 2; // Renamed from pinSwitch for clarity

// Calibration Variables
const float ADC_ZERO = 519.0;    // ADC value at 0 degrees (Horizon)
const float DEVICE_HEIGHT = 0.772; // Device height in meters (75 cm)

// Measurement Variables
float baseAngle = 0;
float peakAngle = 0;
int measurementStep = 0; // 0: Ready, 1: Base Angle, 2: Peak Angle, 3: Result

void setup() {
  // Initialize pins
  pinMode(pinPot, INPUT);
  pinMode(pinButton, INPUT_PULLUP);
  
  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  // Initial Display
  lcd.print("THEO_Mini");
  lcd.setCursor(0, 1);
  lcd.print("By Fiqkri");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Read potentiometer value
  int adcValue = analogRead(pinPot);
  
  // Convert ADC to angle (0 deg at ADC 519)
  float angle = convertADCtoAngle(adcValue);
  
  // Detect button press
  if (digitalRead(pinButton) == LOW) {
    delay(50); // Debouncing
    if (digitalRead(pinButton) == LOW) {
      handleButtonPress(angle);
      while(digitalRead(pinButton) == LOW); // Wait until button is released
    }
  }
  
  // Display information based on current step
  displayInfo(measurementStep, angle, adcValue);
  
  delay(200);
}

// Function: Convert ADC to Angle
float convertADCtoAngle(int adc) {
  float angle = 0;
  
  if (adc <= ADC_ZERO) {
    // BASE Mode: ADC decreases from 519 to 0 = angle increases from 0 to 90
    angle = (ADC_ZERO - adc) * (90.0 / ADC_ZERO);
  } else {
    // PEAK Mode: ADC increases from 519 to 1023 = angle increases from 0 to 90
    angle = (adc - ADC_ZERO) * (90.0 / (1023.0 - ADC_ZERO));
  }
  
  // Apply linear regression for accuracy correction
  angle = (1.328 * angle) + 0.5691;
  
  // ENSURE ANGLE IS NEVER NEGATIVE
  if (angle < 0) angle = 0;
  if (angle > 90) angle = 90;
  
  return angle;
}

// Function: Handle Button Logic
void handleButtonPress(float currentAngle) {
  measurementStep++;
  
  if (measurementStep == 1) {
    // Save base angle
    baseAngle = currentAngle;
    if (baseAngle < 0) baseAngle = 0; // Ensure non-negative
    
    lcd.clear();
    lcd.print("BASE ANGLE SET!");
    lcd.setCursor(0, 1);
    lcd.print("Value: ");
    lcd.print(baseAngle, 1);
    lcd.print((char)223); // Degree symbol
    delay(2000);
    
  } else if (measurementStep == 2) {
    // Save peak angle
    peakAngle = currentAngle;
    if (peakAngle < 0) peakAngle = 0; // Ensure non-negative
    
    lcd.clear();
    lcd.print("PEAK ANGLE SET!");
    lcd.setCursor(0, 1);
    lcd.print("Value: ");
    lcd.print(peakAngle, 1);
    lcd.print((char)223); // Degree symbol
    delay(2000);
    
    // Calculate and display results
    calculateAndDisplay();
    
  } else if (measurementStep == 3) {
    // Reset for new measurement
    measurementStep = 0;
    baseAngle = 0;
    peakAngle = 0;
    
    lcd.clear();
    lcd.print("SYSTEM RESET");
    lcd.setCursor(0, 1);
    lcd.print("Ready to measure");
    delay(2000);
  }
}

// Function: Calculate Distance and Height
void calculateAndDisplay() {
  // Convert degrees to radians
  float baseAngleRad = baseAngle * PI / 180.0;
  float peakAngleRad = peakAngle * PI / 180.0;
  
  // Calculate distance (d) to the object/wall
  // Formula: d = DEVICE_HEIGHT / tan(baseAngle)
  float distance = DEVICE_HEIGHT / tan(baseAngleRad);
  
  // Calculate object height
  // Formula: Height = DEVICE_HEIGHT + (distance * tan(peakAngle))
  float rawHeight = DEVICE_HEIGHT + (distance * tan(peakAngleRad));
  
  // Apply correction factor
  float finalHeight = (0.98 * rawHeight) + 0.442;
  
  // Display Results
  lcd.clear();
  lcd.print("Dist: ");
  lcd.print(distance, 1);
  lcd.print(" m");
  
  lcd.setCursor(0, 1);
  lcd.print("Height: ");
  lcd.print(finalHeight, 1);
  lcd.print(" m");
  
  // Delay to allow reading results
  delay(5000);
}

// Function: Display Real-time Info
void displayInfo(int step, float angle, int adc) {
  lcd.clear();
  
  switch(step) {
    case 0:
      lcd.print("Aim at BASE");
      lcd.setCursor(0, 1);
      lcd.print("Angle: ");
      lcd.print(angle, 1);
      lcd.print((char)223);
      break;
      
    case 1:
      lcd.print("Aim at PEAK"); // Or "Aim at TOP"
      lcd.setCursor(0, 1);
      lcd.print("Angle: ");
      lcd.print(angle, 1);
      lcd.print((char)223);
      break;
      
    case 2:
      // Keep displaying results (handled in calculateAndDisplay)
      break;
      
    case 3:
      lcd.print("Press button to");
      lcd.setCursor(0, 1);
      lcd.print("measure again");
      break;
  }
}