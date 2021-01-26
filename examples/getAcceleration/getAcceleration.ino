/**！
 * @file getAcceleration.ino
 * @brief Get the acceleration in x, y, z directions
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
//DFRobot_LIS331HH_SPI acce(/*cs = */LIS331HH_CS);
/*!
 * @brief Constructor 
 * @param pWire I2c controller
 * @param addr  I2C address(0x19/0x18)
 */
//DFRobot_LIS331HH_I2C acce(&Wire,0x19);
DFRobot_LIS331HH_I2C acce;
void setup(void){

  Serial.begin(9600);
  //Chip initialization
  while(acce.begin()){
     Serial.println("init failure");
  }
  //Get chip id
  Serial.print("chip id : ");
  Serial.println(acce.getID(),HEX);
  
  /**
    set range:Range(g)
              eLis331hhRange_6g /<±6g>/
              eLis331hhRange_12g /<±12g>/
              eLis331hhRange_24g /<±24g>/
  */
  acce.setRange(/*range = */DFRobot_LIS331HH::eLis331hhRange_6g);

  /**
    Set data measurement rate：
      ePowerDown = 0,
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
  acce.setAcquireRate(/*rate = */DFRobot_LIS331HH::eNormal_50HZ);
  delay(1000);
}

void loop(void){
    //Get the acceleration in the three directions of xyz
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