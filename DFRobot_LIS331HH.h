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
#define ENABLE_DBG

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
  #define H3LIS200DL_REG_CARD_ID    0x0F     /*Chip id*/
  #define H3LIS200DL_REG_CTRL_REG1  0x20     /*Control register 1*/
  #define H3LIS200DL_REG_CTRL_REG4  0x23     /*Control register 4*/
  #define H3LIS200DL_REG_CTRL_REG2  0x21     /*Control register 2*/
  #define H3LIS200DL_REG_CTRL_REG3  0x22     /*Control register 3*/
  #define H3LIS200DL_REG_CTRL_REG5  0x24     /*Control register 5*/
  #define H3LIS200DL_REG_CTRL_REG6  0x25     /*Control register 6*/
  #define H3LIS200DL_REG_STATUS_REG 0x27     /*Status register*/
  #define LIS331HH_REG_OUT_X_L      0x28     /*The low order of the X-axis acceleration register*/
  #define LIS331HH_REG_OUT_X_H      0x29     /*The high point of the X-axis acceleration register*/
  #define LIS331HH_REG_OUT_Y_L      0x2A     /*The low order of the Y-axis acceleration register*/
  #define LIS331HH_REG_OUT_Y_H      0x2B     /*The high point of the Y-axis acceleration register*/
  #define LIS331HH_REG_OUT_Z_L      0x2C     /*The low order of the Z-axis acceleration register*/
  #define LIS331HH_REG_OUT_Z_H      0x2D     /*The high point of the Z-axis acceleration register*/
  #define H3LIS200DL_REG_INT1_THS   0x32     /*Interrupt source 1 threshold*/
  #define H3LIS200DL_REG_INT2_THS   0x36     /*Interrupt source 2 threshold*/
  #define H3LIS200DL_REG_INT1_CFG   0x30     /*Interrupt source 1 configuration register*/
  #define H3LIS200DL_REG_INT2_CFG   0x34     /*Interrupt source 2 configuration register*/
  #define H3LIS200DL_REG_INT1_SRC   0x31     /*Interrupt source 1 status register*/
  #define H3LIS200DL_REG_INT2_SRC   0x35     /*Interrupt source 2 status register*/

public:

/**
  Power mode selection, determine the frequency of data collection
*/
typedef enum{
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
}ePowerMode_t;

/**
  Sensor range selection
*/
typedef enum{
  eLIS331HH_RANGE_6GA = 6,
  eLIS331HH_RANGE_12GA = 12,
  eLIS331HH_RANGE_24GA = 24
}eRange_t;

/**
  Filtering mode
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

typedef struct
{
 long acceleration_x;
 long acceleration_y;
 long acceleration_z;
}sAccel_t;

public:
  DFRobot_LIS331HH();
    
  /**
   * @brief Initialize the function
   * @return Return 0 indicates a successful initialization, while other values indicates failure and return to error code.
   */
  int begin(void);
  uint8_t getID();
  void enableXYZ();
  void enableInterruptEvent(eInterruptSource_t source, eInterruptEvent_t event);
  void setRange(eRange_t range);
  void setAcquireRate(ePowerMode_t rate);
  void setHFilterMode(eHighPassFilter_t mode);
  void setIntOneTh(uint8_t threshold);//0 - 100 / 0 - 200 
  void setIntTwoTh(uint8_t threshold);//0 - 100 / 0 - 200 
  int readACCFromX();
  int readACCFromY();
  int readACCFromZ();
  sAccel_t getAcceFromXYZ();
  int enableSleep(bool enable);
  /*
  void setInt1PadSource(eInterruptSource_t source);
  void setInt2PadSource(eInterruptSource_t source);
  */
  bool getInt1Event(eInterruptEvent_t source);
  bool getInt2Event(eInterruptEvent_t source);
  
protected:
  uint8_t _interface = 0;
  uint8_t reset = 0;
  eRange_t _range = eLIS331HH_RANGE_6GA;
  virtual uint8_t readReg(uint8_t reg,uint8_t * pBuf ,size_t size) = 0;
  /**
   * @brief Write command into sensor chip 
   * @param reg  
   * @param data  Data included in command
   * @param size  The number of the byte of command
   */
  virtual uint8_t  writeReg(uint8_t reg,const void *pBuf,size_t size)= 0; 
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
private:

  /**
   * @brief Write command into sensor chip 
   * @param 
   * @param data  Data included in command
   * @param size  The number of the byte of command
   */
    uint8_t readReg(uint8_t reg,uint8_t * pBuf ,size_t size);
  /**
   * @brief Write command into sensor chip 
   * @param reg  
   * @param data  Data included in command
   * @param size  The number of the byte of command
   */
    uint8_t  writeReg(uint8_t reg,const void *pBuf,size_t size); 
    uint8_t _deviceAddr;
    TwoWire *_pWire;
};
class DFRobot_LIS331HH_SPI : public DFRobot_LIS331HH{

public:
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
    uint8_t readReg(uint8_t reg,uint8_t * pBuf ,size_t size);
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