/*!
 * @file DFRobot_LIS331HH.h
 * @brief Define the basic structure of class DFRobot_LIS331HH 
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2020-12-23
 * @get from https://www.dfrobot.com
 * @https://github.com/DFRobot/DFRobot_LIS331HH
 */

#ifndef DFROBOT_LIS331HH_H
#define DFROBOT_LIS331HH_H
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include <Wire.h>
#include <SPI.h>
//#define ENABLE_DBG

#ifdef ENABLE_DBG
#define DBG(...) {Serial.print("["); Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif

#define LIS331HH_I2C_ADDR  (0x19)  /*sensor IIC address*/

//#define ERR_OK             0      //ok
//#define ERR_DATA_BUS      -1      //error in data bus
//#define ERR_IC_VERSION    -2      //chip version mismatch


class DFRobot_LIS331HH
{
  #define REG_CARD_ID    0x0F     /*Chip id*/
  #define REG_CTRL_REG1  0x20     /*Control register 1*/
  #define REG_CTRL_REG4  0x23     /*Control register 4*/
  #define REG_CTRL_REG2  0x21     /*Control register 2*/
  #define REG_CTRL_REG3  0x22     /*Control register 3*/
  #define REG_CTRL_REG5  0x24     /*Control register 5*/
  #define REG_CTRL_REG6  0x25     /*Control register 6*/
  #define REG_STATUS_REG 0x27     /*Status register*/
  #define REG_OUT_X_L      0x28     /*The low order of the X-axis acceleration register*/
  #define REG_OUT_X_H      0x29     /*The high point of the X-axis acceleration register*/
  #define REG_OUT_Y_L      0x2A     /*The low order of the Y-axis acceleration register*/
  #define REG_OUT_Y_H      0x2B     /*The high point of the Y-axis acceleration register*/
  #define REG_OUT_Z_L      0x2C     /*The low order of the Z-axis acceleration register*/
  #define REG_OUT_Z_H      0x2D     /*The high point of the Z-axis acceleration register*/
  #define REG_INT1_THS   0x32     /*Interrupt source 1 threshold*/
  #define REG_INT2_THS   0x36     /*Interrupt source 2 threshold*/
  #define REG_INT1_CFG   0x30     /*Interrupt source 1 configuration register*/
  #define REG_INT2_CFG   0x34     /*Interrupt source 2 configuration register*/
  #define REG_INT1_SRC   0x31     /*Interrupt source 1 status register*/
  #define REG_INT2_SRC   0x35     /*Interrupt source 2 status register*/

public:

/**
  Power mode selection, determine the frequency of data collection
  Represents the number of data collected per second
*/
typedef enum{
   ePowerDown_0HZ = 0,/*测量关闭*/
   eLowPower_halfHZ,/*0.5 hz*/
   eLowPower_1HZ,
   eLowPower_2HZ,
   eLowPower_5HZ,
   eLowPower_10HZ,
   eNormal_50HZ,
   eNormal_100HZ,
   eNormal_400HZ,
   eNormal_1000HZ,
}ePowerMode_t;

/**
  Sensor range selection
*/
typedef enum{
  e6_g = 6,/**<±6g>*/
  e12_g = 12,/**<±12g>*/
  e24_g = 24/**<±24g>*/
}eRange_t;

/*!     High-pass filter cut-off frequency configuration
 * |--------------------------------------------------------------------------------------------------------|
 * |                |    ft [Hz]      |        ft [Hz]       |       ft [Hz]        |        ft [Hz]        |
 * |   mode         |Data rate = 50 Hz|   Data rate = 100 Hz |  Data rate = 400 Hz  |   Data rate = 1000 Hz |
 * |--------------------------------------------------------------------------------------------------------|
 * |  eCutoffMode1  |     1           |         2            |            8         |             20        |
 * |--------------------------------------------------------------------------------------------------------|
 * |  eCutoffMode2  |    0.5          |         1            |            4         |             10        |
 * |--------------------------------------------------------------------------------------------------------|
 * |  eCutoffMode3  |    0.25         |         0.5          |            2         |             5         |
 * |--------------------------------------------------------------------------------------------------------|
 * |  eCutoffMode4  |    0.125        |         0.25         |            1         |             2.5       |
 * |--------------------------------------------------------------------------------------------------------|
 */
typedef enum{
  eCutoffMode1 = 0,
  eCutoffMode2,
  eCutoffMode3,
  eCutoffMode4,
  eShutDown,
}eHighPassFilter_t;

/**
  Interrupt event
*/
typedef enum{
  eXLowThanTh = 0,/**<The acceleration in the x direction is less than the threshold>*/
  eXhigherThanTh ,/**<The acceleration in the x direction is greater than the threshold>*/
  eYLowThanTh,/**<The acceleration in the y direction is less than the threshold>*/
  eYhigherThanTh,/**<The acceleration in the y direction is greater than the threshold>*/
  eZLowThanTh,/**<The acceleration in the z direction is less than the threshold>*/
  eZhigherThanTh,/**<The acceleration in the z direction is greater than the threshold>*/
  eEventError,/**< No event>*/
}eInterruptEvent_t;

/**
  Interrupt pin selection
*/
typedef enum{
  eINT1 = 0,/**<int1 >*/
  eINT2,/**<int2>*/
}eInterruptSource_t;

/**
  Store acceleration in three directions
*/
typedef struct
{
 long acceleration_x;/**<acceleration in x direction(g)>*/
 long acceleration_y;/**<acceleration in y direction(g)>*/
 long acceleration_z;/**<acceleration in z direction(g)>*/
}sAccel_t;

public:
  DFRobot_LIS331HH();
    
