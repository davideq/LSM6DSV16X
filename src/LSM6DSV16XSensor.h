/**
 ******************************************************************************
 * @file    LSM6DSV16XSensor.h
 * @author  STMicroelectronics
 * @version V1.0.0
 * @date    July 2022
 * @brief   Abstract Class of a LSM6DSV16X inertial measurement sensor.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2022 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */


/* Prevent recursive inclusion -----------------------------------------------*/

#ifndef __LSM6DSV16XSensor_H__
#define __LSM6DSV16XSensor_H__


/* Includes ------------------------------------------------------------------*/

#include "Wire.h"
#include "SPI.h"
#include "lsm6dsv16x_reg.h"


/* Defines -------------------------------------------------------------------*/
/* For compatibility with ESP32 platforms */
#ifdef ESP32
  #ifndef MSBFIRST
    #define MSBFIRST SPI_MSBFIRST
  #endif
#endif

#define LSM6DSV16X_ACC_SENSITIVITY_FS_2G   0.061f
#define LSM6DSV16X_ACC_SENSITIVITY_FS_4G   0.122f
#define LSM6DSV16X_ACC_SENSITIVITY_FS_8G   0.244f
#define LSM6DSV16X_ACC_SENSITIVITY_FS_16G  0.488f

#define LSM6DSV16X_GYRO_SENSITIVITY_FS_125DPS     4.375f
#define LSM6DSV16X_GYRO_SENSITIVITY_FS_250DPS     8.750f
#define LSM6DSV16X_GYRO_SENSITIVITY_FS_500DPS    17.500f
#define LSM6DSV16X_GYRO_SENSITIVITY_FS_1000DPS   35.000f
#define LSM6DSV16X_GYRO_SENSITIVITY_FS_2000DPS   70.000f
#define LSM6DSV16X_GYRO_SENSITIVITY_FS_4000DPS  140.000f

#define LSM6DSV16X_QVAR_GAIN  78.000f

/* Typedefs ------------------------------------------------------------------*/

typedef enum {
  LSM6DSV16X_OK = 0,
  LSM6DSV16X_ERROR = -1
} LSM6DSV16XStatusTypeDef;

typedef enum {
  LSM6DSV16X_INT1_PIN,
  LSM6DSV16X_INT2_PIN,
} LSM6DSV16X_SensorIntPin_t;

typedef struct {
  unsigned int FreeFallStatus : 1;
  unsigned int TapStatus : 1;
  unsigned int DoubleTapStatus : 1;
  unsigned int WakeUpStatus : 1;
  unsigned int StepStatus : 1;
  unsigned int TiltStatus : 1;
  unsigned int D6DOrientationStatus : 1;
  unsigned int SleepStatus : 1;
} LSM6DSV16X_Event_Status_t;

typedef union {
  int16_t i16bit[3];
  uint8_t u8bit[6];
} lsm6dsv16x_axis3bit16_t;

typedef union {
  int16_t i16bit;
  uint8_t u8bit[2];
} lsm6dsv16x_axis1bit16_t;

typedef enum {
  LSM6DSV16X_ACC_HIGH_PERFORMANCE_MODE,
  LSM6DSV16X_ACC_HIGH_ACCURACY_MODE,
  LSM6DSV16X_ACC_NORMAL_MODE,
  LSM6DSV16X_ACC_LOW_POWER_MODE1,
  LSM6DSV16X_ACC_LOW_POWER_MODE2,
  LSM6DSV16X_ACC_LOW_POWER_MODE3
} LSM6DSV16X_ACC_Operating_Mode_t;

typedef enum {
  LSM6DSV16X_GYRO_HIGH_PERFORMANCE_MODE,
  LSM6DSV16X_GYRO_HIGH_ACCURACY_MODE,
  LSM6DSV16X_GYRO_SLEEP_MODE,
  LSM6DSV16X_GYRO_LOW_POWER_MODE
} LSM6DSV16X_GYRO_Operating_Mode_t;


/* Class Declaration ---------------------------------------------------------*/

/**
 * Abstract class of a LSM6DSV16X sensor.
 */
class LSM6DSV16XSensor {
  public:
    LSM6DSV16XSensor(TwoWire *i2c, uint8_t address = LSM6DSV16X_I2C_ADD_H);
    LSM6DSV16XSensor(SPIClass *spi, int cs_pin, uint32_t spi_speed = 2000000);

    LSM6DSV16XStatusTypeDef begin();
    LSM6DSV16XStatusTypeDef end();
    LSM6DSV16XStatusTypeDef ReadID(uint8_t *Id);

