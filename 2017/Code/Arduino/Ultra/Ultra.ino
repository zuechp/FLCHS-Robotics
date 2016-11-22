/**
   Dual HC-SR04 Ultrasonic Distance

   Description:
    Connect the ultrasonic sensors to the Arduino as per the
    hardware connections below. Run the sketch and open a serial
    monitor. The distances read from each sensor will be displayed
    as a time delay.

   Hardware Connections:
    Arduino | Left HC-SR04        Arduino | Right HC-SR04
    ----------------------        -----------------------
      5V    |     VCC               5V    |     VCC
      2     |     Trig              12    |     Trig
      4     |     Echo              13    |     Echo
      GND   |     GND               GND   |     GND

*/

// Pins
const int TRIG_PIN_L = 2;
const int ECHO_PIN_L = 4;
const int TRIG_PIN_R = 12;
const int ECHO_PIN_R = 13;

// Anything over 400 cm (23200 us pulse) is "out of range"
const unsigned int MAX_DIST = 23200;
unsigned long l_dist;
unsigned long r_dist;

void measureDistances() {

  unsigned long t1;
  unsigned long t2;


  // Hold the trigger pin high for at least 10 us
  digitalWrite(TRIG_PIN_L, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN_L, LOW);

  // Wait for pulse on echo pin
  while ( digitalRead(ECHO_PIN_L) == 0 );

  // Measure how long the echo pin was held high (pulse width)
  // Note: the micros() counter will overflow after ~70 min
  t1 = micros();
  while ( digitalRead(ECHO_PIN_L) == 1);
  t2 = micros();
  l_dist = t2 - t1;

  // Hold the trigger pin high for at least 10 us
  digitalWrite(TRIG_PIN_R, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN_R, LOW);

  // Wait for pulse on echo pin
  while ( digitalRead(ECHO_PIN_R) == 0 );

  // Measure how long the echo pin was held high (pulse width)
  // Note: the micros() counter will overflow after ~70 min
  t1 = micros();
  while ( digitalRead(ECHO_PIN_R) == 1);
  t2 = micros();
  r_dist = t2 - t1;

  // Wait at least 60ms before next measurement
  delay(60);
}

void setup() {

  // The Trigger pin will tell the sensor to range find
  pinMode(TRIG_PIN_L, OUTPUT);
  digitalWrite(TRIG_PIN_L, LOW);
  pinMode(TRIG_PIN_R, OUTPUT);
  digitalWrite(TRIG_PIN_R, LOW);

  // We'll use the serial monitor to view the sensor output
  Serial.begin(9600);
}

void loop() {
  measureDistances();

  // Print out results
  Serial.print("Left \t");
  if ( l_dist > MAX_DIST ) {
    Serial.print("Out of range");
  } else {
    Serial.print(l_dist);
    Serial.print(" \t");
  }
  Serial.print("Right \t");
  if ( r_dist > MAX_DIST ) {
    Serial.print("Out of range");
    Serial.println(" \t");
  } else {
    Serial.print(r_dist);
    Serial.println(" \t");
  }

}
