/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         servo_ultrasonic_avoid.c
* @author       Danny
* @version      V1.0
* @date         2017.07.26
* @brief        servo_ultrasonic_avoid
* @details
* @par History  
*
*/
#include <Servo.h>  

#define ON  1   
#define OFF 0       

Servo myservo;      

//Definition of Pin
int LED_R = 11;     //LED_R is connected to port 11 of Arduino UNO
int LED_G = 10;     //LED_G is connected to port 10 of Arduino UNO
int LED_B = 9;      //LED_B is connected to port 9 of Arduino UNO

int ServoPin = 3;

int Left_motor_go = 8;       //AIN2 connects to port 8 of Arduino UNO for control Left motor forward 
int Left_motor_back = 7;     //AIN2 connects to port 7 of Arduino UNO for control Left motor back

int Right_motor_go = 2;      //BIN1 connects to port 2 of Arduino UNO for control Right motor forward 
int Right_motor_back = 4;    //BIN2 connects to port 4 of Arduino UNO for control Right motor back

int Left_motor_pwm = 6;      //PWMA connects to port 6 of Arduino UNO for control the speed of the left motor
int Right_motor_pwm = 5;     //PWMA connects to port 5 of Arduino UNO for control the speed of the right motor

int key  = A0;                //Key connects to wiringPi port A0 of Arduino UNO

int EchoPin = 12;             //Define the EchoPin connect to port 12 of Arduino UNO
int TrigPin = 13;             //Define the TrigPin connect to port 13 of Arduino UNO

float distance = 0;           

/**
* Function       setup
* @author        Danny
* @date          2017.07.25
* @brief         Initialization configure
* @param[in]     void
* @retval        void
* @par History   
*/
void setup()
{
  //Set the baud rate of serial data transmission to 9600
  Serial.begin(9600);

  //Initialize the motor drive IO as the output mode
  pinMode(Left_motor_go, OUTPUT);
  pinMode(Left_motor_back, OUTPUT);
  pinMode(Right_motor_go, OUTPUT);
  pinMode(Right_motor_back, OUTPUT);

  //Initialize the RGB IO as the output mode
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  //Initialize the key interface as the input mode
  pinMode(key, INPUT);
  //Initialize the key interface is high level
  digitalWrite(key, HIGH);

  //Initialize ultrasonic pin
  pinMode(EchoPin, INPUT);   
  pinMode(TrigPin, OUTPUT);   

  myservo.attach(ServoPin);

  //Initialize the servo position forward
  int ServoPos = 90;
  myservo.write(ServoPos);

  key_scan();
}

/**
* Function       servo_color_carstate
* @author        Danny
* @date          2017.07.26
* @brief         servo_color_carstate
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/
void servo_color_carstate()
{
  int iServoPos = 0;
  int LeftDistance = 0;  
  int RightDistance = 0;   
  int FrontDistance = 0;   
  corlor_led(ON, OFF, OFF);//LED_red
  back(90);                //Avoid stop suddenly
  delay(80);
  brake();

  //The servo rotates to 20°(right)to measure distance
  myservo.write(20);
  delay(500);
  Distance_test();         
  RightDistance = distance;

  //The servo rotates to 160°(left)to measure distance
  myservo.write(160);
  delay(500);
  Distance_test();        
  LeftDistance = distance;

  //The servo rotates to 90°(front)to measure distance
  myservo.write(90);
  delay(500);
  
  if (LeftDistance < 20 && RightDistance < 20  )
  {
    corlor_led(ON, OFF, ON);
    spin_right(150);
    delay(1100);
    brake();
  }
  else if ( LeftDistance >= RightDistance) 
  {
    corlor_led(OFF, OFF, ON);
    spin_left(150);
    delay(550);
    brake();
  }
  else if (LeftDistance < RightDistance ) 
  {
    corlor_led(ON, OFF, ON);
    spin_right(150);
    delay(550);
    brake();
  }
}

/**
* Function       run
* @author        Danny
* @date          2017.07.26
* @brief         advance
* @param[in1]    LeftSpeed
* @param[in2]    RightSpeed
* @param[out]    void
* @retval        void
* @par History   
*/
void run(int LeftSpeed, int RightSpeed)
{
  //Left motor advance
  digitalWrite(Left_motor_go, HIGH);   
  digitalWrite(Left_motor_back, LOW);  
  analogWrite(Left_motor_pwm, LeftSpeed);

  //Right motor advance
  digitalWrite(Right_motor_go, HIGH);  
  digitalWrite(Right_motor_back, LOW); 
  analogWrite(Right_motor_pwm, RightSpeed);
}

/**
* Function       brake
* @author        Danny
* @date          2017.07.25
* @brief         brake
* @param[in]
* @param[out]    void
* @retval        void
* @par History   
*/
void brake()
{
  digitalWrite(Left_motor_go, LOW);
  digitalWrite(Left_motor_back, LOW);
  digitalWrite(Right_motor_go, LOW);
  digitalWrite(Right_motor_back, LOW);

}

