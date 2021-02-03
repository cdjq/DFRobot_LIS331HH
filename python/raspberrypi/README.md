# DFRobot_H3LIS200DL
The LIS331HH is an ultra low-power high 
performance high full-scale three axes linear 
accelerometer belonging to the “nano” family, with 
digital I2C/SPI serial interface standard output. <br>
The device features ultra low-power operational 
modes that allow advanced power saving and 
smart sleep to wake-up functions. <br>
The LIS331HH has dynamically user selectable 
full scales of ±6g/±12g/±24g and it is capable of 
measuring accelerations with output data rates 
from 0.5 Hz to 1 kHz. The self-test capability 
allows the user to check the functioning of the 
sensor in the final application.<br>
The device contains 2 indipendent interrupt 
engines able to recognize dedicated inertial 
events.<br>
Thresholds and timing of interrupt generators are 
programmable by the end user on the fly.<br>
The LIS331HH is available in small thin plastic 
land grid array package (LGA) and it is 
guaranteed to operate over an extended 
temperature range from -40 °C to +85 °C.


## DFRobot_LIS331HH Library for RaspberryPi
---------------------------------------------------------

Provide an RaspberryPi library to get Three-axis acceleration by reading data from LIS331HH.

## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

## Summary

Provide an RaspberryPi library to get Three-axis acceleration by reading data from LIS331HH.


## Installation



## Methods


```python
  '''
    @brief Initialize the function
    @return Return 0 indicates a successful initialization, while other values indicates failure and return to error code.
  '''
  begin(self)
  
  '''
    @brief get chip id
    @return returns the 8 bit serial number
  '''
  get_id(self)

  '''
    @brief Set the measurement range
    @param range:Range(g)
          RANGE_6G = 6#/**<±6G>*/
          RANGE_12G = 12,#/**<±12G>*/
          RANGE_24G = 24#/**<±24G>*/
  '''
  set_range(self,range_r)

  '''
    @brief Set data measurement rate
    @param range:rate(HZ)
                 POWERDOWN_0HZ = 0
                 LOWPOWER_HALFHZ = 1 
                 LOWPOWER_1HZ = 2
                 LOWPOWER_2HZ = 3
                 LOWPOWER_5HZ = 4
                 LOWPOWER_10HZ = 5 
                 NORMAL_50HZ = 6
                 NORMAL_100HZ = 7
                 NORMAL_400HZ = 8
                 NORMAL_1000HZ = 9
  '''
  set_acquire_rate(self, rate)


  '''
    @brief Set the threshold of interrupt source 1 interrupt
    @param threshold:Threshold(g)
  '''
  set_int1_th(self,threshold)

  '''
    @brief Set interrupt source 2 interrupt generation threshold
    @param threshold:Threshold(g)
  '''
  set_int2_th(self,threshold)
  
  '''
    @brief Enable interrupt
    @source Interrupt pin selection
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
  enable_int_event(self,source,event)

  '''
    @brief Check whether the interrupt event'source' is generated in interrupt 1
    @param source:Interrupt event
                  X_LOWTHAN_TH = 0 <The acceleration in the x direction is less than the threshold>
                  X_HIGHERTHAN_TH  = 1<The acceleration in the x direction is greater than the threshold>
                  Y_LOWTHAN_TH = 2<The acceleration in the y direction is less than the threshold>
                  Y_HIGHERTHAN_TH = 3<The acceleration in the y direction is greater than the threshold>
                  Z_LOWTHAN_TH = 4<The acceleration in the z direction is less than the threshold
                  Z_HIGHERTHAN_TH = 5<The acceleration in the z direction is greater than the threshold>
                  EVENT_ERROR = 6 <No event>
    @return true ：produce
            false：Interrupt event
  '''
  get_int1_event(self,source)
         
  '''
    @brief Check whether the interrupt event'source' is generated in interrupt 2
    @param source:Interrupt event
                  X_LOWTHAN_TH = 0 <The acceleration in the x direction is less than the threshold>
                  X_HIGHERTHAN_TH  = 1<The acceleration in the x direction is greater than the threshold>
                  Y_LOWTHAN_TH = 2<The acceleration in the y direction is less than the threshold>
                  Y_HIGHERTHAN_TH = 3<The acceleration in the y direction is greater than the threshold>
                  Z_LOWTHAN_TH = 4<The acceleration in the z direction is less than the threshold
                  Z_HIGHERTHAN_TH = 5<The acceleration in the z direction is greater than the threshold>
                  EVENT_ERROR = 6 <No event>
    @return true ：produce
            false：Interrupt event
  '''
  get_int2_event(self,source)

  '''
    @brief Enable sleep wake function
    @param enable:True(enable)/False(disable)
  '''
  enable_sleep(self, enable)
  
  '''
    @brief Set data filtering mode
    @param mode:Four modes
                CUTOFF_MODE1 = 0
                CUTOFF_MODE2 = 1
                CUTOFF_MODE3 = 2
                CUTOFF_MODE4 = 3
     High-pass filter cut-off frequency configuration
    |--------------------------------------------------------------------------------------------------------|
    |                |    ft [Hz]      |        ft [Hz]       |       ft [Hz]        |        ft [Hz]        |
    |   mode         |Data rate = 50 Hz|   Data rate = 100 Hz |  Data rate = 400 Hz  |   Data rate = 1000 Hz |
    |--------------------------------------------------------------------------------------------------------|
    |  CUTOFF_MODE1  |     1           |         2            |            8         |             20        |
    |--------------------------------------------------------------------------------------------------------|
    |  CUTOFF_MODE2  |    0.5          |         1            |            4         |             10        |
    |--------------------------------------------------------------------------------------------------------|
    |  CUTOFF_MODE3  |    0.25         |         0.5          |            2         |             5         |
    |--------------------------------------------------------------------------------------------------------|
    |  CUTOFF_MODE4  |    0.125        |         0.25         |            1         |             2.5       |
    |--------------------------------------------------------------------------------------------------------|
  '''
  set_filter_mode(self,mode)

  '''
    @brief Get the acceleration in the three directions of xyz
    @return Three-axis acceleration 
  '''
  read_acce_xyz(self)

```

## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
raspberry pi 3             |      √         |            |             | 




## History

- data 2021-1-26
- version V1.0


## Credits

Written by(li.feng@dfrobot.com), 2021. (Welcome to our [website](https://www.dfrobot.com/))