    LSM6DSV16XStatusTypeDef Enable_X();
    LSM6DSV16XStatusTypeDef Disable_X();
    LSM6DSV16XStatusTypeDef Get_X_Sensitivity(float *Sensitivity);
    LSM6DSV16XStatusTypeDef Get_X_ODR(float *Odr);
    LSM6DSV16XStatusTypeDef Set_X_ODR(float Odr, LSM6DSV16X_ACC_Operating_Mode_t Mode = LSM6DSV16X_ACC_HIGH_PERFORMANCE_MODE);
    LSM6DSV16XStatusTypeDef Get_X_FS(int32_t *FullScale);
    LSM6DSV16XStatusTypeDef Set_X_FS(int32_t FullScale);
    LSM6DSV16XStatusTypeDef Get_X_AxesRaw(int16_t *Value);
    LSM6DSV16XStatusTypeDef Get_X_Axes(int32_t *Acceleration);
    LSM6DSV16XStatusTypeDef Get_X_DRDY_Status(uint8_t *Status);
    LSM6DSV16XStatusTypeDef Get_X_Event_Status(LSM6DSV16X_Event_Status_t *Status);
    LSM6DSV16XStatusTypeDef Set_X_Power_Mode(uint8_t PowerMode);
    LSM6DSV16XStatusTypeDef Set_X_Filter_Mode(uint8_t LowHighPassFlag, uint8_t FilterMode);

    LSM6DSV16XStatusTypeDef Enable_G();
    LSM6DSV16XStatusTypeDef Disable_G();
    LSM6DSV16XStatusTypeDef Get_G_Sensitivity(float *Sensitivity);
    LSM6DSV16XStatusTypeDef Get_G_ODR(float *Odr);
    LSM6DSV16XStatusTypeDef Set_G_ODR(float Odr, LSM6DSV16X_GYRO_Operating_Mode_t Mode = LSM6DSV16X_GYRO_HIGH_PERFORMANCE_MODE);
    LSM6DSV16XStatusTypeDef Get_G_FS(int32_t *FullScale);
    LSM6DSV16XStatusTypeDef Set_G_FS(int32_t FullScale);
    LSM6DSV16XStatusTypeDef Get_G_AxesRaw(int16_t *Value);
    LSM6DSV16XStatusTypeDef Get_G_Axes(int32_t *AngularRate);
    LSM6DSV16XStatusTypeDef Get_G_DRDY_Status(uint8_t *Status);
    LSM6DSV16XStatusTypeDef Set_G_Power_Mode(uint8_t PowerMode);
    LSM6DSV16XStatusTypeDef Set_G_Filter_Mode(uint8_t LowHighPassFlag, uint8_t FilterMode);

    LSM6DSV16XStatusTypeDef Enable_6D_Orientation(LSM6DSV16X_SensorIntPin_t IntPin);
    LSM6DSV16XStatusTypeDef Disable_6D_Orientation();
    LSM6DSV16XStatusTypeDef Set_6D_Orientation_Threshold(uint8_t Threshold);
    LSM6DSV16XStatusTypeDef Get_6D_Orientation_XL(uint8_t *XLow);
    LSM6DSV16XStatusTypeDef Get_6D_Orientation_XH(uint8_t *XHigh);
    LSM6DSV16XStatusTypeDef Get_6D_Orientation_YL(uint8_t *YLow);
    LSM6DSV16XStatusTypeDef Get_6D_Orientation_YH(uint8_t *YHigh);
    LSM6DSV16XStatusTypeDef Get_6D_Orientation_ZL(uint8_t *ZLow);
    LSM6DSV16XStatusTypeDef Get_6D_Orientation_ZH(uint8_t *ZHigh);

    LSM6DSV16XStatusTypeDef Enable_Free_Fall_Detection(LSM6DSV16X_SensorIntPin_t IntPin);
    LSM6DSV16XStatusTypeDef Disable_Free_Fall_Detection();
    LSM6DSV16XStatusTypeDef Set_Free_Fall_Threshold(uint8_t Threshold);
    LSM6DSV16XStatusTypeDef Set_Free_Fall_Duration(uint8_t Duration);

    LSM6DSV16XStatusTypeDef Enable_Wake_Up_Detection(LSM6DSV16X_SensorIntPin_t IntPin);
    LSM6DSV16XStatusTypeDef Disable_Wake_Up_Detection();
    LSM6DSV16XStatusTypeDef Set_Wake_Up_Threshold(uint32_t Threshold);
    LSM6DSV16XStatusTypeDef Set_Wake_Up_Duration(uint8_t Duration);

