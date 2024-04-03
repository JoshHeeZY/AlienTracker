#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

// Pin definitions for the TFT display
#define TFT_CS   A3  // Chip Select
#define TFT_DC   A2  // Data/Command
// Note: The RST pin is not used in this example. If your TFT has a RST pin, you can connect it to a digital pin and define it here.

// Initialize the Adafruit_ILI9341
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

// Define pins for the Ultrasonic Sensor
#define TRIGGER_PIN  30
#define ECHO_PIN     32

// Define pin for the Buzzer
#define BUZZER_PIN   34

// Define pin for the PIR motion sensor
#define PIR_PIN  7  // Connect PIR OUT pin to pin 7 on the Arduino

// Color definitions
#define BLACK   0x0000
#define RED     0xF800
#define GREEN   0x07E0
#define BLUE    0x001F
#define WHITE   0xFFFF

void setup() {
  // Initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  // TFT setup
  tft.begin();
  tft.setRotation(1); // Landscape mode
  tft.fillScreen(BLACK); // Clear the screen
  
  // Setup for Ultrasonic Sensor
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Setup for Buzzer
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Setup for PIR Motion Sensor
  pinMode(PIR_PIN, INPUT);
}

void loop() {
  // Ultrasonic sensor distance measurement
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2;

  // Display distance on the TFT
  tft.fillScreen(BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(WHITE); tft.setTextSize(2);
  tft.print("Distance: ");
  tft.print(distance);
  tft.println(" cm");

  // Check for motion detected by the PIR sensor
  int motionDetected = digitalRead(PIR_PIN);
  if (motionDetected == HIGH) {
    tft.setTextColor(RED); tft.setTextSize(2);
    tft.println("Motion detected!");
    tone(BUZZER_PIN, 1000); // Sound the buzzer
  } else {
    noTone(BUZZER_PIN); // Stop the buzzer if no motion
  }

  delay(500); // Delay a half second before repeating the loop
}
