#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <SoftwareSerial.h>

#define RX_PIN 7   // Arduino Nano RX to SIM800L TX
#define TX_PIN 8   // Arduino Nano TX to SIM800L RX
#define BAUD_RATE 9600

SoftwareSerial sim800l(RX_PIN, TX_PIN);
Adafruit_BMP280 bmp;

// Variables for call detection
String incomingData = "";
String callerNumber = "";

void setup() {
  Serial.begin(9600);
  sim800l.begin(BAUD_RATE);

  // Initialize BMP280
  if (!bmp.begin()) { // Address 0x76 or 0x77 depending on your module, had to change in library
    Serial.println("Could not find BMP280 sensor!");
    while (1);
  }

  // Initialize SIM800L
  sendCommand("AT");             // Check connection
  sendCommand("AT+CLIP=1");       // Enable caller ID notification
  sendCommand("AT+CMGF=1");       // Set SMS text mode
  delay(1000);

  Serial.println("Setup complete. Waiting for calls...");
}

void loop() {
  if (sim800l.available()) {
    char c = sim800l.read();
    incomingData += c;

    // Caller ID line format: +CLIP: "<number>",145,"",0,"",0
    if (incomingData.indexOf("+CLIP:") != -1) {
      int startIdx = incomingData.indexOf("\"") + 1;
      int endIdx = incomingData.indexOf("\"", startIdx);
      callerNumber = incomingData.substring(startIdx, endIdx);
      Serial.println("Incoming call from: " + callerNumber);

      // Hang up the call
      sendCommand("ATH");
      delay(500);

      // Get BMP280 data
      float temperature = bmp.readTemperature();
      float pressure = bmp.readPressure() / 100.0F; // hPa
      float altitude = bmp.readAltitude(1013.25);   // Sea level pressure

      // Create SMS content
      String smsText = "Temp: " + String(temperature, 2) + " C\n" +
                       "Pressure: " + String(pressure, 2) + " hPa\n" +
                       "Altitude: " + String(altitude, 2) + " m";

      sendSMS(callerNumber, smsText);
    }

    // Clear buffer to avoid multiple triggers
    if (incomingData.length() > 200) incomingData = "";
  }
}

// Function to send AT commands
void sendCommand(String cmd) {
  sim800l.println(cmd);
  delay(500);
  while (sim800l.available()) {
    Serial.write(sim800l.read());
  }
}

// Function to send SMS
void sendSMS(String number, String text) {
  Serial.println("Sending SMS to " + number);
  sim800l.print("AT+CMGS=\"");
  sim800l.print(number);
  sim800l.println("\"");
  delay(500);
  sim800l.print(text);
  delay(500);
  sim800l.write(26); // CTRL+Z to send
  delay(3000);
}
