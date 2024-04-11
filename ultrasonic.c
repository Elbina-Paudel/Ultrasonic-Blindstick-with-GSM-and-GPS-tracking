// Define pins for ultrasonic sensor
#define trigPin A2
#define echoPin A3

// Define pin for push button
#define buttonPin 4

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize push button pin
  pinMode(buttonPin, INPUT_PULLUP);

  // Initialize ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Check if push button is pressed
  if (digitalRead(buttonPin) == 0) {
    //float pin= digitalRead(buttonPin);
    //Serial.println(pin);
    // Measure distance using ultrasonic sensor
    float distance = measureDistance();

    // Print distance to serial monitor
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Delay to prevent rapid readings
    delay(500);
  }
}

float measureDistance() {
  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the pulse duration
  unsigned long pulseDuration = pulseIn(echoPin, HIGH);

  // Calculate distance based on the pulse duration
  float distance = pulseDuration * 0.034 / 2; // Speed of sound is 0.034 cm/µs

  return distance;