  /**
   * @brief Initialize the function
   * @return Return 0 indicates a successful initialization, while other values indicates failure and return to error code.
   */
  int begin(void);
 
  /**
   * @brief Get chip id
   * @return Returns the 8 bit serial number
   */
  uint8_t getID();
  
  /**
   * @brief Enable interrupt
   * @ source Interrupt pin selection
              eINT1 = 0,/<int1 >/
              eINT2,/<int2>/
   * @param event Interrupt event selection
                   eXLowThanTh = 0,/<The acceleration in the x direction is less than the threshold>/
                   eXhigherThanTh ,/<The acceleration in the x direction is greater than the threshold>/
                   eYLowThanTh,/<The acceleration in the y direction is less than the threshold>/
                   eYhigherThanTh,/<The acceleration in the y direction is greater than the threshold>/
                   eZLowThanTh,/<The acceleration in the z direction is less than the threshold>/
                   eZhigherThanTh,/<The acceleration in the z direction is greater than the threshold>/
   */
  void enableInterruptEvent(eInterruptSource_t source, eInterruptEvent_t event);
  
  /**
   * @brief Set the measurement range
   * @param range Range(g)
                  e6_g = ±6g
                  e12_g = ±12g
                  e24_g = ±24g
   */
  void setRange(eRange_t range);
  
  /**
   * @brief Set data measurement rate
   * @param range:rate(HZ)
                  ePowerDown_0HZ   //测量关闭
                  eLowPower_halfHZ //0.5 hz
                  eLowPower_1HZ
                  eLowPower_2HZ
                  eLowPower_5HZ
                  eLowPower_10HZ
                  eNormal_50HZ
                  eNormal_100HZ
                  eNormal_400HZ
                  eNormal_1000HZ
   */
  void setAcquireRate(ePowerMode_t rate);
  
  /**
   * @brief Set data filtering mode
   * @param mode Four modes
                 eCutoffMode1 = 0,
                 eCutoffMode2,
                 eCutoffMode3,
                 eCutoffMode4,
                 eShutDown,  无过滤
   *|---------------------------High-pass filter cut-off frequency configuration-----------------------------|
   *|--------------------------------------------------------------------------------------------------------|
   *|                |    ft [Hz]      |        ft [Hz]       |       ft [Hz]        |        ft [Hz]        |
   *|   mode         |Data rate = 50 Hz|   Data rate = 100 Hz |  Data rate = 400 Hz  |   Data rate = 1000 Hz |
   *|--------------------------------------------------------------------------------------------------------|
   *|  eCutoffMode1  |     1           |         2            |            8         |             20        |
   *|--------------------------------------------------------------------------------------------------------|
   *|  eCutoffMode2  |    0.5          |         1            |            4         |             10        |
   *|--------------------------------------------------------------------------------------------------------|
   *|  eCutoffMode3  |    0.25         |         0.5          |            2         |             5         |
   *|--------------------------------------------------------------------------------------------------------|
   *|  eCutoffMode4  |    0.125        |         0.25         |            1         |             2.5       |
   *|--------------------------------------------------------------------------------------------------------|
   */
  void setHFilterMode(eHighPassFilter_t mode);

  /**
   * @brief Set the threshold of interrupt source 1 interrupt
   * @param threshold 设置的阈值在量程之内(unit:g)
   */
  void setInt1Th(uint8_t threshold);
  
  /**
   * @brief Set interrupt source 2 interrupt generation threshold
   * @param threshold 设置de阈值在量程之内(unit:g）
   */
  void setInt2Th(uint8_t threshold);
  
  /**
   * @brief Enable sleep wake function
   * @param enable true(enable)\false(disable)
   * @return 1 表示使能失败/0 表示使能成功
   */
  int enableSleep(bool enable);

