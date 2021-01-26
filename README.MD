# DFRobot_LIS331HH
The LIS331HH is an ultra low-power high <br>
performance high full-scale three axes linear <br>
accelerometer belonging to the “nano” family, with <br>
digital I2C/SPI serial interface standard output. <br>
The device features ultra low-power operational <br>
modes that allow advanced power saving and <br>
smart sleep to wake-up functions. <br>
The LIS331HH has dynamically user selectable <br>
full scales of ±6g/±12g/±24g and it is capable of <br>
measuring accelerations with output data rates <br>
from 0.5 Hz to 1 kHz. The self-test capability <br>
allows the user to check the functioning of the <br>
sensor in the final application.<br>
The device contains 2 indipendent interrupt <br>
engines able to recognize dedicated inertial <br>
events.<br>
Thresholds and timing of interrupt generators are <br>
programmable by the end user on the fly.<br>
The LIS331HH is available in small thin plastic <br>
land grid array package (LGA) and it is <br>
guaranteed to operate over an extended <br>
temperature range from -40 °C to +85 °C.<br>

## DFRobot_LIS331HH Library for Arduino
---------------------------------------------------------

Provide an Arduino library to get Three-axis acceleration by reading data from LIS331HH.

## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

## Summary

Provide an Arduino library to get Three-axis acceleration by reading data from LIS331HH.

## Installation

To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

## Methods

```C++
#include <DFRobot_LIS331HH.h>
  DFRobot_LIS331HH();
    
  /**
   * @brief Initialize the function
   * @return Return 0 indicates a successful initialization, while other values indicates failure and return to error code.
   */
  int begin(void);
 
  /**
   * @brief Get chip id
   * @return Returns the eight-digit serial number
   */
  uint8_t getID();
  
  /**
   * @brief Enable interrupt
   * @param source:Interrupt pin selection
   * @param event:Interrupt event selection
   */
  void enableInterruptEvent(eInterruptSource_t source, eInterruptEvent_t event);
  
  /**
   * @brief Set the measurement range
   * @param range:Range(g)
                  eLis331hhRange_6g = ±6
                  eLis331hhRange_12g = ±12g
                  eLis331hhRange_24g = ±24g
   */
  void setRange(eRange_t range);
  
  /**
   * @brief Set data measurement rate
   * @param range:rate(g)
   */
  void setAcquireRate(ePowerMode_t rate);
  
  /**
   * @brief Set data filtering mode
   * @param mode:Four modes
                 eCutoffMode1 = 0,
                 eCutoffMode2,
                 eCutoffMode3,
                 eCutoffMode4,
                 eShutDown,
   */
  void setHFilterMode(eHighPassFilter_t mode);

  /**
   * @brief Set the threshold of interrupt source 1 interrupt
   * @param threshold:Threshold(g)
   */
  void setIntOneTh(uint8_t threshold);
  
  /**
   * @brief Set interrupt source 2 interrupt generation threshold
   * @param threshold:Threshold(g)
   */
  void setIntTwoTh(uint8_t threshold);
  
  /**
   * @brief Get the acceleration in the three directions of xyz
   * @return Three-axis acceleration 
             acceleration_x;
             acceleration_y;
             acceleration_z;
   */
  sAccel_t getAcceFromXYZ();

  /**
   * @brief Enable sleep wake function
   * @param enable:true\false
   * @return 0
   */
  int enableSleep(bool enable);

  /**
   * @brief Check whether the interrupt event'source' is generated in interrupt 1
   * @param source:Interrupt event
                   eXLowThanTh = 0,/<The acceleration in the x direction is less than the threshold>/
                   eXhigherThanTh ,/<The acceleration in the x direction is greater than the threshold>/
                   eYLowThanTh,/<The acceleration in the y direction is less than the threshold>/
                   eYhigherThanTh,/<The acceleration in the y direction is greater than the threshold>/
                   eZLowThanTh,/<The acceleration in the z direction is less than the threshold>/
                   eZhigherThanTh,/<The acceleration in the z direction is greater than the threshold>/
   * @return true ：produce
             false：Interrupt event
   */
  bool getInt1Event(eInterruptEvent_t source);
  
  /**
   * @brief Check whether the interrupt event'source' is generated in interrupt 2
   * @param source:Interrupt event
                   eXLowThanTh = 0,/<The acceleration in the x direction is less than the threshold>/
                   eXhigherThanTh ,/<The acceleration in the x direction is greater than the threshold>/
                   eYLowThanTh,/<The acceleration in the y direction is less than the threshold>/
                   eYhigherThanTh,/<The acceleration in the y direction is greater than the threshold>/
                   eZLowThanTh,/<The acceleration in the z direction is less than the threshold>/
                   eZhigherThanTh,/<The acceleration in the z direction is greater than the threshold>/
   * @return true ：produce
             false：Interrupt event
   */
  bool getInt2Event(eInterruptEvent_t source);


```

## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino uno        |      √       |              |             | 
FireBeetle-ESP8266        |      √       |              |             | 
FireBeetle-ESP32        |      √       |              |             | 
掌控板        |      √       |              |             | 
树莓派        |      √       |              |             | 
microbit        |      √       |              |             | 



## History

- data 2020-12-31
- version V1.0


## Credits

Written by(li.feng@dfrobot.com), 2020. (Welcome to our [website](https://www.dfrobot.com/))