/**
* Function       spin_left
* @author        Danny
* @date          2017.07.25
* @brief         turn left in place(left wheel back,right wheel advance)
* @param[in]     time
* @param[out]    void
* @retval        void
* @par History   
*/
void spin_left(int speed)
{
  //Left motor back
  digitalWrite(Left_motor_go, LOW);     
  digitalWrite(Left_motor_back, HIGH);  
  analogWrite(Left_motor_pwm, speed);

  //Right motor advance
  digitalWrite(Right_motor_go, HIGH);  
  digitalWrite(Right_motor_back, LOW); 
  analogWrite(Right_motor_pwm, speed);
}

/**
* Function       spin_right
* @author        Danny
* @date          2017.07.25
* @brief         turn right in place(right wheel back,left wheel advance)
* @param[in]     time
* @param[out]    void
* @retval        void
* @par History   
*/
void spin_right(int speed)
{
  //Left motor advance
  digitalWrite(Left_motor_go, HIGH);  
  digitalWrite(Left_motor_back, LOW);  
  analogWrite(Left_motor_pwm, speed);

  //Right motor back
  digitalWrite(Right_motor_go, LOW);    
  digitalWrite(Right_motor_back, HIGH); 
  analogWrite(Right_motor_pwm, speed);
}

/**
* Function       back
* @author        Danny
* @date          2017.07.25
* @brief         back
* @param[in]     time
* @param[out]    void
* @retval        void
* @par History   
*/
void back(int speed)
{
  //Left motor back
  digitalWrite(Left_motor_go, LOW);     
  digitalWrite(Left_motor_back, HIGH);  
  analogWrite(Left_motor_pwm, speed);

  //Right motor back
  digitalWrite(Right_motor_go, LOW);    
  digitalWrite(Right_motor_back, HIGH); 
  analogWrite(Right_motor_pwm, speed);
}

/**
* Function       color_led
* @author        Danny
* @date          2017.07.25
* @brief         7 different colors formed by different combinations of R,G and B
* @param[in1]    v_iRed
* @param[in2]    v_iGreen
* @param[in3]    v_iBlue
* @retval        void
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
* Function       Distance
* @author        Danny
* @date          2017.07.26
* @brief          measure the distance by Ultrasonic
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/
void Distance()
{
  digitalWrite(TrigPin, LOW);               //Input a low level of 2 us to the Trig pin
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);              //Input a high level of at least 10 us to the Trig pin
  delayMicroseconds(15);
  digitalWrite(TrigPin, LOW);
  float Fdistance = pulseIn(EchoPin, HIGH); 
  Fdistance = Fdistance / 58;
  Serial.print("Distance:");             
  Serial.print(Fdistance);              
  Serial.println("cm");
  distance = Fdistance;
}

/**
* Function       Distane_test
* @author        Danny
* @date          2017.07.26
* @brief         Remove the maximum, minimum of the 5 datas, and get average values of 3 datas to improve accuracy of test
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/
void Distance_test()
{
  unsigned long ultrasonic[5] = {0};
  int num = 0;
  while (num < 5)
  {
    Distance();
    while (distance >= 600 || distance == 0)
    {
      brake();
      Distance();
    }
    ultrasonic[num] = distance;
    num++;
    delay(10);
  }
  num = 0;
  bubble(ultrasonic, 5);
  distance = (ultrasonic[1] + ultrasonic[2] + ultrasonic[3]) / 3;
  return;
}

/**
* Function       bubble
* @author        Danny
* @date          2017.07.26
* @brief         Bubble sorting 
* @param[in1]    a:Ultrasonic array first address
* @param[in2]    n:Size of Ultrasonic array 
* @param[out]    void
* @retval        void
* @par History   
*/
void bubble(unsigned long *a, int n)

{
  int i, j, temp;
  for (i = 0; i < n - 1; i++)
  {
    for (j = i + 1; j < n; j++)
    {
      if (a[i] > a[j])
      {
        temp = a[i];
        a[i] = a[j];
        a[j] = temp;
      }
    }
  }
}

/**
* Function       key_scan
* @author        Danny
* @date          2017.07.25
* @brief         key detection (including software-key debounce)
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/
void key_scan()
{
  while (digitalRead(key));       //Loops this code when the key is not pressed
  while (!digitalRead(key))       //When the key is pressed
  {
    delay(10);	                  
    if (digitalRead(key)  ==  LOW)//Re-determine whether the key was pressed
    {
      delay(100);
      while (!digitalRead(key));  //Determine whether the key is released
    }
  }
}

/**
* Function       loop
* @author        Danny
* @date          2017.07.25
* @brief         
* @param[in]     void
* @retval        void
* @par History   
*/
void loop()
{
  Distance_test();        
  if (distance > 35  )    
  {
    run(150, 150);
    corlor_led(OFF, ON, OFF);
  }
  else if ((distance >= 25 && distance <= 35))
  {
    run(100, 100);
  }
  else if (  distance < 25  )
  {
    servo_color_carstate();
  }
}




