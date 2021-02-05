# -*- coding:utf-8 -*-
"""
   @file wake_up.py
 * @brief Use sleep wakeup function
   @n 现象：在睡眠唤醒功能里面，当有中断产生，传感器采集速率明显变快
   @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
   @licence     The MIT License (MIT)
   @author [fengli](li.feng@dfrobot.com)
   @version  V1.0
   @date  2021-01-16
   @get from https://www.dfrobot.com
   @https://github.com/DFRobot/DFRobot_LIS331HH
"""

import sys
sys.path.append("../..") # set system path to top

from DFRobot_LIS331HH import *
import time

INT1 = 26                           #Interrupt pin
int_pad_Flag = False                 #intPad flag
def int_pad_callback():
  global int_pad_Flag
  int_pad_Flag = True

#如果你想要用SPI驱动此模块，打开下面两行的注释,并通过SPI连接好模块和树莓派
#RASPBERRY_PIN_CS =  27              #Chip selection pin when SPI is selected
#acce = DFRobot_LIS331HH_SPI(RASPBERRY_PIN_CS)


#如果你想要应IIC驱动此模块，打开下面三行的注释，并通过I2C连接好模块和树莓派
I2C_MODE         = 0x01             #default use I2C1
ADDRESS_0        = 0x19             #I2C address
acce = DFRobot_LIS331HH_I2C(I2C_MODE ,ADDRESS_0)

int_pad.setInterrupt(GPIO.FALLING, int_pad_callback) #set int_Pad 

#Chip initialization
acce.begin()
#Get chip id
print("chip id :")
print(acce.get_id())

'''
set range:Range(g)
          RANGE_6G = 6#/**<±6G>*/
          RANGE_12G = 12,#/**<±12G>*/
          RANGE_24G = 24#/**<±24G>*/
'''
acce.set_range(acce.RANGE_6G)

'''
Set data measurement rate
         POWERDOWN_0HZ 
         LOWPOWER_HALFHZ 
         LOWPOWER_1HZ 
         LOWPOWER_2HZ 
         LOWPOWER_5HZ 
         LOWPOWER_10HZ 
         NORMAL_50HZ 
         NORMAL_100HZ 
         NORMAL_400HZ 
         NORMAL_1000HZ 
'''
acce.set_acquire_rate(acce.LOWPOWER_HALFHZ)
'''
   Set the threshold of interrupt source 1 interrupt
   threshold Threshold(g),范围是设置好的的测量量程
'''
acce.set_int1_th(5)

#Enable sleep wake function
acce.enable_sleep(True)

'''
@brief Enable interrupt
@param source Interrupt pin selection
         INT_1 = 0,/<int pad 1 >/
         INT_2,/<int pad 2>/
@param event Interrupt event selection
             X_LOWTHAN_TH = 0 <The acceleration in the x direction is less than the threshold>
             X_HIGHERTHAN_TH  = 1<The acceleration in the x direction is greater than the threshold>
             Y_LOWTHAN_TH = 2<The acceleration in the y direction is less than the threshold>
             Y_HIGHERTHAN_TH = 3<The acceleration in the y direction is greater than the threshold>
             Z_LOWTHAN_TH = 4<The acceleration in the z direction is less than the threshold
             Z_HIGHERTHAN_TH = 5<The acceleration in the z direction is greater than the threshold>
             EVENT_ERROR = 6 <No event>
'''
acce.enable_int_event(acce.INT_1,acce.Y_HIGHERTHAN_TH)
time.sleep(1)

while True:
    #Get the acceleration in the three directions of xyz
    #当有中断产生，能观察到芯片测量的频率明显变快
    x,y,z = acce.read_acce_xyz()
    time.sleep(0.1)
    print("Acceleration [X = %.2f g,Y = %.2f g,Z = %.2f g]"%(x,y,z))
    if(int_pad_Flag == True):
      print("Out of sleep mode")
