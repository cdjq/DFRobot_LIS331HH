/**！
 * @file wakeUp.ino
 * @brief 让芯片进入低功耗模式，可以降低功耗，当产生中断事件时，芯片从低功耗模式回复正常模式，从而快速采集数据
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2021-01-16
 * @get from https://www.dfrobot.com
 * @https://github.com/DFRobot/DFRobot_LIS331HH
 */

#include <DFRobot_LIS331HH.h>
#if defined(ESP32) || defined(ESP8266)
#define LIS331HH_CS  D5

/* AVR series mainboard */
#else
#define LIS331HH_CS 3
#endif
/*!
 * @brief Constructor 
 * @param cs : Chip selection pinChip selection pin
 * @param spi :SPI controller
 */
DFRobot_LIS331HH_SPI acce(/*cs = */LIS331HH_CS);

//DFRobot_LIS331HH_I2C acce;
void setup(void){

  Serial.begin(9600);
  while(acce.begin()){
     Serial.println("init failure");
  }
  Serial.print("chip id : ");
  Serial.println(acce.getID(),HEX);
  acce.setRange(DFRobot_LIS331HH::eLIS331HH_RANGE_6GA);
  // “sleep to wake-up” function 需要先让芯片处于低功耗模式
  acce.setAcquireRate(DFRobot_LIS331HH::eLowPower_halfHZ);
  //acce.begin();
  acce.setIntOneTh(2);//0 - 100 / 0 - 200 
  acce.enableSleep(true);
   acce.enableInterruptEvent(DFRobot_LIS331HH::eINT1,
                             DFRobot_LIS331HH::eXhigherThanTh);
}

void loop(void){
    DFRobot_LIS331HH::sAccel_t accel = acce.getAcceFromXYZ();
    Serial.print("Acceleration x: "); //print acceleration
    Serial.print(accel.acceleration_x);
    Serial.print(" mg \ty: ");
    Serial.print(accel.acceleration_y);
    Serial.print(" mg \tz: ");
    Serial.print(accel.acceleration_z);
    Serial.println(" mg");
    delay(100);

}