/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         voltage_detection.c
* @author       Danny
* @version      V1.0
* @date         2017.07.26
* @brief        voltage_detection
* @details
* @par History  
*
*/

float Voltage = 0;
float time = 0;

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
  Serial.begin(9600);
}

/**
* Function       loop
* @author        Danny
* @date          2017.07.25
* @brief         Read the collected voltage value and print it once per second through the serial port.
* @param[in]     void
* @retval        void
* @par History   
*/
void loop()
{
  time =  time + 1;
  Voltage = analogRead(A0);                     
  Voltage = (Voltage / 1023) * 4.98 * 1.68 - 0.35 ; //Convert to voltage value

  Serial.print("U:");
  Serial.print(Voltage , 3);
  Serial.print("V");
  Serial.print("  time:");
  Serial.print(time);
  Serial.println("s");

  delay(1000);
}
