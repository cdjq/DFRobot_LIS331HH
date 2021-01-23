/**！
 * @file interrupt.ino
 * @brief 启用传感器里面的一些中断事件，并可以通过中断引脚获取中断信号
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2021-01-16
 * @get from https://www.dfrobot.com
 * @https://github.com/DFRobot/DFRobot_LIS331HH
 */

#include <DFRobot_LIS331HH.h>
volatile int Flag = 0;
//DFRobot_LIS331HH_SPI acce;
DFRobot_LIS331HH_I2C acce;
void interEvent(){
   Flag = 1;
  // Serial.println("Flag = 2");
}
void setup(void){

  Serial.begin(9600);
  while(acce.begin()){
     Serial.println("init failure");
  }
  Serial.print("chip id : ");
  Serial.println(acce.getID(),HEX);
  //设置量程
  acce.setRange(DFRobot_LIS331HH::eLIS331HH_RANGE_6GA);
  acce.setAcquireRate(DFRobot_LIS331HH::eLowPower_2HZ);
  //pinMode(2,INPUT);
  attachInterrupt(0,interEvent, CHANGE);//当int.0电平改变时,interEvent
  acce.setIntOneTh(2);//单位为：g
  acce.enableInterruptEvent(DFRobot_LIS331HH::eINT1,DFRobot_LIS331HH::eYhigherThanTh);
 //acce.enableInterruptEvent(DFRobot_LIS331HH::eINT1,DFRobot_LIS331HH::eXhigherThanTh);
 //acce.enableInterruptEvent(DFRobot_LIS331HH::eINT1,DFRobot_LIS331HH::eZhigherThanTh);
  
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
    delay(100);  
   
   if(Flag == 1){
      Serial.println("Flag = 1");
      if(acce.getInt1Event(DFRobot_LIS331HH::eYhigherThanTh)){
        Serial.println("YH");
	  }
     if(acce.getInt1Event(DFRobot_LIS331HH::eZhigherThanTh)){
       Serial.println("ZH");
	  }
      if(acce.getInt1Event(DFRobot_LIS331HH::eXhigherThanTh)){
        Serial.println("XH");
	  }
      Flag = 0;
   }

}