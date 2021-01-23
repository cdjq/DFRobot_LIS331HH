/**！
 * @file getAcceleration.ino
 * @brief 获取 x,y,z方向上的加速度
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
  //设置量程
  acce.setRange(DFRobot_LIS331HH::eLIS331HH_RANGE_6GA);
  acce.setAcquireRate(DFRobot_LIS331HH::eNormal_50HZ);
  delay(1000);
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
    delay(300);
}