    LSM6DSV16XStatusTypeDef Enable_Single_Tap_Detection(LSM6DSV16X_SensorIntPin_t IntPin);
    LSM6DSV16XStatusTypeDef Disable_Single_Tap_Detection();
    LSM6DSV16XStatusTypeDef Enable_Double_Tap_Detection(LSM6DSV16X_SensorIntPin_t IntPin);
    LSM6DSV16XStatusTypeDef Disable_Double_Tap_Detection();
    LSM6DSV16XStatusTypeDef Set_Tap_Threshold(uint8_t Threshold);
    LSM6DSV16XStatusTypeDef Set_Tap_Shock_Time(uint8_t Time);
    LSM6DSV16XStatusTypeDef Set_Tap_Quiet_Time(uint8_t Time);
    LSM6DSV16XStatusTypeDef Set_Tap_Duration_Time(uint8_t Time);

    LSM6DSV16XStatusTypeDef Enable_Pedometer(LSM6DSV16X_SensorIntPin_t IntPin);
    LSM6DSV16XStatusTypeDef Disable_Pedometer();
    LSM6DSV16XStatusTypeDef Get_Step_Count(uint16_t *StepCount);
    LSM6DSV16XStatusTypeDef Step_Counter_Reset();

    LSM6DSV16XStatusTypeDef Enable_Tilt_Detection(LSM6DSV16X_SensorIntPin_t IntPin);
    LSM6DSV16XStatusTypeDef Disable_Tilt_Detection();

    LSM6DSV16XStatusTypeDef FIFO_Get_Num_Samples(uint16_t *NumSamples);
    LSM6DSV16XStatusTypeDef FIFO_Get_Full_Status(uint8_t *Status);
    LSM6DSV16XStatusTypeDef FIFO_Set_INT1_FIFO_Full(uint8_t Status);
    LSM6DSV16XStatusTypeDef FIFO_Set_INT2_FIFO_Full(uint8_t Status);
    LSM6DSV16XStatusTypeDef FIFO_Set_Watermark_Level(uint8_t Watermark);
    LSM6DSV16XStatusTypeDef FIFO_Set_Stop_On_Fth(uint8_t Status);
    LSM6DSV16XStatusTypeDef FIFO_Set_Mode(uint8_t Mode);
    LSM6DSV16XStatusTypeDef FIFO_Get_Tag(uint8_t *Tag);
    LSM6DSV16XStatusTypeDef FIFO_Get_Data(uint8_t *Data);
    LSM6DSV16XStatusTypeDef FIFO_Get_X_Axes(int32_t *Acceleration);
    LSM6DSV16XStatusTypeDef FIFO_Set_X_BDR(float Bdr);
    LSM6DSV16XStatusTypeDef FIFO_Get_G_Axes(int32_t *AngularVelocity);
    LSM6DSV16XStatusTypeDef FIFO_Set_G_BDR(float Bdr);

    LSM6DSV16XStatusTypeDef QVAR_Enable();
    LSM6DSV16XStatusTypeDef QVAR_Disable();
    LSM6DSV16XStatusTypeDef QVAR_GetStatus(uint8_t *val);
    LSM6DSV16XStatusTypeDef QVAR_GetImpedance(uint16_t *val);
    LSM6DSV16XStatusTypeDef QVAR_SetImpedance(uint16_t val);
    LSM6DSV16XStatusTypeDef QVAR_GetData(float *Data);

    LSM6DSV16XStatusTypeDef Get_MLC_Status(lsm6dsv16x_mlc_status_mainpage_t *status);
    LSM6DSV16XStatusTypeDef Get_MLC_Output(lsm6dsv16x_mlc_out_t *output);

    LSM6DSV16XStatusTypeDef Enable_Rotation_Vector();
    LSM6DSV16XStatusTypeDef Disable_Rotation_Vector();
    LSM6DSV16XStatusTypeDef Enable_Gravity_Vector();
    LSM6DSV16XStatusTypeDef Disable_Gravity_Vector();
    LSM6DSV16XStatusTypeDef Enable_Gyroscope_Bias();
    LSM6DSV16XStatusTypeDef Disable_Gyroscope_Bias();
    LSM6DSV16XStatusTypeDef FIFO_Get_Rotation_Vector(float *rvec);
    LSM6DSV16XStatusTypeDef FIFO_Get_Gravity_Vector(float *gvec);
    LSM6DSV16XStatusTypeDef FIFO_Get_Gyroscope_Bias(float *gbias);
    LSM6DSV16XStatusTypeDef Reset_SFLP();

    LSM6DSV16XStatusTypeDef Read_Reg(uint8_t Reg, uint8_t *Data);
    LSM6DSV16XStatusTypeDef Write_Reg(uint8_t Reg, uint8_t Data);

