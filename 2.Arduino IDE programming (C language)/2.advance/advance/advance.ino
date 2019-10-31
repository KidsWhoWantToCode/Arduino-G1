/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         advance.c
* @author       Danny
* @version      V1.0
* @date         2017.07.25
* @brief        advance
* @details
* @par History  
*
*/

int Left_motor_go = 8;       //AIN2 connects to port 8 of Arduino UNO for control Left motor forward 
int Left_motor_back = 7;     //AIN1 connects to port 7 of Arduino UNO for control Left motor back

int Right_motor_go = 2;      //BIN1 connects to port 2 of Arduino UNO for control Right motor forward 
int Right_motor_back = 4;    //BIN2 connects to port 4 of Arduino UNO for control Right motor back

int Left_motor_pwm = 6;      //PWMA connects to port 6 of Arduino UNO for control the speed of the left motor
int Right_motor_pwm = 5;     //PWMA connects to port 5 of Arduino UNO for control the speed of the right motor

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
  // Initializethe motor drive IO as the output mode
  pinMode(Left_motor_go, OUTPUT);
  pinMode(Left_motor_back, OUTPUT);
  pinMode(Right_motor_go, OUTPUT);
  pinMode(Right_motor_back, OUTPUT);
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
  analogWrite(Left_motor_pwm, 200);     //pwm:0-255. The left and right wheels are slightly different

  //Right motor advance
  digitalWrite(Right_motor_go, HIGH);   
  digitalWrite(Right_motor_back, LOW); 
  analogWrite(Right_motor_pwm, 200);    //pwm:0-255. The left and right wheels are slightly different

  delay(time * 100); //Unit:ms
}

/**
* Function       loop
* @author        Danny
* @date          2017.07.25
* @brief         The car will delay 2s and advance 1s
* @param[in]     void
* @retval        void
* @par History   
*/
void loop()
{
  delay(2000);     
  run(10);         
}
