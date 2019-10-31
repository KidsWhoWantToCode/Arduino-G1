/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         keysacnStart.c
* @author       Danny
* @version      V1.0
* @date         2017.07.25
* @brief         keysacnStart
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

int key = A0;                //Key connects to wiringPi port A0 of Arduino UNO

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
  //Initializethe motor drive IO as the output mode
  pinMode(Left_motor_go, OUTPUT);
  pinMode(Left_motor_back, OUTPUT);
  pinMode(Right_motor_go, OUTPUT);
  pinMode(Right_motor_back, OUTPUT);

  //Initialize the key interface as the input mode
  pinMode(key, INPUT);

  //Initialize the key interface is high level
  digitalWrite(key, HIGH);
}

/**
* Function       run
* @author        Danny
* @date          2017.07.25
* @brief         advance
* @param[in]     time
* @param[out]    void
* @retval        void
* @par History   
*/
void run(int time)
{
  //Left motor advance
  digitalWrite(Left_motor_go, HIGH);   
  digitalWrite(Left_motor_back, LOW);  
  analogWrite(Left_motor_pwm, 200);

  //Right motor advance
  digitalWrite(Right_motor_go, HIGH); 
  digitalWrite(Right_motor_back, LOW); 
  analogWrite(Right_motor_pwm, 200);

  delay(time * 100);
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
* @brief         turn left (left wheel stop,right wheel advance)
* @param[in]     time
* @param[out]    void
* @retval        void
* @par History  
*/
void left(int time)
{
  //Left motor stop
  digitalWrite(Left_motor_go, LOW);    
  digitalWrite(Left_motor_back, LOW);  
  analogWrite(Left_motor_pwm, 0);

  //Right motor advance
  digitalWrite(Right_motor_go, HIGH);  
  digitalWrite(Right_motor_back, LOW); 
  analogWrite(Right_motor_pwm, 200);

  delay(time * 100);
}

/**
* Function       right
* @author        Danny
* @date          2017.07.25
* @brief         turn right (left wheel advance,right wheel stop)
* @param[in]     time
* @param[out]    void
* @retval        void
* @par History  
*/
void right(int time)
{
  //Left motor advance
  digitalWrite(Left_motor_go, HIGH);   
  digitalWrite(Left_motor_back, LOW);  
  analogWrite(Left_motor_pwm, 200);

  //Right motor stop
  digitalWrite(Right_motor_go, LOW);   
  digitalWrite(Right_motor_back, LOW); 
  analogWrite(Right_motor_pwm, 0);

  delay(time * 100);
}

/**
* Function       spin_left
* @author        Danny
* @date          2017.07.25
* @brief         turn left in place(left wheel back,right wheel advance)
* @param[in]     time：
* @param[out]    void
* @retval        void
* @par History   
*/
void spin_left(int time)
{
  //Left motor back
  digitalWrite(Left_motor_go, LOW);     
  digitalWrite(Left_motor_back, HIGH);  
  analogWrite(Left_motor_pwm, 200);

  //Right motor advance
  digitalWrite(Right_motor_go, HIGH);  
  digitalWrite(Right_motor_back, LOW); 
  analogWrite(Right_motor_pwm, 200);

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
  analogWrite(Left_motor_pwm, 200);

  //Right motor back
  digitalWrite(Right_motor_go, LOW);    
  digitalWrite(Right_motor_back, HIGH);
  analogWrite(Right_motor_pwm, 200);

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
  analogWrite(Left_motor_pwm, 200);

  //Right motor back
  digitalWrite(Right_motor_go, LOW); 
  digitalWrite(Right_motor_back, HIGH); 
  analogWrite(Right_motor_pwm, 200);

  delay(time * 100);
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
* @brief         When key is pressed，advance 1s，back 1s,turn left 2s,turn right 2s,
*                turn left in place 3s,turn right in place 3s,stop 0.5s
* @param[in]     void
* @retval        void
* @par History   
*/
void loop()
{
  key_scan();      

  run(10);          
  back(10);         
  left(20);         
  right(20);        
  spin_left(30);    
  spin_right(30);  
  brake(5);         
}
