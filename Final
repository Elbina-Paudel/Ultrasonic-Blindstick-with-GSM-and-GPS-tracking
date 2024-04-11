#include <SoftwareSerial.h>
#include <TinyGPS++.h>

int buttonpin = 6;
int distance1, distance2;
long duration1, duration2;
const int trigPin1 = A0;
const int echoPin1 = A1;
const int trigPin2 = A2;
const int echoPin2 = A3;
#define buzzer_pin 5

float lattitude, longitude;
float a[2];
float *p;

SoftwareSerial gpsSerial(2, 3);
SoftwareSerial gsmSerial(10, 11);

static const int RXPin = 3, TXPin = 2;
static const uint32_t GPSBaud = 9600;
SoftwareSerial ss(RXPin, TXPin);
TinyGPSPlus gps;

void setup() {
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(buttonpin, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  Serial.begin(9600);
  ss.begin(GPSBaud);
  gpsSerial.begin(9600);
  gsmSerial.begin(9600);
  delay(1000);
  Serial.println("Initializing...");
  delay(2000);
  Serial.println("System Ready");
  delay(1000);
}

void loop() {
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10) {
    Serial.println("No GPS detected: check wiring.");
    while(true);
  }

  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1 * 0.034 / 2;
  Serial.print("Distance1: ");
  Serial.println(distance1);

  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = duration2 * 0.034 / 2;
  Serial.print("Distance2: ");
  Serial.println(distance2);

  if (distance1 <= 40 || distance2 <= 40) {
    Serial.println("Close to obstacle");
    alert();
  } else {
    digitalWrite(buzzer_pin, LOW);
  }

  int sensorValue = digitalRead(A4);
  if (sensorValue == 1) {
    Serial.println("Water Alert");
    alert();
  } else {
    digitalWrite(buzzer_pin, LOW);
  }

  if (digitalRead(buttonpin) == 0) {
    Serial.println("Button pressed");
    delay(2000);
    SendMessage();
  }

  if (gsmSerial.available() > 0)
    Serial.write(gsmSerial.read());

  while (gsmSerial.available())
    gsmSerial.read();

  while (Serial.available())
    Serial.read();
}

void displayInfo() {
  Serial.print("Location: ");
  if (gps.location.isValid()) {
    Serial.print(gps.location.lat(), 6);
    Serial.print(",");
    Serial.print(gps.location.lng(), 6);
  } else {
    Serial.print("INVALID");
  }
  Serial.println();
}

float *get_gps() {
  gpsSerial.listen();
  Serial.println("INSIDE get_gps");
  while (1) {
    while (gpsSerial.available() > 0) {
      gps.encode(gpsSerial.read());
    }
    if (gps.location.isUpdated()) {
      Serial.print("LAT=");
      Serial.println(gps.location.lat(), 8);
      Serial.print("LONG=");
      Serial.println(gps.location.lng(), 8);
      lattitude = gps.location.lat();
      longitude = gps.location.lng();
      break;
    }
  }
  a[0] = lattitude;
  a[1] = longitude;
  return a;
}

void SendMessage() {
  gsmSerial.println("AT+CMGF=1");
  delay(1000);
  gsmSerial.println("AT+CMGS=\"+9779808711811\"");
  delay(1000);
  gsmSerial.println("I Am In Problem Plz Help Me");
  delay(1000);
  p = get_gps();
  gsmSerial.listen();
  Serial.print("Your Position is : ");
  gsmSerial.print("Position is : ");
  Serial.print("LATITUDE=");
  Serial.print(p, 8);
  gsmSerial.print("LATITUDE=");
  gsmSerial.print(p, 8);
  gsmSerial.print(",");
  Serial.print("LONGITUDE=");
  Serial.print((p + 1), 8);
  gsmSerial.print("LONGITUDE=");
  gsmSerial.print((p + 1), 8);
  delay(100);
  gsmSerial.println((char)26);
}

void alert() {
  digitalWrite(buzzer_pin, HIGH);
  delay(1000);
  digitalWrite(buzzer_pin, LOW);
  delay(1000);
  digitalWrite(buzzer_pin, HIGH);
  delay(1000);
  digitalWrite(buzzer_pin, LOW);
}
