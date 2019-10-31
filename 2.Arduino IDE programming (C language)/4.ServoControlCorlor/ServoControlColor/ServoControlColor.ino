/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         ServoControlColor.c
* @author       Danny
* @version      V1.0
* @date         2017.07.25
* @brief        ServoControlColor
* @details
* @par History  
*
*/
#include <Servo.h>  //Arduino IDE comes with the servo library file

#define ON  1       
#define OFF 0      

Servo myservo;      

//Definition of Pin
int LED_R = 11;     //LED_R is connected to port 11 of Arduino UNO
int LED_G = 10;     //LED_G is connected to port 10 of Arduino UNO
int LED_B = 9;      //LED_B is connected to port 9 of Arduino UNO

//Define the servo pin
int ServoPin = 3;

/**
* Function       setup
* @author        Danny
* @date          2017.07.25
* @brief         initialization configure
* @param[in]     void
* @retval        void
* @par History   
*/
void setup()
{
  //Initialize the RGB IO as the output mode
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  myservo.attach(ServoPin);

  //Initialize the servo position forward
  int ServoPos = 90;
  myservo.write(ServoPos);
}

/**
* Function       servo_control_color
* @author        Danny
* @date          2017.07.25
* @brief         The servo turns from 0-180, then turns from 180 to 0.
*                At the same time, the 180 degree angle is divided into 7 sections to represent 7 different colors.
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/
void servo_control_color()
{
  int pos = 0;
  for (pos = 0; pos < 180; pos++)
  {
    myservo.write(pos);
    corlor_light(pos);
    delay(20);
  }

  for (pos = 180; pos > 0; pos--)
  {
    myservo.write(pos);
    corlor_light(pos);
    delay(20);
  }
}

/**
* Function       corlor_light
* @author        Danny
* @date          2017.07.25
* @brief         According to the angle of rotation ,light up the corresponding color 
* @param[in]     pos 
* @param[out]    void
* @retval        void
* @par History   
*/
void corlor_light(int pos)
{
  if (pos > 150)
  {
    corlor_led(ON, OFF, OFF);
  }
  else if (pos > 125)
  {
    corlor_led(OFF, ON, OFF);
  }
  else if (pos > 100)
  {
    corlor_led(OFF, OFF, ON);
  }
  else if (pos > 75)
  {
    corlor_led(OFF, ON, ON);
  }
  else if (pos > 50)
  {
    corlor_led(ON, ON, OFF);
  }
  else if (pos > 25)
  {
    corlor_led(ON, OFF, ON);
  }
  else if (pos > 0)
  {
    corlor_led(ON, ON, ON);
  }
  else
  {
    corlor_led(OFF, OFF, OFF);
  }
}
/**
* Function        color_led
* @author         Danny
* @date           2017.07.25
* @brief          7 different colors formed by different combinations of R,G and B
* @param[in1]     Red
* @param[in2]     Green
* @param[in3]     Blue
* @retval         void
* @par History    
*/
void corlor_led(int v_iRed, int v_iGreen, int v_iBlue)
{
  if (v_iRed == ON)
  {
    digitalWrite(LED_R, HIGH);
  }
  else
  {
    digitalWrite(LED_R, LOW);
  }
  if (v_iGreen == ON)
  {
    digitalWrite(LED_G, HIGH);
  }
  else
  {
    digitalWrite(LED_G, LOW);
  }
  if (v_iBlue == ON)
  {
    digitalWrite(LED_B, HIGH);
  }
  else
  {
    digitalWrite(LED_B, LOW);
  }
}

/**
* Function       loop
* @author        Danny
* @date          2017.07.25
* @brief         Delay 0.5 s, Servo_control_color mode is opened
* @param[in]     void
* @retval        void
* @par History   
*/
void loop()
{
  delay(500);
  servo_control_color();
}



