#include <DRV8835MotorShield.h>
DRV8835MotorShield motors;
/*
 * Motor functions
    static void setM1Speed(int speed);
    static void setM2Speed(int speed);
    static void setSpeeds(int m1Speed, int m2Speed);
    static void flipM1(boolean flip);
    static void flipM2(boolean flip);
*/

/*
 * StraightDistance
 * keep robot moving along striaght line equidistant from reflecting barriers
 *
 * connections:
 * D2  = left ultrasonic trigger
 * D4  = left ultrasonic echo
 * D7  = M1DIR - left motor dir
 * D8  = M2DIR - right motor dir
 * D9  = M1PWM - left motor pwm
 * D10 = M2PWM - right motor pwm
 * D12 = right ultrasonic trigger
 * D13 = right ultrasonic echo
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
unsigned long l_dist_old;
unsigned long r_dist_old;

const int fwdSpeed = 50;
int leftSpeed;
int rightSpeed;

void measureDistances() {
  /*
  pulse left sensor first, then right sensor
  */

  unsigned long t1;
  unsigned long t2;


  // Hold the trigger pin high for at least 10 us
  digitalWrite(TRIG_PIN_L, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN_L, LOW);

  // Wait for pulse on echo pin
  while ( digitalRead(ECHO_PIN_L) == LOW );

  // Measure how long the echo pin was held high (pulse width)
  // Note: the micros() counter will overflow after ~70 min
  t1 = micros();
  while ( digitalRead(ECHO_PIN_L) == HIGH);
  t2 = micros();
  l_dist = t2 - t1;

  // Hold the trigger pin high for at least 10 us
  digitalWrite(TRIG_PIN_R, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN_R, LOW);

  // Wait for pulse on echo pin
  while ( digitalRead(ECHO_PIN_R) == LOW );

  // Measure how long the echo pin was held high (pulse width)
  // Note: the micros() counter will overflow after ~70 min
  t1 = micros();
  while ( digitalRead(ECHO_PIN_R) == HIGH);
  t2 = micros();
  r_dist = t2 - t1;

  // Wait at least 60ms before next measurement
  delay(60);
}

void rampMotors(int l_dist, int l_dist_old)//int leftTargetSpeed, int rightTargetSpeed) {
{
if (l_dist<l_dist_old)
{
  motors.setM1Speed(0);
   motors.setM2Speed(fwdSpeed);
   delay(20);
}
else if(l_dist>l_dist_old)
{
  motors.setM1Speed(fwdSpeed);
   motors.setM2Speed(0);
   delay(20);
}
  /*if (leftTargetSpeed != leftSpeed)
    if (leftTargetSpeed > leftSpeed) {
    } else {
    }
  if (rightTargetSpeed != rightSpeed)
    if (rightTargetSpeed > rightSpeed) {
    } else {
    }
*/
}

void setup() {

  // The Trigger pin will tell the sensors to range find
  pinMode(TRIG_PIN_L, OUTPUT);
  digitalWrite(TRIG_PIN_L, LOW);
  pinMode(TRIG_PIN_R, OUTPUT);
  digitalWrite(TRIG_PIN_R, LOW);

  // uncomment one or both of the following lines if your motors' directions need to be flipped
  // set for red chassis

  motors.flipM1(true);
  //motors.flipM2(true);

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
  rampMotors(l_dist,l_dist_old);
  l_dist_old=l_dist;
}