    /**
     * @brief Utility function to read data.
     * @param  pBuffer: pointer to data to be read.
     * @param  RegisterAddr: specifies internal address register to be read.
     * @param  NumByteToRead: number of bytes to be read.
     * @retval 0 if ok, an error code otherwise.
     */
    uint8_t IO_Read(uint8_t *pBuffer, uint8_t RegisterAddr, uint16_t NumByteToRead)
    {
      if (dev_spi) {
        dev_spi->beginTransaction(SPISettings(spi_speed, MSBFIRST, SPI_MODE3));

        digitalWrite(cs_pin, LOW);

        /* Write Reg Address */
        dev_spi->transfer(RegisterAddr | 0x80);
        /* Read the data */
        for (uint16_t i = 0; i < NumByteToRead; i++) {
          *(pBuffer + i) = dev_spi->transfer(0x00);
        }

        digitalWrite(cs_pin, HIGH);

        dev_spi->endTransaction();

        return 0;
      }

      if (dev_i2c) {
        dev_i2c->beginTransmission(((uint8_t)(((address) >> 1) & 0x7F)));
        dev_i2c->write(RegisterAddr);
        dev_i2c->endTransmission(false);

        dev_i2c->requestFrom(((uint8_t)(((address) >> 1) & 0x7F)), (uint8_t) NumByteToRead);

        int i = 0;
        while (dev_i2c->available()) {
          pBuffer[i] = dev_i2c->read();
          i++;
        }

        return 0;
      }

      return 1;
    }

    /**
     * @brief Utility function to write data.
     * @param  pBuffer: pointer to data to be written.
     * @param  RegisterAddr: specifies internal address register to be written.
     * @param  NumByteToWrite: number of bytes to write.
     * @retval 0 if ok, an error code otherwise.
     */
    uint8_t IO_Write(uint8_t *pBuffer, uint8_t RegisterAddr, uint16_t NumByteToWrite)
    {
      if (dev_spi) {
        dev_spi->beginTransaction(SPISettings(spi_speed, MSBFIRST, SPI_MODE3));

        digitalWrite(cs_pin, LOW);

        /* Write Reg Address */
        dev_spi->transfer(RegisterAddr);
        /* Write the data */
        for (uint16_t i = 0; i < NumByteToWrite; i++) {
          dev_spi->transfer(pBuffer[i]);
        }

        digitalWrite(cs_pin, HIGH);

        dev_spi->endTransaction();

        return 0;
      }

      if (dev_i2c) {
        dev_i2c->beginTransmission(((uint8_t)(((address) >> 1) & 0x7F)));

        dev_i2c->write(RegisterAddr);
        for (uint16_t i = 0 ; i < NumByteToWrite ; i++) {
          dev_i2c->write(pBuffer[i]);
        }

        dev_i2c->endTransmission(true);

        return 0;
      }

      return 1;
    }

  private:
    LSM6DSV16XStatusTypeDef Set_X_ODR_When_Enabled(float Odr);
    LSM6DSV16XStatusTypeDef Set_X_ODR_When_Disabled(float Odr);
    LSM6DSV16XStatusTypeDef Set_G_ODR_When_Enabled(float Odr);
    LSM6DSV16XStatusTypeDef Set_G_ODR_When_Disabled(float Odr);
    LSM6DSV16XStatusTypeDef npy_halfbits_to_floatbits(uint16_t h, uint32_t *f);
    LSM6DSV16XStatusTypeDef npy_half_to_float(uint16_t h, float *f);
    LSM6DSV16XStatusTypeDef sflp2q(float quat[4], uint16_t sflp[3]);

    /* Helper classes. */
    TwoWire *dev_i2c;
    SPIClass *dev_spi;

    /* Configuration */
    uint8_t address;
    int cs_pin;
    uint32_t spi_speed;

    lsm6dsv16x_data_rate_t acc_odr;
    lsm6dsv16x_data_rate_t gyro_odr;
    uint8_t acc_is_enabled;
    uint8_t gyro_is_enabled;
    uint8_t initialized;
    lsm6dsv16x_ctx_t reg_ctx;
};

#ifdef __cplusplus
extern "C" {
#endif
int32_t LSM6DSV16X_io_write(void *handle, uint8_t WriteAddr, uint8_t *pBuffer, uint16_t nBytesToWrite);
int32_t LSM6DSV16X_io_read(void *handle, uint8_t ReadAddr, uint8_t *pBuffer, uint16_t nBytesToRead);
#ifdef __cplusplus
}
#endif

#endif /* __LSM6DSV16XSensor_H__ */
