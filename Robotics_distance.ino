// Adafruit SSD1306 - Version: 1.2.9
#include <Adafruit_SSD1306.h>
#include <splash.h>

/*
  Taylor Astill, Rob Lagwiniski, Onur Otemis, Daniel
*/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// pin numbers for Trig pin and echo pin
const int trigPin = 4;
const int echoPin = 5;

// defines variables
long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) {
    Serial.println(F("Display setup failed"));
    for (;;);
  }

  // Display the splash screen
  display.display();
  
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  display.setTextSize(5);
  display.setTextColor(WHITE);
  display.display();

}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigger to high for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin
  // returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance = duration * 0.034 / 2;

  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(int(distance));
  display.display();
}
