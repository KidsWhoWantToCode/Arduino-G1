/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         avoid_ultrasonic.c
* @author       Danny
* @version      V1.0
* @date         2017.07.26
* @brief        avoid_ultrasonic
* @details
* @par History  
*
*/

int Left_motor_go = 8;       //AIN2 connects to port 8 of Arduino UNO for control Left motor forward 
int Left_motor_back = 7;     //AIN2 connects to port 7 of Arduino UNO for control Left motor back

int Right_motor_go = 2;      //BIN1 connects to port 2 of Arduino UNO for control Right motor forward 
int Right_motor_back = 4;    //BIN2 connects to port 4 of Arduino UNO for control Right motor back

int Left_motor_pwm = 6;      //PWMA connects to port 6 of Arduino UNO for control the speed of the left motor
int Right_motor_pwm = 5;     //PWMA connects to port 5 of Arduino UNO for control the speed of the right motor

int key = A0;                //Key connects to wiringPi port 10 of Arduino UNO

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

  //Initialize the key interface as the input mode
  pinMode(key, INPUT);
  //Initialize the key interface is high level
  digitalWrite(key, HIGH);

  //Initialize ultrasonic pin
  pinMode(EchoPin, INPUT);    
  pinMode(TrigPin, OUTPUT);   

  key_scan();
}

/**
* Function       run
* @author        Danny
* @date          2017.07.26
* @brief         advance
* @param[in1]    left_speed
* @param[in2]    right_speed
* @param[out]    void
* @retval        void
* @par History   
*/
void run(int left_speed, int right_speed)
{
  //Left motor advance
  digitalWrite(Left_motor_go, HIGH);   
  digitalWrite(Left_motor_back, LOW);  
  analogWrite(Left_motor_pwm, left_speed );

  //Right motor davance
  digitalWrite(Right_motor_go, HIGH); 
  digitalWrite(Right_motor_back, LOW); 
  analogWrite(Right_motor_pwm, right_speed);
}

/**
* Function       brake
* @author        Danny
* @date          2017.07.25
* @brief         brake
* @param[in]     time
* @param[out]    void
* @retval        void
* @par History   
*/
void brake(int time)
{
  digitalWrite(Left_motor_go, LOW);
  digitalWrite(Left_motor_back, LOW);
  digitalWrite(Right_motor_go, LOW);
  digitalWrite(Right_motor_back, LOW);

  delay(time * 100);
}

/**
* Function       left
* @author        Danny
* @date          2017.07.25
* @brief         turn left (left aheel stop,right wheel advance)
* @param[in1]    left_speed
* @param[in2]    right_speed
* @param[out]    void
* @retval        void
* @par History   
*/
void left(int left_speed, int right_speed)
{
  //Left motor stop
  digitalWrite(Left_motor_go, LOW);   
  digitalWrite(Left_motor_back, LOW);  
  analogWrite(Left_motor_pwm, left_speed);

  //Right motor advance
  digitalWrite(Right_motor_go, HIGH);  
  digitalWrite(Right_motor_back, LOW); 
  analogWrite(Right_motor_pwm, right_speed);
}

/**
* Function       right
* @author        Danny
* @date          2017.07.25
* @brief         turn right(right wheel stop,left wheel advance)
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/
void right()
{
  //Left motor advance
  digitalWrite(Left_motor_go, HIGH);   
  digitalWrite(Left_motor_back, LOW);  
  analogWrite(Left_motor_pwm, 150);

  //Right motor stop
  digitalWrite(Right_motor_go, LOW);   
  digitalWrite(Right_motor_back, LOW); 
  analogWrite(Right_motor_pwm, 0);
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
void spin_left(int time)
{
  //Left motor back
  digitalWrite(Left_motor_go, LOW);     
  digitalWrite(Left_motor_back, HIGH);  
  analogWrite(Left_motor_pwm, 160);

  //Right motor advance
  digitalWrite(Right_motor_go, HIGH); 
  digitalWrite(Right_motor_back, LOW); 
  analogWrite(Right_motor_pwm, 160);
  
  delay(time * 100);
}

/**
* Function       spin_right
* @author        Danny
* @date          2017.07.25
* @brief         turn right in place(left wheel advance,right wheel back)
* @param[in]     time
* @param[out]    void
* @retval        void
* @par History   
*/
void spin_right(int time)
{
  //Left motor advance
  digitalWrite(Left_motor_go, HIGH);    
  digitalWrite(Left_motor_back, LOW);   
  analogWrite(Left_motor_pwm,160);

  //Right motor back
  digitalWrite(Right_motor_go, LOW);   
  digitalWrite(Right_motor_back, HIGH); 
  analogWrite(Right_motor_pwm, 160);
  
  delay(time * 100);
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
void back(int time)
{
  //Left motor back
  digitalWrite(Left_motor_go, LOW);     
  digitalWrite(Left_motor_back, HIGH);  
  analogWrite(Left_motor_pwm, 40);

  //Right motor back
  digitalWrite(Right_motor_go, LOW);    
  digitalWrite(Right_motor_back, HIGH); 
  analogWrite(Right_motor_pwm, 40);

  delay(time );
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
* Function       Distance
* @author        Danny
* @date          2017.07.26
* @brief         measure the distance by Ultrasonic
* @param[in]     void
* @param[out]    void
* @retval        void
* @par History   
*/
void Distance()
{
  digitalWrite(TrigPin, LOW);               //Input a low level of 2 US to the Trig pin
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);              //Input a high level of at least 10 US to the Trig pin
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
    //Filter out data greater than 500 or smaller than 0 in the test distance
    while (distance >= 500)
    {
      brake(0);
      Distance();
    }
    ultrasonic[num] = distance;
    num++;
  }
  num = 0;
  bubble(ultrasonic, 5);
  distance = (ultrasonic[1] + ultrasonic[2] + ultrasonic[3]) / 3;
  return;
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
  if (distance > 50)
  {
    run(200, 200);      
  }
  else if (distance >= 25 && distance <= 50)
  {
    run(100, 100);      
  }
  else if (distance < 25)
  {
    spin_right(3.5);  
    brake(1);
    Distance_test();    
    if (distance >= 25)
    {
      run(100, 100);   
    }
    else if (distance < 25)
    {
      spin_left(7);    
      brake(1);
      Distance_test(); 
      if (distance >= 25)
      {
        run(100, 100); 
      }
      else if (distance < 25)
      {
        spin_left(3.5);
        brake(1);
      }
    }
  }
}
