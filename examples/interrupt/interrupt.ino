/**！
 * @file interrupt.ino
 * @brief Enable some interrupt events in the sensor, and get
   @n the interrupt signal through the interrupt pin
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2021-01-16
 * @get from https://www.dfrobot.com
 * @https://github.com/DFRobot/DFRobot_LIS331HH
 */

#include <DFRobot_LIS331HH.h>
//当你使用I2C通信时,使用下面这段程序,使用DFRobot_LIS331HH_I2C构造对象
/*!
 * @brief Constructor 
 * @param pWire I2c controller
 * @param addr  I2C address(0x18/0x19)
 */
//DFRobot_LIS331HH_I2C acce(&Wire,0x19);
DFRobot_LIS331HH_I2C acce;

//当你使用SPI通信时,使用下面这段程序,使用DFRobot_LIS331HH_SPI构造对象
#if defined(ESP32) || defined(ESP8266)
#define LIS331HH_CS  D3
#elif defined(__AVR__) || defined(ARDUINO_SAM_ZERO)
#define LIS331HH_CS 3
#elif (defined NRF5)
#define LIS331HH_CS P3
#endif
/*!
 * @brief Constructor 
 * @param cs : Chip selection pinChip selection pin
 * @param spi :SPI controller
 */
//DFRobot_LIS331HH_SPI acce(/*cs = */LIS331HH_CS);
volatile int intFlag = 0;
void interEvent(){
   intFlag = 1;

}
void setup(void){

  Serial.begin(9600);
  //Chip initialization
  while(acce.begin()){
     Serial.println("init failure");
  }
  Serial.print("chip id : ");
  Serial.println(acce.getID(),HEX);
  
  /**

    set range:Range(g)
                  e6_g = ±6g
                  e12_g = ±12g
                  e24_g = ±24g
  */
  acce.setRange(/*range = */DFRobot_LIS331HH::e6_g);
  
  /**
    Set data measurement rate：
      ePowerDown_0HZ = 0,
      eLowPower_halfHZ,
      eLowPower_1HZ,
      eLowPower_2HZ,
      eLowPower_5HZ,
      eLowPower_10HZ,
      eNormal_50HZ,
      eNormal_100HZ,
      eNormal_400HZ,
      eNormal_1000HZ,
  */
  acce.setAcquireRate(/*rate = */DFRobot_LIS331HH::eLowPower_2HZ);
  #if defined(ESP32) || defined(ESP8266)||defined(ARDUINO_SAM_ZERO)
  attachInterrupt(digitalPinToInterrupt(D6)/*Query the interrupt number of the D6 pin*/,interEvent,CHANGE);
  #else
  /*    The Correspondence Table of AVR Series Arduino Interrupt Pins And Terminal Numbers
   * ---------------------------------------------------------------------------------------
   * |                                        |  DigitalPin  | 2  | 3  |                   |
   * |    Uno, Nano, Mini, other 328-based    |--------------------------------------------|
   * |                                        | Interrupt No | 0  | 1  |                   |
   * |-------------------------------------------------------------------------------------|
   * |                                        |    Pin       | 2  | 3  | 21 | 20 | 19 | 18 |
   * |               Mega2560                 |--------------------------------------------|
   * |                                        | Interrupt No | 0  | 1  | 2  | 3  | 4  | 5  |
   * |-------------------------------------------------------------------------------------|
   * |                                        |    Pin       | 3  | 2  | 0  | 1  | 7  |    |
   * |    Leonardo, other 32u4-based          |--------------------------------------------|
   * |                                        | Interrupt No | 0  | 1  | 2  | 3  | 4  |    |
   * |--------------------------------------------------------------------------------------
   */
  /*                      The Correspondence Table of micro:bit Interrupt Pins And Terminal Numbers
   * ---------------------------------------------------------------------------------------------------------------------------------------------
   * |             micro:bit                       | DigitalPin |P0-P20 can be used as an external interrupt                                     |
   * |  (When using as an external interrupt,      |---------------------------------------------------------------------------------------------|
   * |no need to set it to input mode with pinMode)|Interrupt No|Interrupt number is a pin digital value, such as P0 interrupt number 0, P1 is 1 |
   * |-------------------------------------------------------------------------------------------------------------------------------------------|
   */
  attachInterrupt(/*Interrupt No*/0,interEvent,CHANGE);//Open the external interrupt 0, connect INT1/2 to the digital pin of the main control: 
     //UNO(2), Mega2560(2), Leonardo(3), microbit(P0).
  #endif
  
  /**
    Set the threshold of interrupt source 1 interrupt
    threshold:Threshold(g)
   */
  acce.setInt1Th(/*Threshold = */2);//单位为:g
  
  /**
   * @brief Enable interrupt
   * @param source Interrupt pin selection
              eINT1 = 0,/<int1 >/
              eINT2,/<int2>/
   * @param event:Interrupt event selection
                   eXLowThanTh = 0,/<The acceleration in the x direction is less than the threshold>/
                   eXhigherThanTh ,/<The acceleration in the x direction is greater than the threshold>/
                   eYLowThanTh,/<The acceleration in the y direction is less than the threshold>/
                   eYhigherThanTh,/<The acceleration in the y direction is greater than the threshold>/
                   eZLowThanTh,/<The acceleration in the z direction is less than the threshold>/
                   eZhigherThanTh,/<The acceleration in the z direction is greater than the threshold>/
   */
  acce.enableInterruptEvent(/*int pin*/DFRobot_LIS331HH::eINT1,/*interrupt = */DFRobot_LIS331HH::eYhigherThanTh);
  
  delay(1000);
}

void loop(void){
   //Get the acceleration in the three directions of xyz
   Serial.print("Acceleration x: "); 
   Serial.print(acce.readAccX());
   Serial.print(" g \ty: ");
   Serial.print(acce.readAccY());
   Serial.print(" g \tz: ");
   Serial.print(acce.readAccZ());
   Serial.println(" g");

   
   if(intFlag == 1){
      //Check whether the interrupt event is generated in interrupt 1
      if(acce.getInt1Event(DFRobot_LIS331HH::eYhigherThanTh)){
        Serial.println("The acceleration in the y direction is greater than the threshold");
      }
     if(acce.getInt1Event(DFRobot_LIS331HH::eZhigherThanTh)){
       Serial.println("The acceleration in the z direction is greater than the threshold");
      }
      if(acce.getInt1Event(DFRobot_LIS331HH::eXhigherThanTh)){
        Serial.println("The acceleration in the x direction is greater than the threshold");
      }
      intFlag = 0;
   }
   delay(300);
}