#include <DRV8835MotorShield.h>
/*
   This example uses the DRV8835MotorShield library to drive each motor with the
   Pololu DRV8835 Dual Motor Driver Shield for Arduino forward, then backward.
*/

DRV8835MotorShield motors;
/*
    static void setM1Speed(int speed);
    static void setM2Speed(int speed);
    static void setSpeeds(int m1Speed, int m2Speed);
    static void flipM1(boolean flip);
    static void flipM2(boolean flip);
*/


/*
   Pin Assignments
   Motor pins
   D7  (pi5 ) - M1DIR - left motor dir
   D8  (pi6 ) - M2DIR - right motor dir
   D9  (pi12) - M1PWM - left motor pwm
   D10 (pi13) - M2PWM - right motor pwm

*/

void exerciseMotors() {
  // run left motor with positive speed
  Serial.println("run left motor with positive speed");
  for (int speed = 0; speed <= 400; speed++)
  {
    motors.setM1Speed(speed);
    delay(2);
  }

  for (int speed = 400; speed >= 0; speed--)
  {
    motors.setM1Speed(speed);
    delay(2);
  }

  // run M1 motor with negative speed
  Serial.println("run M1 motor with negative speed");

  for (int speed = 0; speed >= -400; speed--)
  {
    motors.setM1Speed(speed);
    delay(2);
  }

  for (int speed = -400; speed <= 0; speed++)
  {
    motors.setM1Speed(speed);
    delay(2);
  }

  // run M2 motor with positive speed

  Serial.println("run M2 motor with positive speed");
  for (int speed = 0; speed <= 400; speed++)
  {
    motors.setM2Speed(speed);
    delay(2);
  }

  for (int speed = 400; speed >= 0; speed--)
  {
    motors.setM2Speed(speed);
    delay(2);
  }

  // run M2 motor with negative speed

  Serial.println("run M2 motor with negative speed");
  for (int speed = 0; speed >= -400; speed--)
  {
    motors.setM2Speed(speed);
    delay(2);
  }

  for (int speed = -400; speed <= 0; speed++)
  {
    motors.setM2Speed(speed);
    delay(2);
  }

  delay(500);

}
void setup()
{
  Serial.begin(9600);
  delay(1000);

  // uncomment one or both of the following lines if your motors' directions need to be flipped
  // set for red chassis

  motors.flipM1(true);
  //motors.flipM2(true);
}

void loop()
{
  exerciseMotors();
}
