# -*- coding:utf-8 -*-
"""
   @file wakeUp.py
 * @brief Use sleep wakeup function
   @n when the sensor is in low power consumption mode, when an interrupt is generated, the sensor will work in normal mode
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

# peripheral params
RASPBERRY_PIN_CS = 27              #Chip selection pin
I2C_MODE         = 0x01            # default use I2C1
ADDRESS_0        = 0x19
acce = DFRobot_LIS331HH_SPI(RASPBERRY_PIN_CS)
#
#acce = DFRobot_LIS331HH_I2C(I2C_MODE ,ADDRESS_0)
# clear screen
acce.begin()
print("chip id :")
print(acce.getID())

'''
    set range:Range(g)
              E_LIS331HH_RANGE_6G = 6,#/**<±6G>*/
              E_LIS331HH_RANGE_12G = 12,#/**<±12G>*/
              E_LIS331HH_RANGE_24G = 24#/**<±24G>*/
'''
acce.setRange(acce.E_LIS331HH_RANGE_6G)

'''
    Set data measurement rate�?
           E_POWER_DOWN 
           E_LOWPOWER_HALFHZ 
           E_LOWPOWER_1HZ 
           E_LOWPOWER_2HZ 
           E_LOWPOWER_5HZ 
           E_LOWPOWER_10HZ 
           E_NORMAL_50HZ 
           E_NORMAL_100HZ 
           E_NORMAL_400HZ 
           E_NORMAL_1000HZ 
'''
acce.setAcquireRate(acce.E_LOWPOWER_HALFHZ)
'''
   Set the threshold of interrupt source 1 interrupt
   threshold:Threshold(g)
'''
acce.setIntOneTh(3); 

#Enable sleep wake function
acce.enableSleep(True);

'''
  @brief Enable interrupt
  @ source:Interrupt pin selection
           eINT1 = 0,/<int1 >/
           eINT2,/<int2>/
  @param event:Interrupt event selection
                eXLowThanTh = 0,/<The acceleration in the x direction is less than the threshold>/
                eXhigherThanTh ,/<The acceleration in the x direction is greater than the threshold>/
                eYLowThanTh,/<The acceleration in the y direction is less than the threshold>/
                eYhigherThanTh,/<The acceleration in the y direction is greater than the threshold>/
                eZLowThanTh,/<The acceleration in the z direction is less than the threshold>/
                eZhigherThanTh,/<The acceleration in the z direction is greater than the threshold>/
'''
acce.enableInterruptEvent(acce.eINT1,acce.E_X_HIGHERTHAN_TH)
time.sleep(1)

while True:
    #Get the acceleration in the three directions of xyz
    x,y,z = acce.readAcceFromXYZ()
    time.sleep(0.1)
    print("Acceleration [X = %.2f mg,Y = %.2f mg,Z = %.2f mg]"%(x,y,z))
