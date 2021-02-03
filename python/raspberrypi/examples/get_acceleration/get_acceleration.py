# -*- coding:utf-8 -*-
"""
  @file get_acceleration.py
  @brief Get the acceleration in x, y, z directions
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





#如果你想要用SPI驱动此模块，打开下面两行的注释,并通过SPI连接好模块和树莓派
#RASPBERRY_PIN_CS =  27              #Chip selection pin when SPI is selected
#acce = DFRobot_LIS331HH_SPI(RASPBERRY_PIN_CS)


#如果你想要应IIC驱动此模块，打卡下面三行的注释，并通过I2C连接好模块和树莓派
I2C_MODE         = 0x01             #default use I2C1
ADDRESS_0        = 0x19             #I2C address
acce = DFRobot_LIS331HH_I2C(I2C_MODE ,ADDRESS_0)

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
acce.set_acquire_rate(acce.NORMAL_50HZ)
time.sleep(0.1)

while True:
    #Get the acceleration in the three directions of xyz
    x,y,z = acce.read_acce_xyz()
    time.sleep(1)
    print("Acceleration [X = %.2d g,Y = %.2d g,Z = %.2d g]"%(x,y,z))