  /**
   * @brief Check whether the interrupt event'source' is generated in interrupt 1
   * @param source Interrupt event
                   eXLowThanTh = 0,/<The acceleration in the x direction is less than the threshold>/
                   eXhigherThanTh ,/<The acceleration in the x direction is greater than the threshold>/
                   eYLowThanTh,/<The acceleration in the y direction is less than the threshold>/
                   eYhigherThanTh,/<The acceleration in the y direction is greater than the threshold>/
                   eZLowThanTh,/<The acceleration in the z direction is less than the threshold>/
                   eZhigherThanTh,/<The acceleration in the z direction is greater than the threshold>/
   * @return true produce
             false Interrupt event
   */
  bool getInt1Event(eInterruptEvent_t source);
  
  /**
   * @brief Check whether the interrupt event'source' is generated in interrupt 2
   * @param source Interrupt event
    in the y direction is less than the threshold>/
                   eYhigherThanTh,/<The acceleration in the y direction is greater than the threshold>/
                   eZLowThanTh,/<The acceleration in the z direction is less than the threshold>/
                       eXLowThanTh = 0,/<The acceleration in the x direction is less than the threshold>/
                   eXhigherThanTh ,/<The acceleration in the x direction is greater than the threshold>/
                   eYLowThanTh,/<The acceleration            eZhigherThanTh,/<The acceleration in the z direction is greater than the threshold>/
   * @return true produce
             false Interrupt event
   */
  bool getInt2Event(eInterruptEvent_t source);
  
  /**
   * @brief Get the acceleration in the x direction
   * @return acceleration (unit:g)
   */
  long readAccX();
  
  /**
   * @brief Get the acceleration in the y direction
   * @return acceleration (unit:g)
   */
  long readAccY();
  
  /**
   * @brief Get the acceleration in the z direction
   * @return acceleration (unit:g)
   */
  long readAccZ();
  
  /**
   * @brief Get the acceleration in the three directions of xyz
   * @param accx 储存x方向加速度的变量
   * @param accy 储存y方向加速度的变量
   * @param accz 储存z方向加速度的变量
   */
  bool getAcceFromXYZ(long &accx,long &accy,long &accz);
protected:
  uint8_t _interface = 0;
  uint8_t reset = 0;
  eRange_t _range = e6_g;
  //uint8_t sensorData[6];
  //uint8_t readFlag = 0;
  //uint8_t dir = 1;
  //uint8_t dir = 1;
  virtual uint8_t readReg(uint8_t reg,void * pBuf ,size_t size) = 0;
  /**
   * @brief Write command into sensor chip 
   * @param reg  
   * @param data  Data included in command
   * @param size  The number of the byte of command
   */
  virtual uint8_t  writeReg(uint8_t reg,const void *pBuf,size_t size)= 0; 
private:
  /**
   * @brief Get the acceleration in the three directions of xyz
   * @return Three-axis acceleration 
             acceleration_x;
             acceleration_y;
             acceleration_z;
   */
  sAccel_t getAcceFromXYZ();
   void enableXYZ();
};



class DFRobot_LIS331HH_I2C : public DFRobot_LIS331HH{
public:
  /*!
   * @brief Constructor 
   * @param pWire I2c controller
   * @param addr  I2C address(0x19/0x18)
   */
  DFRobot_LIS331HH_I2C(TwoWire * pWire = &Wire,uint8_t addr = LIS331HH_I2C_ADDR);
  /**
   * @brief init function
   * @return Return 1 if initialization succeeds, otherwise return non-zero and error code.
   */
  int begin(void);
protected:

  /**
   * @brief Write command into sensor chip 
   * @param 
   * @param data  Data included in command
   * @param size  The number of the byte of command
   */
    uint8_t readReg(uint8_t reg,void * pBuf ,size_t size);
  /**
   * @brief Write command into sensor chip 
   * @param reg  
   * @param data  Data included in command
   * @param size  The number of the byte of command
   */
    uint8_t  writeReg(uint8_t reg,const void *pBuf,size_t size); 
private:
    uint8_t _deviceAddr;
    TwoWire *_pWire;
};
class DFRobot_LIS331HH_SPI : public DFRobot_LIS331HH{

public:

  /*!
   * @brief Constructor 
   * @param cs : Chip selection pinChip selection pin
   * @param spi :SPI controller
   */
  DFRobot_LIS331HH_SPI(uint8_t cs,SPIClass *spi=&SPI);
  
  /**
   * @brief init function
   * @return Return 1 if initialization succeeds, otherwise return non-zero and error code.
   */
  int begin(void);
protected:

  /**
   * @brief Write command into sensor chip 
   * @param 
   * @param data  Data included in command
   * @param size  The number of the byte of command
   */
    uint8_t readReg(uint8_t reg,void * pBuf ,size_t size);
  /**
   * @brief Write command into sensor chip 
   * @param reg  
   * @param data  Data included in command
   * @param size  The number of the byte of command
   */
    uint8_t  writeReg(uint8_t reg,const void *pBuf,size_t size); 
private:
    SPIClass *_pSpi;
    uint8_t _cs;
};

#endif
