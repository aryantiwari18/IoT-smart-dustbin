#include <SoftwareSerial.h>
#include <TinyGPS++.h>


#define TRIG_PIN 9
#define ECHO_PIN 10


SoftwareSerial sim800(7, 8);   // RX, TX


SoftwareSerial gpsSerial(4, 3); // RX, TX
TinyGPSPlus gps;


const int dustbinHeight = 30;   // cm
const int fullLevel = 5;        // cm

bool smsSent = false;


void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  sim800.begin(9600);
  gpsSerial.begin(9600);

  delay(2000);

  Serial.println("Smart Dustbin Started...");
}


long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);

  long distance = duration * 0.034 / 2;

  return distance;
}


void sendSMS(float latitude, float longitude) {

  sim800.println("AT+CMGF=1");
  delay(1000);

  sim800.println("AT+CMGS=\"+91XXXXXXXXXX\"");
  delay(1000);

  sim800.println("ALERT: Smart Dustbin is FULL!");

  sim800.print("Location: ");
  sim800.print("https://maps.google.com/?q=");
  sim800.print(latitude, 6);
  sim800.print(",");
  sim800.print(longitude, 6);

  sim800.write(26); // CTRL+Z
  delay(5000);

  Serial.println("SMS Sent!");
}


void loop() {

  long distance = getDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  
  gpsSerial.listen();

  unsigned long start = millis();

  while (millis() - start < 1000) {
    while (gpsSerial.available()) {
      gps.encode(gpsSerial.read());
    }
  }

  
  if (distance <= fullLevel && !smsSent) {

    Serial.println("Dustbin FULL!");

    if (gps.location.isValid()) {

      float latitude = gps.location.lat();
      float longitude = gps.location.lng();

      Serial.print("Latitude: ");
      Serial.println(latitude, 6);

      Serial.print("Longitude: ");
      Serial.println(longitude, 6);

      sim800.listen();

      sendSMS(latitude, longitude);

      smsSent = true;
    }
    else {
      Serial.println("GPS location not available.");
    }
  }

  
  if (distance > 8) {
    smsSent = false;
  }

  delay(1000);
}