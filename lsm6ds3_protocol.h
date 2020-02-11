/*
 * lsm6ds3_protocol.h
 *
 *  Created on: 18 Jan 2019
 *      Author: stefan jaritz
 */

#ifndef DRV_LSM6DS3_PROTOCOL_H_
#define DRV_LSM6DS3_PROTOCOL_H_


/* Comms Stuff */
#define LSM6DS3_SPI_READ		(1 << 7)
#define LSM6DS3_SPI_WRITE               0x00
//#define LSM6DS3_SINGLE              0x00
//#define LSM6DS3_MULTI               0x40
#define LSM6DS3_SPI_ADDR_MASK           0x3F

/*
 * Registers
 */
/* Enable embedded functions register (r/w). */
#define LSM6DS3_FUNC_CFG_ACCESS      0x01
// Bits & Masks
#define LSM6DS3_FUNC_CFG_EN        0b10000000  // Enable access to the embedded functions configuration registers (1) from address
                        //   02h to 32h. Default value: 0.
                        //  (0: disable access to embedded functions configuration registers;
                        //   1: enable access to embedded functions configuration registers)
                        //   1. The embedded functions configuration registers details are available in 10: Embedded functions register
                        //      mapping and 11: Embedded functions registers description.

/* Sensor syncronization time frame register (r/w). */
#define LSM6DS3_SENSOR_SYNC_TIME_FRAME  0x04

/* FIFO control register (r/w). */
#define LSM6DS3_FIFO_CTRL1        0x06

/* FIFO control register (r/w). */
#define LSM6DS3_FIFO_CTRL2        0x07
// Bits & Masks
#define LSM6DS3_TIMER_PEDO_FIFO_EN    0b10000000  // Enable pedometer step counter and time stamp as 4th FIFO data set. Default: 0
                        //  (0: disable step counter and time stamp data as 4th FIFO data set;
                        //   1: enable step counter and time stamp data as 4th FIFO data set)
#define LSM6DS3_TIMER_PEDO_FIFO_DRDY  0b01000000  // FIFO write mode(1). Default: 0
                        //  (0: enable write in FIFO based on XL/Gyro data-ready;
                        //   1: enable write in FIFO at every step detected by step counter.)
#define LSM6DS3_FTH_11_8        0b00001111  // FIFO threshold level setting(2). Default value: 0000
                        //   Watermark flag rises when the number of bytes written to FIFO after the next
                        //   write is greater than or equal to the threshold level.
                        //   Minimum resolution for the FIFO is 1LSB = 2 bytes (1 word) in FIFO
/* FIFO control register (r/w). */
#define LSM6DS3_FIFO_CTRL3        0x08
// Bits & Masks
#define LSM6DS3_DEC_FIFO_GYRO      0b00111000  // Gyro FIFO (first data set) decimation setting. Default: 000
                        //   For the configuration setting, refer to Table 27.
#define LSM6DS3_DEC_FIFO_GYRO_NOT_IN  0b00000000  // Gyro sensor not in FIFO
#define LSM6DS3_DEC_FIFO_GYRO_X0    0b00001000  // No decimation
#define LSM6DS3_DEC_FIFO_GYRO_X2    0b00010000  // Decimation with factor 2
#define LSM6DS3_DEC_FIFO_GYRO_X4    0b00011000  // Decimation with factor 4
#define LSM6DS3_DEC_FIFO_GYRO_X8    0b00101000  // Decimation with factor 8
#define LSM6DS3_DEC_FIFO_GYRO_X16    0b00110000  // Decimation with factor 16
#define LSM6DS3_DEC_FIFO_GYRO_X32    0b00111000  // Decimation with factor 32

#define LSM6DS3_DEC_FIFO_XL       0b00000111  // Accelerometer FIFO (second data set) decimation setting. Default: 000
                        //   For the configuration setting, refer to Table 28.
#define LSM6DS3_DEC_FIFO_XL_NOT_IN    0b00000000  // Accelerometer sensor not in FIFO
#define LSM6DS3_DEC_FIFO_XL_X0      0b00000001  // No decimation
#define LSM6DS3_DEC_FIFO_XL_X2      0b00000010  // Decimation with factor 2
#define LSM6DS3_DEC_FIFO_XL_X4      0b00000011  // Decimation with factor 4
#define LSM6DS3_DEC_FIFO_XL_X8      0b00000101  // Decimation with factor 8
#define LSM6DS3_DEC_FIFO_XL_X16      0b00000110  // Decimation with factor 16
#define LSM6DS3_DEC_FIFO_XL_X32      0b00000111  // Decimation with factor 32

/* FIFO control register (r/w). */
#define LSM6DS3_FIFO_CTRL4        0x09
// Bits & Masks
#define LSM6DS3_ONLY_HIGH_DATA      0b01000000  // 8-bit data storage in FIFO. Default: 0
                        //  (0: disable MSByte only memorization in FIFO for XL and Gyro;
                        //   1: enable MSByte only memorization in FIFO for XL and Gyro in FIFO)
#define LSM6DS3_DEC_DS4_FIFO      0b00111000  // Fourth FIFO data set decimation setting. Default: 000
                        //   For the configuration setting, refer to Table 31.
#define LSM6DS3_DEC_DS4_FIFO_NOT_IN    0b00000000  // Fourth FIFO data set not in FIFO
#define LSM6DS3_DEC_DS4_FIFO_X0      0b00001000  // No decimation
#define LSM6DS3_DEC_DS4_FIFO_X2      0b00010000  // Decimation with factor 2
#define LSM6DS3_DEC_DS4_FIFO_X4      0b00011000  // Decimation with factor 4
#define LSM6DS3_DEC_DS4_FIFO_X8      0b00101000  // Decimation with factor 8
#define LSM6DS3_DEC_DS4_FIFO_X16    0b00110000  // Decimation with factor 16
#define LSM6DS3_DEC_DS4_FIFO_X32    0b00111000  // Decimation with factor 32

#define LSM6DS3_DEC_DS3_FIFO       0b00000111  // Third FIFO data set decimation setting. Default: 000
                        //   For the configuration setting, refer to Table 32.
#define LSM6DS3_DEC_DS3_FIFO_NOT_IN    0b00000000  // Third FIFO data set not in FIFO
#define LSM6DS3_DEC_DS3_FIFO_X0      0b00000001  // No decimation
#define LSM6DS3_DEC_DS3_FIFO_X2      0b00000010  // Decimation with factor 2
#define LSM6DS3_DEC_DS3_FIFO_X4      0b00000011  // Decimation with factor 4
#define LSM6DS3_DEC_DS3_FIFO_X8      0b00000101  // Decimation with factor 8
#define LSM6DS3_DEC_DS3_FIFO_X16    0b00000110  // Decimation with factor 16
#define LSM6DS3_DEC_DS3_FIFO_X32    0b00000111  // Decimation with factor 32

/* FIFO control register (r/w). */
#define LSM6DS3_FIFO_CTRL5        0x0A
// Bits & Masks
#define LSM6DS3_ODR_FIFO        0b01111000  // FIFO ODR selection, setting FIFO_MODE also. Default: 0000
                        //   For the configuration setting, refer to Table 35
#define LSM6DS3_ODR_FIFO_DISABLED    0b00000000   // FIFO disabled
#define LSM6DS3_ODR_FIFO_13HZ      0b00001000  // FIFO ODR is set to 13 Hz
#define LSM6DS3_ODR_FIFO_26HZ      0b00010000  // FIFO ODR is set to 26 Hz
#define LSM6DS3_ODR_FIFO_52HZ      0b00011000  // FIFO ODR is set to 52 Hz
#define LSM6DS3_ODR_FIFO_104HZ      0b00100000  // FIFO ODR is set to 104 Hz
#define LSM6DS3_ODR_FIFO_208HZ      0b00101000  // FIFO ODR is set to 208 Hz
#define LSM6DS3_ODR_FIFO_416HZ      0b00110000  // FIFO ODR is set to 416 Hz
#define LSM6DS3_ODR_FIFO_833HZ      0b00111000  // FIFO ODR is set to 833 Hz
#define LSM6DS3_ODR_FIFO_1660HZ      0b01000000  // FIFO ODR is set to 1.66 kHz
#define LSM6DS3_ODR_FIFO_3330HZ      0b01001000  // FIFO ODR is set to 3.33 kHz
#define LSM6DS3_ODR_FIFO_6660HZ      0b01010000  // FIFO ODR is set to 6.66 kHz

#define LSM6DS3_FIFO_MODE        0b00000111  // FIFO mode selection bits, setting ODR_FIFO also. Default value: 000
                        //   For the configuration setting refer to Table 36
#define LSM6DS3_FIFO_MODE_BYPASS    0b00000000  // Bypass mode. FIFO disabled.
#define LSM6DS3_FIFO_MODE_FIFO      0b00000001  // FIFO mode. Stops collecting data when FIFO is full.
#define LSM6DS3_FIFO_MODE_CONT_TRIG    0b00000011  // Continuous mode until trigger is deasserted, then FIFO mode.
#define LSM6DS3_FIFO_MODE_BYPASS_TRIG  0b00000100  // Bypass mode until trigger is deasserted, then Continuous mode.
#define LSM6DS3_FIFO_MODE_CONT      0b00000110  // Continuous mode. If the FIFO is full, the new sample overwrites the older one.

/* Angular rate sensor sign and orientation register (r/w). */
#define LSM6DS3_ORIENT_CFG_G      0x0B
// Bits & Masks
#define LSM6DS3_SIGNX_G          0b00100000  // Pitch axis (X) angular rate sign. Default value: 0
                        //  (0: positive sign; 1: negative sign)
#define LSM6DS3_SIGNY_G          0b00010000  // Pitch axis (Y) angular rate sign. Default value: 0
                        //  (0: positive sign; 1: negative sign)
#define LSM6DS3_SIGNZ_G          0b00001000  // Pitch axis (Z) angular rate sign. Default value: 0
                        //  (0: positive sign; 1: negative sign)
#define LSM6DS3_ORIENT           0b00000111  // Directional user-orientation selection. Default value: 000
                        //   For the configuration setting, refer to Table 39.
#define LSM6DS3_ORIENT_PX_RY_YZ     0b00000000  // Pitch = X; Roll = Y; Yaw = Z.
#define LSM6DS3_ORIENT_PX_RZ_YY     0b00000001  // Pitch = X; Roll = Z; Yaw = Y.
#define LSM6DS3_ORIENT_PY_RX_YZ     0b00000010  // Pitch = Y; Roll = X; Yaw = Z.
#define LSM6DS3_ORIENT_PY_RZ_YX     0b00000011  // Pitch = Y; Roll = Z; Yaw = X.
#define LSM6DS3_ORIENT_PZ_RX_YY     0b00000100  // Pitch = Z; Roll = X; Yaw = Y.
#define LSM6DS3_ORIENT_PZ_RY_YX     0b00000101  // Pitch = Z; Roll = Y; Yaw = X.

/* INT1 pad control register (r/w). */
/* Each bit in this register enables a signal to be carried through INT1. The pad?s output will
 * supply the OR combination of the selected signals. */
#define LSM6DS3_INT1_CTRL        0x0D
// Bits & Masks
#define LSM6DS3_INT1_STEP_DETECTOR    0b10000000  // Pedometer step recognition interrupt enable on INT1 pad. Default value: 0
                        //  (0: disabled; 1: enabled)
#define LSM6DS3_INT1_SIGN_MOT      0b01000000  // Significant motion interrupt enable on INT1 pad. Default value: 0
                        //  (0: disabled; 1: enabled)
#define LSM6DS3_INT1_FULL_FLAG      0b00100000  // FIFO full flag interrupt enable on INT1 pad. Default value: 0
                        //  (0: disabled; 1: enabled)
#define LSM6DS3_INT1_FIFO_OVR      0b00010000  // FIFO overrun interrupt on INT1 pad. Default value: 0
                        //  (0: disabled; 1: enabled)
#define LSM6DS3_INT1_FTH        0b00001000  // FIFO threshold interrupt on INT1 pad. Default value: 0
                        //  (0: disabled; 1: enabled)
#define LSM6DS3_INT1_BOOT        0b00000100  // Boot status available on INT1 pad. Default value: 0
                        //  (0: disabled; 1: enabled)
#define LSM6DS3_INT1_DRDY_G        0b00000010  // Gyroscope Data Ready on INT1 pad. Default value: 0
                        //  (0: disabled; 1: enabled)
#define LSM6DS3_INT1_DRDY_XL      0b00000001  // Accelerometer Data Ready on INT1 pad. Default value: 0
                        //  (0: disabled; 1: enabled)

/* INT2 pad control register (r/w). */
/* Each bit in this register enables a signal to be carried through INT2. The pad?s output will
supply the OR combination of the selected signals. */
#define LSM6DS3_INT2_CTRL        0x0E
// Bits & Masks
#define LSM6DS3_INT2_STEP_DELTA      0b10000000  // Pedometer step recognition interrupt on delta time(1) enable on INT2 pad.
                        //   Default value: 0
                        //  (0: disabled; 1: enabled)
                        //   1. Delta time value is defined in register STEP_COUNT_DELTA (15h).
#define LSM6DS3_INT2_STEP_COUNT_OV    0b01000000  // Step counter overflow interrupt enable on INT2 pad. Default value: 0
                        //  (0: disabled; 1: enabled)
#define LSM6DS3_INT2_FULL_FLAG      0b00100000  // FIFO full flag interrupt enable on INT2 pad. Default value: 0
                        //  (0: disabled; 1: enabled)
#define LSM6DS3_INT2_FIFO_OVR      0b00010000  // FIFO overrun interrupt on INT2 pad. Default value: 0
                        //  (0: disabled; 1: enabled)
#define LSM6DS3_INT2_FTH        0b00001000  // FIFO threshold interrupt on INT2 pad. Default value: 0
                        //  (0: disabled; 1: enabled)
#define LSM6DS3_INT2_DRDY_TEMP      0b00000100  // Temperature Data Ready in INT2 pad. Default value: 0
                        //  (0: disabled; 1: enabled)
#define LSM6DS3_INT2_DRDY_G        0b00000010  // Gyroscope Data Ready on INT2 pad. Default value: 0
                        //  (0: disabled; 1: enabled)
#define LSM6DS3_INT2_DRDY_XL      0b00000001  // Accelerometer Data Ready on INT2 pad. Default value: 0
                        //  (0: disabled; 1: enabled)

/* Who_AM_I register (r). This register is a read-only register. Its value is fixed at 69h. */
#define LSM6DS3_WHO_AM_I        0x0F
// Bits & Masks
#define LSM6DS3_WHO_AM_I_RETURN      0x69    // Return value for this register

/* Linear acceleration sensor control register 1 (r/w). */
#define LSM6DS3_CTRL1_XL        0x10
// Bits & Masks
#define LSM6DS3_ODR_XL          0b11110000  // Output data rate and power mode selection. Default value: 0000 (see Table 47).
#define LSM6DS3_ODR_XL_POWER_DOWN    0b00000000  // Power Down
#define LSM6DS3_ODR_XL_13HZ        0b00010000  // 13 Hz
#define LSM6DS3_ODR_XL_26HZ        0b00100000  // 26 Hz
#define LSM6DS3_ODR_XL_52HZ        0b00110000  // 52 Hz
#define LSM6DS3_ODR_XL_104HZ      0b01000000  // 104 Hz
#define LSM6DS3_ODR_XL_208HZ      0b01010000  // 208 Hz
#define LSM6DS3_ODR_XL_416HZ      0b01100000  // 416 Hz
#define LSM6DS3_ODR_XL_833HZ      0b01110000  // 833 kHz
#define LSM6DS3_ODR_XL_1660HZ      0b10000000  // 1.66 kHz
#define LSM6DS3_ODR_XL_3330HZ      0b10010000  // 3.33 kHz
#define LSM6DS3_ODR_XL_6660HZ      0b10100000  // 6.66 kHz
#define LSM6DS3_FS_XL          0b00001100  // Accelerometer full-scale selection. Default value: 00.
                        //  (00: �2 g; 01: �16 g; 10: �4 g; 11: �8 g)
#define LSM6DS3_FS_XL_2G        0b00000000  // �2g
#define LSM6DS3_FS_XL_16G        0b00000100  // �16g
#define LSM6DS3_FS_XL_4G        0b00001000  // �4g
#define LSM6DS3_FS_XL_8G        0b00001100  // �8g
#define LSM6DS3_BW_XL          0b00000011  // Anti-aliasing filter bandwidth selection. Default value: 00
                        //  (00: 400 Hz; 01: 200 Hz; 10: 100 Hz; 11: 50 Hz)
#define LSM6DS3_BW_XL_400HZ        0b00000000  // 400Hz
#define LSM6DS3_BW_XL_200HZ        0b00000001  // 200Hz
#define LSM6DS3_BW_XL_100HZ        0b00000010  // 100Hz
#define LSM6DS3_BW_XL_50HZ        0b00000011  // 50Hz

/* Angular rate sensor control register 2 (r/w). */
#define LSM6DS3_CTRL2_G          0x11
// Bits & Masks
#define LSM6DS3_ODR_G          0b11110000  // Gyroscope output data rate selection. Default value: 0000
                        //  (Refer toTable 49)
#define LSM6DS3_ODR_G_POWER_DOWN    0b00000000  // Power Down
#define LSM6DS3_ODR_G_13HZ        0b00010000  // 13 Hz
#define LSM6DS3_ODR_G_26HZ        0b00100000  // 26 Hz
#define LSM6DS3_ODR_G_52HZ        0b00110000  // 52 Hz
#define LSM6DS3_ODR_G_104HZ        0b01000000  // 104 Hz
#define LSM6DS3_ODR_G_208HZ        0b01010000  // 208 Hz
#define LSM6DS3_ODR_G_416HZ        0b01100000  // 416 Hz
#define LSM6DS3_ODR_G_833HZ        0b01110000  // 833 kHz
#define LSM6DS3_ODR_G_1660HZ      0b10000000  // 1.66 kHz
#define LSM6DS3_FS_G           0b00001100  // Gyroscope full-scale selection. Default value: 00
                        //  (00: 245 dps; 01: 500 dps; 10: 1000 dps; 11: 2000 dps)
#define LSM6DS3_FS_G_245DPS        0b00000000  // 245 dps
#define LSM6DS3_FS_G_500DPS        0b00000100  // 500 dps
#define LSM6DS3_FS_G_1000DPS      0b00001000  // 1000 dps
#define LSM6DS3_FS_G_2000DPS      0b00001100  // 2000 dps
#define LSM6DS3_FS_125          0b00000010  // Gyroscope full-scale at 125 dps. Default value: 0
                        //  (0: disabled; 1: enabled)

/* Control register 3 (r/w). */
#define LSM6DS3_CTRL3_C          0x12
// Bits & Masks
#define LSM6DS3_BOOT           0b10000000  // Reboot memory content. Default value: 0
                        //  (0: normal mode; 1: reboot memory content(1))
                        //   1. Boot request is executed as soon as internal oscillator is turned on. It is possible to set bit while in powerdown
                        //      mode, in this case it will be served at the next normal mode or sleep mode.
#define LSM6DS3_BDU           0b01000000  // Block Data Update. Default value: 0
                        //  (0: continuous update; 1: output registers not updated until MSB and LSB have
                        //   been read)
#define LSM6DS3_H_LACTIVE         0b00100000  // Interrupt activation level. Default value: 0
                        //  (0: interrupt output pads active high; 1: interrupt output pads active low)
#define LSM6DS3_PP_OD           0b00010000  // Push-pull/open-drain selection on INT1 and INT2 pads. Default value: 0
                        //  (0: push-pull mode; 1: open-drain mode)
#define LSM6DS3_SIM           0b00001000  // SPI Serial Interface Mode selection. Default value: 0
                        //  (0: 4-wire interface; 1: 3-wire interface).
#define LSM6DS3_IF_INC           0b00000100  // Register address automatically incremented during a multiple byte access with a
                        //   serial interface (I2C or SPI). Default value: 1
                        //  (0: disabled; 1: enabled)
#define LSM6DS3_BLE           0b00000010  // Big/Little Endian Data selection. Default value 0
                        //  (0: data LSB @ lower address; 1: data MSB @ lower address)
#define LSM6DS3_SW_RESET         0b00000001  //   Software reset. Default value: 0
                        //  (0: normal mode; 1: reset device)
                        //   This bit is cleared by hardware after next flash boot.

/* Control register 4 (r/w). */
#define LSM6DS3_CTRL4_C          0x13
#define LSM6DS3_XL_BW_SCAL_ODR      0b10000000  // Accelerometer bandwidth selection. Default value: 0
                        //  (0(1): bandwidth determined by ODR selection, refer to Table 48;
                        //   1(2): bandwidth determined by setting BW_XL[1:0] in CTRL1_XL (10h) register.)
                        //   1. Filter used in high-performance mode only with ODR less than 3.33 kHz.
                        //   2. Filter used in high-performance mode only.
#define LSM6DS3_SLEEP_G         0b01000000  // Gyroscope sleep mode enable. Default value: 0
                        //  (0: disabled; 1: enabled)
#define LSM6DS3_INT2_ON_INT1       0b00100000  // All interrupt signals available on INT1 pad enable. Default value: 0
                        //  (0: interrupt signals divided between INT1 and INT2 pads;
                        //   1: all interrupt signals in logic or on INT1 pad)
#define LSM6DS3_FIFO_TEMP_EN       0b00010000  // Enable temperature data as 4th FIFO data set(3). Default: 0
                        //  (0: disable temperature data as 4th FIFO data set;
                        //   1: enable temperature data as 4th FIFO data set)
                        //   3. This bit is effective if the TIMER_PEDO_FIFO_EN bit of FIFO_CTRL2 register is set to 0.
#define LSM6DS3_DRDY_MASK         0b00001000  // Configuration 1(4) data available enable bit. Default value: 0
                        //  (0: DA timer disabled; 1: DA timer enabled)
                        //   4. In configuration 1, switching to combo mode, data are collected in FIFO only when both accelerometer and
                        //      gyroscope are set. Switching to accelerometer only, data are collected in FIFO after filter setting.
#define LSM6DS3_I2C_DISABLE       0b00000100  // Disable I2C interface. Default value: 0
                        //  (0: both I2C and SPI enabled; 1: I2C disabled, SPI only)
#define LSM6DS3_MODE3_EN         0b00000010  // Enable auxiliary SPI interface (Mode 3, refer to Table 2). Default value: 0
                        //  (0: auxiliary SPI disabled; 1: auxiliary SPI enabled(5))
                        //   5. Conditioned pads are: SDx, SCx, OCS
#define LSM6DS3_STOP_ON_FTH       0b00000001  // Enable FIFO threshold level use. Default value: 0.
                        //  (0: FIFO depth is not limited; 1: FIFO depth is limited to threshold level)

/* Control register 5 (r/w). */
#define LSM6DS3_CTRL5_C          0x14
// Bits & Masks
#define LSM6DS3_ROUNDING        0b11100000  // Circular burst-mode (rounding) read from output registers. Default: 000
                        //  (000: no rounding; Others: refer to Table 58)
#define LSM6DS3_ROUNDING_NONE      0b00000000  // No rounding
#define LSM6DS3_ROUNDING_XL        0b00100000  // Accelerometer only
#define LSM6DS3_ROUNDING_G        0b01000000  // Gyroscope only
#define LSM6DS3_ROUNDING_G_XL      0b01100000  // Gyroscope + accelerometer
#define LSM6DS3_ROUNDING_SHL      0b10000000  // Registers from SENSORHUB1_REG (2Eh) to SENSORHUB6_REG (33h) only
#define LSM6DS3_ROUNDING_XL_SHL      0b10100000  // Accelerometer + registers from SENSORHUB1_REG (2Eh) to
                        //   SENSORHUB6_REG (33h)
#define LSM6DS3_ROUNDING_G_XL_SH    0b11000000  // Gyroscope + accelerometer + registers from SENSORHUB1_REG (2Eh) to
                        //   SENSORHUB6_REG (33h) and registers from SENSORHUB7_REG (34h) to
                        //   SENSORHUB12_REG(39h)
#define LSM6DS3_ROUNDING_G_XL_SHL    0b11100000  // Gyroscope + accelerometer + registers from SENSORHUB1_REG (2Eh) to
                        //   SENSORHUB6_REG (33h)
#define LSM6DS3_ST_G           0b00001100  // Angular rate sensor self-test enable. Default value: 00
                        //  (00: Self-test disabled; Other: refer to Table 59)
#define LSM6DS3_ST_G_NORMAL        0b00000000  // Normal mode
#define LSM6DS3_ST_G_POSITIVE      0b00000100  // Positive sign self-test
#define LSM6DS3_ST_G_NEGATIVE      0b00001100  // Negative sign self-test
#define LSM6DS3_ST_XL           0b00000011  // Linear acceleration sensor self-test enable. Default value: 00
                        //  (00: Self-test disabled; Other: refer to Table 60)
#define LSM6DS3_ST_XL_NORMAL      0b00000000  // Normal mode
#define LSM6DS3_ST_XL_POSITIVE      0b00000001  // Positive sign self-test
#define LSM6DS3_ST_XL_NEGATIVE      0b00000010  // Negative sign self-

/* Angular rate sensor control register 6 (r/w). */
#define LSM6DS3_CTRL6_C          0x15
// Bits & Masks
#define LSM6DS3_TRIG_EN          0b10000000  // Gyroscope data edge-sensitive trigger enable. Default value: 0
                        //  (0: external trigger disabled; 1: external trigger enabled)
#define LSM6DS3_LVLEN           0b01000000  // Gyroscope data level-sensitive trigger enable. Default value: 0
                        //  (0: level-sensitive trigger disabled; 1: level sensitive trigger enabled)
#define LSM6DS3_LVL2_EN          0b00100000  // Gyroscope level-sensitive latched enable. Default value: 0
                        //  (0: level-sensitive latched disabled; 1: level sensitive latched enabled)
#define LSM6DS3_XL_HM_MODE        0b00010000  // High-performance operating mode disable for accelerometer(1). Default value: 0
                        //  (0: high-performance operating mode enabled;
                        //   1: high-performance operating mode disabled)
                        //   1. Normal and low-power mode depends on the ODR setting, for details refer to Table 47.

/* Angular rate sensor control register 7 (r/w). */
#define LSM6DS3_CTRL7_G          0x16
// Bits & Masks
#define LSM6DS3_G_HM_MODE        0b10000000  // High-performance operating mode disable for gyroscope(1). Default: 0
                        //  (0: high-performance operating mode enabled;
                        //   1: high-performance operating mode disabled)
                        //   1. Normal and low-power mode depends on the ODR setting, for details refer to Table 51.
#define LSM6DS3_HP_G_EN          0b01000000  // Gyroscope high-pass filter enable. Default value: 0
                        //  (0: HPF disabled; 1: HPF enabled)
#define LSM6DS3_HP_G_RST        0b00100000  // Gyro digital HP filter reset. Default: 0
                        //  (0: gyro digital HP filter reset OFF; 1: gyro digital HP filter reset ON)
#define LSM6DS3_ROUNDING_STATUS      0b00010000  // Source register rounding function enable on STATUS_REG (1Eh), FUNC_SRC
                        //   (53h) and WAKE_UP_SRC (1Bh) registers. Default value: 0
                        //  (0: disabled; 1: enabled)
#define LSM6DS3_HPCF_G          0b00001100  // Gyroscope high-pass filter cutoff frequency selection. Default value: 00.
                        //   Refer to Table 65.
#define LSM6DS3_HPCF_G_8M1HZ       0b00000000  // 0.0081 Hz
#define LSM6DS3_HPCF_G_32M4HZ       0b00000100  // 0.0324 Hz
#define LSM6DS3_HPCF_G_2070MHZ       0b00001000  // 2.07 Hz
#define LSM6DS3_HPCF_G_16320MHZ     0b00001100  // 16.32 Hz

/* Linear acceleration sensor control register 8 (r/w). */
#define LSM6DS3_CTRL8_XL        0x17
// Bits & Masks
#define LSM6DS3_LPF2_XL_EN         0b10000000  // Accelerometer low-pass filter LPF2 selection. Refer to Figure 5.
#define LSM6DS3_HPCF_XL          0b01100000  // Accelerometer slope filter and high-pass filter configuration and cutoff
                        //   setting. Refer to Table 68. It is also used to select the cutoff frequency of the
                        //   LPF2 filter, as shown in Table 69. This low-pass filter can also be used in the
                        //   6D/4D functionality by setting the LOW_PASS_ON_6D bit of CTRL8_XL
                        //   (17h) to 1.
                        // Applied filter : HP filter cutoff frequency [Hz]
#define LSM6DS3_HPCF_XL_DIV4      0b00000000  // Slope          : ODR_XL/4
#define LSM6DS3_HPCF_XL_DIV100      0b00100000  // High-pass      : ODR_XL/100
#define LSM6DS3_HPCF_XL_DIV9      0b01000000  // High-pass      : ODR_XL/9
#define LSM6DS3_HPCF_XL_DIV400      0b01100000  // High-pass      : ODR_XL/400
#define LSM6DS3_HPCF_XL_DIV50      0b00000000  // LPF2           : ODR_XL/50
//#define LSM6DS3_HPCF_XL_DIV100    0b00100000  // LPF2           : ODR_XL/100
//#define LSM6DS3_HPCF_XL_DIV9      0b01000000  // LPF2           : ODR_XL/9
//#define LSM6DS3_HPCF_XL_DIV400    0b01100000  // LPF2           : ODR_XL/400
#define LSM6DS3_HP_SLOPE_XL_EN      0b00000100  // Accelerometer slope filter / high-pass filter selection. Refer to Figure 5.
#define LSM6DS3_LOW_PASS_ON_6D      0b00000001  // Low-pass filter on 6D function selection. Refer to Figure 5.

/* Linear acceleration sensor control register 9 (r/w). */
#define LSM6DS3_CTRL9_XL        0x18
// Bits & Masks
#define LSM6DS3_ZEN_XL          0b00100000  // Accelerometer Z-axis output enable. Default value: 1
                        //  (0: Z-axis output disabled; 1: Z-axis output enabled)
#define LSM6DS3_YEN_XL          0b00010000  // Accelerometer Y-axis output enable. Default value: 1
                        //  (0: Y-axis output disabled; 1: Y-axis output enabled)
#define LSM6DS3_XEN_XL          0b00001000  // Accelerometer X-axis output enable. Default value: 1
                        //  (0: X-axis output disabled; 1: X-axis output enabled)
#define LSM6DS3_SOFT_EN          0b00000100  // Enable soft-iron correction algorithm for magnetometer(1). Default value: 0
                        //  (0: soft-iron correction algorithm disabled;
                        //   1: soft-iron correction algorithm disabled)

/* Control register 10 (r/w). */
#define LSM6DS3_CTRL10_C        0x19
// Bits & Masks
#define LSM6DS3_ZEN_G          0b00100000  // Gyroscope yaw axis (Z) output enable. Default value: 1
                        //  (0: Z-axis output disabled; 1: Z-axis output enabled)
#define LSM6DS3_YEN_G          0b00010000  // Gyroscope roll axis (Y) output enable. Default value: 1
                        //  (0: Y-axis output disabled; 1: Y axis output enabled)
#define LSM6DS3_XEN_G          0b00001000  // Gyroscope pitch axis (X) output enable. Default value: 1
                        //  (0: X-axis output disabled; 1: X-axis output enabled)
#define LSM6DS3_FUNC_EN         0b00000100  // Enable embedded functionalities (pedometer, tilt, significant motion, sensor hub
                        //   and ironing) and accelerometer HP and LPF2 filters (refer to Figure 5). Default
                        //   value: 0
                        //  (0: disable functionalities of embedded functions and accelerometer filters;
                        //   1: enable functionalities of embedded functions and accelerometer filters)
#define LSM6DS3_PEDO_RST_STEP      0b00000010  // Reset pedometer step counter. Default value: 0
                        //  (0: disabled; 1: enabled)
#define LSM6DS3_SIGN_MOTION_EN      0b00000001  // Enable significant motion function. Default value: 0
                        //  (0: disabled; 1: enabled)

/* Master configuration register (r/w). */
#define LSM6DS3_MASTER_CONFIG      0x1A
// Bits & Masks
#define LSM6DS3_DRDY_ON_INT1      0b10000000  // Manage the Master DRDY signal on INT1 pad. Default: 0
                        //  (0: disable Master DRDY on INT1; 1: enable Master DRDY on INT1)
#define LSM6DS3_DATA_VALID_SEL_FIFO    0b01000000  // Selection of FIFO data-valid signal. Default value: 0
                        //  (0: data-valid signal used to write data in FIFO is the XL/Gyro data-ready or step
                        //   detection(1);
                        //   1: data-valid signal used to write data in FIFO is the sensor hub data-ready)
                        //   1. If the TIMER_PEDO_FIFO_DRDY bit in FIFO_CTRL2(07h) is set to 0, the trigger for writing data in FIFO is
                        //      XL/Gyro data-ready, otherwise it's the step detection.
#define LSM6DS3_START_CONFIG      0b00010000  // Sensor Hub trigger signal selection. Default value: 0
                        //  (0: Sensor hub signal is the XL/Gyro data-ready;
                        //   1: Sensor hub signal external from INT2 pad.)
#define LSM6DS3_PULL_UP_EN        0b00001000  // Auxiliary I2C pull-up. Default value: 0
                        //  (0: internal pull-up on auxiliary I2C line disabled;
                        //   1: internal pull-up on auxiliary I2C line enabled)
#define LSM6DS3_PASS_THROUGH_MODE    0b00000100  // I2C interface pass-through. Default value: 0
                        //  (0: through disabled; 1: through enabled)
#define LSM6DS3_IRON_EN          0b00000010  // Enable hard-iron correction algorithm for magnetometer. Default value: 0
                        //  (0:hard-iron correction algorithm disabled;
                        //   1: hard-iron correction algorithm enabled)
#define LSM6DS3_MASTER_ON         0b00000001  // Sensor hub I2C master enable. Default: 0
                        //  (0: master I2C of sensor hub disabled; 1: master I2C of sensor hub enabled)

/* Wake up interrupt source register (r). */
#define LSM6DS3_WAKE_UP_SRC        0x1B
// Bits & Masks
#define LSM6DS3_FF_IA           0b00100000  // Free-fall event detection status. Default: 0
                        //  (0: free-fall event not detected; 1: free-fall event detected)
#define LSM6DS3_SLEEP_STATE_IA      0b00010000  // Sleep event status. Default value: 0
                        //  (0: sleep event not detected; 1: sleep event detected)
#define LSM6DS3_WU_IA          0b00001000  // Wakeup event detection status. Default value: 0
                        //  (0: wakeup event not detected; 1: wakeup event detected.)
#define LSM6DS3_X_WU          0b00000100  // Wakeup event detection status on X-axis. Default value: 0
                        //  (0: wakeup event on X-axis not detected; 1: wakeup event on X-axis detected)
#define LSM6DS3_Y_WU          0b00000010  // Wakeup event detection status on Y-axis. Default value: 0
                        //  (0: wakeup event on Y-axis not detected; 1: wakeup event on Y-axis detected)
#define LSM6DS3_Z_WU          0b00000001  // Wakeup event detection status on Z-axis. Default value: 0
                        //  (0: wakeup event on Z-axis not detected; 1: wakeup event on Z-axis detected)

/* Tap source register (r). */
#define LSM6DS3_TAP_SRC          0x1C
// Bits & Masks
#define LSM6DS3_TAP_IA          0b01000000  // Tap event detection status. Default: 0
                        //  (0: tap event not detected; 1: tap event detected)
#define LSM6DS3_SINGLE_TAP        0b00100000  // Single-tap event status. Default value: 0
                        //  (0: single tap event not detected; 1: single tap event detected)
#define LSM6DS3_DOUBLE_TAP        0b00010000  // Double-tap event detection status. Default value: 0
                        //  (0: double-tap event not detected; 1: double-tap event detected.)
#define LSM6DS3_TAP_SIGN        0b00001000  // Sign of acceleration detected by tap event. Default: 0
                        //  (0: positive sign of acceleration detected by tap event;
                        //   1: negative sign of acceleration detected by tap event)
#define LSM6DS3_X_TAP          0b00000100  // Tap event detection status on X-axis. Default value: 0
                        //  (0: tap event on X-axis not detected; 1: tap event on X-axis detected)
#define LSM6DS3_Y_TAP          0b00000010  // Tap event detection status on Y-axis. Default value: 0
                        //  (0: tap event on Y-axis not detected; 1: tap event on Y-axis detected)
#define LSM6DS3_Z_TAP          0b00000001  // Tap event detection status on Z-axis. Default value: 0
                        //  (0: tap event on Z-axis not detected; 1: tap event on Z-axis detected)

/* Portrait, landscape, face-up and face-down source register (r) */
#define LSM6DS3_D6D_SRC          0x1D
// Bits & Masks
#define LSM6DS3_D6D_IA          0b01000000  // Interrupt active for change position portrait, landscape, face-up, face-down. Default value: 0
                        //  (0: change position not detected; 1: change position detected)
#define LSM6DS3_ZH             0b00100000  // Z-axis high event (over threshold). Default value: 0
                        //  (0: event not detected; 1: event (over threshold) detected)
#define LSM6DS3_ZL             0b00010000  // Z-axis low event (under threshold). Default value: 0
                        //  (0: event not detected; 1: event (under threshold) detected)
#define LSM6DS3_YH             0b00001000  // Y-axis high event (over threshold). Default value: 0
                        //  (0: event not detected; 1: event (over-threshold) detected)
#define LSM6DS3_YL             0b00000100  // Y-axis low event (under threshold). Default value: 0
                        //  (0: event not detected; 1: event (under threshold) detected)
#define LSM6DS3_XH             0b00000010  // X-axis high event (over threshold). Default value: 0
                        //  (0: event not detected; 1: event (over threshold) detected)
#define LSM6DS3_XL             0b00000001  // X-axis low event (under threshold). Default value: 0
                        //  (0: event not detected; 1: event (under threshold) detected)

/* Status Register (r) */
#define LSM6DS3_STATUS_REG        0x1E
// Bits & Masks
#define LSM6DS3_EV_BOOT          0b00001000  // Boot running flag signal. Default value: 0
                        //  (0: no boot running; 1: boot running)
#define LSM6DS3_TDA           0b00000100  // Temperature new data available. Default: 0
                        //  (0: no set of data is available at temperature sensor output;
                        //   1: a new set of data is available at temperature sensor output)
#define LSM6DS3_GDA           0b00000010  // Gyroscope new data available. Default value: 0
                        //  (0: no set of data available at gyroscope output;
                        //   1: a new set of data is available at gyroscope output)
#define LSM6DS3_XLDA          0b00000001  // Accelerometer new data available. Default value: 0
                        //  (0: no set of data available at accelerometer output;
                        //   1: a new set of data is available at accelerometer output)

/* Temperature data output register (r). L and H registers together express a 16-bit word in two?s
complement (r). */
#define LSM6DS3_OUT_TEMP_L        0x20
#define LSM6DS3_OUT_TEMP_H        0x21


/* Angular rate sensor base address of six contiguous registers used for 16-bit 2's complement x,y,z values*/
#define LSM6DS3_OUT_BASE_G      0x22

/* Angular rate sensor pitch axis (X) angular rate output register (r). The value is expressed as a 16-bit
word in two?s complement. (r) */
#define LSM6DS3_OUTX_L_G        0x22
#define LSM6DS3_OUTX_H_G        0x23

/* Angular rate sensor roll axis (Y) angular rate output register (r). The value is expressed as a 16-bit
word in two?s complement. (r). */
#define LSM6DS3_OUTY_L_G        0x24
#define LSM6DS3_OUTY_H_G        0x25

/* Angular rate sensor yaw axis (Z) angular rate output register (r). The value is expressed as a 16-bit
word in two?s complement. (r). */
#define LSM6DS3_OUTZ_L_G        0x26
#define LSM6DS3_OUTZ_H_G        0x27

/* Linear acceleration sensor base address of six contiguous registers used for 16-bit 2's complement x,y,z values*/
#define LSM6DS3_OUT_BASE_XL      0x28

/* Linear acceleration sensor X-axis output register (r). The value is expressed as a 16-bit word in two?s
complement. */
#define LSM6DS3_OUTX_L_XL        0x28
#define LSM6DS3_OUTX_H_XL        0x29

/* Linear acceleration sensor Y-axis output register (r). The value is expressed as a 16-bit word in two?s
complement. */
#define LSM6DS3_OUTY_L_XL        0x2A
#define LSM6DS3_OUTY_H_XL        0x2B

/* Linear acceleration sensor Z-axis output register (r). The value is expressed as a 16-bit word in two?s
complement. */
#define LSM6DS3_OUTZ_L_XL        0x2C
#define LSM6DS3_OUTZ_H_XL        0x2D

/* First byte associated to external sensors. The content of the register is consistent with the
SLAVEx_CONFIG number of read operation configurations (for external sensors from x = 0 to x = 3). */
#define LSM6DS3_SENSORHUB1_REG      0x2E

/* Second byte associated to external sensors. The content of the register is consistent with the
SLAVEx_CONFIG number of read operations configurations (for external sensors from x = 0 to x = 3). */
#define LSM6DS3_SENSORHUB2_REG      0x2F

/* Third byte associated to external sensors. The content of the register is consistent with the
SLAVEx_CONFIG number of read operations configurations (for external sensors from x = 0 to x = 3). */
#define LSM6DS3_SENSORHUB3_REG      0x30
#define LSM6DS3_SENSORHUB4_REG      0x31
#define LSM6DS3_SENSORHUB5_REG      0x32
#define LSM6DS3_SENSORHUB6_REG      0x33
#define LSM6DS3_SENSORHUB7_REG      0x34
#define LSM6DS3_SENSORHUB8_REG      0x35
#define LSM6DS3_SENSORHUB9_REG      0x36
#define LSM6DS3_SENSORHUB10_REG      0x37
#define LSM6DS3_SENSORHUB11_REG      0x38
#define LSM6DS3_SENSORHUB12_REG      0x39

/* FIFO status control register (r). For a proper reading of the register, it is recommended to set the
BDU bit in CTRL3_C (12h) to 1. */
#define LSM6DS3_FIFO_STATUS1      0x3A

/* FIFO status control register (r). For a proper reading of the register, it is recommended to set the
BDU bit in CTRL3_C (12h) to 1. */
#define LSM6DS3_FIFO_STATUS2      0x3B
// Bits & Masks
#define LSM6DS3_FTH           0b10000000  // FIFO watermark status. Default value: 0
                        //  (0: FIFO filling is lower than watermark level(1);
                        //   1: FIFO filling is equal to or higher than the watermark level)
                        //   1. FIFO watermark level is set in FTH_[11:0] in FIFO_CTRL1 (06h) and FIFO_CTRL2 (07h)
#define LSM6DS3_FIFO_OVER_RUN       0b01000000  //  FIFO overrun status. Default value: 0
                        //  (0: FIFO is not completely filled; 1: FIFO is completely filled)
#define LSM6DS3_FIFO_FULL         0b00100000  // FIFO full status. Default value: 0
                        //  (0: FIFO is not full; 1: FIFO will be full at the next ODR)
#define LSM6DS3_FIFO_EMPTY         0b00010000  // FIFO empty bit. Default value: 0
                        //  (0: FIFO contains data; 1: FIFO is empty)
#define LSM6DS3_DIFF_FIFO_H       0b00001111  // Number of unread words (16-bit axes) stored in FIFO(2).
                        //   2. For a complete number of unread samples, consider DIFF_FIFO [11:8] in FIFO_STATUS1 (3Ah)

#define LSM6DS3_FIFO_STATUS3      0x3C
#define LSM6DS3_FIFO_STATUS4      0x3D

/* FIFO data output register (r). For a proper reading of the register, it is recommended to set the BDU bit
in CTRL3_C (12h) to 1. */
#define LSM6DS3_DATA_OUT_L        0x3E
#define LSM6DS3_DATA_OUT_H        0x3F

/* Time stamp first byte data output register (r). The value is expressed as a 24-bit word and the bit
resolution is defined by setting the value in WAKE_UP_DUR (5Ch). */
#define LSM6DS3_TIMESTAMP0_REG      0x40
#define LSM6DS3_TIMESTAMP1_REG      0x41
#define LSM6DS3_TIMESTAMP2_REG      0x42

/* Step counter timestamp information register (r). When a step is detected, the value of
TIMESTAMP_REG1 register is copied in STEP_TIMESTAMP_L. */
#define LSM6DS3_STEP_TIMESTAMP_L    0x49

/* Step counter timestamp information register (r). When a step is detected, the value of
TIMESTAMP_REG2 register is copied in STEP_TIMESTAMP_H. */
#define LSM6DS3_STEP_TIMESTAMP_H    0x4A

/* Step counter output register (r). */
#define LSM6DS3_STEP_COUNTER_L      0x4B
#define LSM6DS3_STEP_COUNTER_H      0x4C

/* Thirteenth byte associated to external sensors. The content of the register is consistent with the
SLAVEx_CONFIG number of read operation configurations (for external sensors from x = 0 to x = 3). */
#define LSM6DS3_SENSORHUB13_REG      0x4D
#define LSM6DS3_SENSORHUB14_REG      0x4E
#define LSM6DS3_SENSORHUB15_REG      0x4F
#define LSM6DS3_SENSORHUB16_REG      0x50
#define LSM6DS3_SENSORHUB17_REG      0x51
#define LSM6DS3_SENSORHUB18_REG      0x52

/* Significant motion, tilt, step detector, hard/soft-iron and sensor hub interrupt source register
(r). */
#define LSM6DS3_FUNC_SRC        0x53
// Bits & Masks
#define LSM6DS3_STEP_COUNT_DELTA_IA    0b10000000  // Pedometer step recognition on delta time status. Default value: 0
                        //  (0: no step recognized during delta time; 1: at least one step recognized during
                        //   delta time)
#define LSM6DS3_SIGN_MOTION_IA      0b01000000  // Significant motion event detection status. Default value: 0
                        //  (0: significant motion event not detected; 1: significant motion event detected)
#define LSM6DS3_TILT_IA          0b00100000  // Tilt event detection status. Default value: 0
                        //  (0: tilt event not detected; 1: tilt event detected)
#define LSM6DS3_STEP_DETECTED      0b00010000  // Step detector event detection status. Default value: 0
                        //  (0: step detector event not detected; 1: step detector event detected)
#define LSM6DS3_STEP_OVERFLOW      0b00001000  // Step counter overflow status. Default value: 0
                        //  (0: step counter value < 216; 1: step counter value reached 216)
#define LSM6DS3_SI_END_OP        0b00000100  // Hard/soft-iron calculation status. Default value: 0
                        //  (0: Hard/soft-iron calculation not concluded; 1: Hard/soft-iron calculation concluded)
#define LSM6DS3_SENSORHUB_END_OP    0b00000010  // Sensor hub communication status. Default value: 0
                        //  (0: sensor hub communication not concluded;
                        //   1: sensor hub communication concluded)

/* Time stamp, pedometer, tilt, filtering, and tap recognition functions configuration register
(r/w). */
#define LSM6DS3_TAP_CFG          0x58
// Bits & Masks
#define LSM6DS3_TIMER_EN         0b10000000  // Time stamp count enable, output data are collected in TIMESTAMP0_REG (40h),
                        //   TIMESTAMP1_REG (41h), TIMESTAMP2_REG (42h) register. Default: 0
                        //  (0: time stamp count disabled; 1: time stamp count enabled)
#define LSM6DS3_PEDO_EN         0b01000000  // Pedometer algorithm enable. Default value: 0
                        //  (0: pedometer algorithm disabled; 1: pedometer algorithm enabled)
#define LSM6DS3_TILT_EN         0b00100000  // Tilt calculation enable. Default value: 0
                        //  (0: tilt calculation disabled; 1: tilt calculation enabled.)
#define LSM6DS3_SLOPE_FDS         0b00010000  // Enable accelerometer HP and LPF2 filters (refer to Figure 5). Default value: 0
                        //  (0: disable; 1: enable)
#define LSM6DS3_TAP_X_EN         0b00001000  // Enable X direction in tap recognition. Default value: 0
                        //  (0: X direction disabled; 1:X direction enabled)
#define LSM6DS3_TAP_Y_EN         0b00000100  // Enable Y direction in tap recognition. Default value: 0
                        //  (0: Y direction disabled; 1:Y direction enabled)
#define LSM6DS3_TAP_Z_EN         0b00000010  // Enable Z direction in tap recognition. Default value: 0
                        //  (0: Z direction disabled; 1:Z direction enabled)
#define LSM6DS3_LIR           0b00000001  // Latched Interrupt. Default value: 0
                        //  (0: interrupt request not latched; 1: interrupt request latched)

/* Portrait/landscape position and tap function threshold register (r/w). */
#define LSM6DS3_TAP_THS_6D        0x59
// Bits & Masks
#define LSM6DS3_D4D_EN          0b10000000  // 4D orientation detection enable. Z-axis position detection is disabled.
                        //   Default value: 0
                        //  (0: enabled; 1: disabled)
#define LSM6DS3_SIXD_THS        0b01100000  // Threshold for D6D function. Default value: 00
                        //   For details, refer to Table 179.
#define LSM6DS3_SIXD_THS_80DEG      0b00000000  // 80 degrees
#define LSM6DS3_SIXD_THS_70DEG      0b00100000  // 70 degrees
#define LSM6DS3_SIXD_THS_60DEG      0b01000000  // 60 degrees
#define LSM6DS3_SIXD_THS_50DEG      0b01100000  // 50 degrees
#define LSM6DS3_TAP_THS         0b00011111  // Threshold for tap recognition. Default value: 00000

/* Tap recognition function setting register (r/w). */
#define LSM6DS3_INT_DUR2        0x5A
#define LSM6DS3_DUR           0b11110000  // Duration of maximum time gap for double tap recognition. Default: 0000
                        //   When double tap recognition is enabled, this register expresses the maximum time
                        //   between two consecutive detected taps to determine a double tap event. The
                        //   default value of these bits is 0000b which corresponds to 16*ODR_XL time. If the
                        //   DUR[3:0] bits are set to a different value, 1LSB corresponds to 32*ODR_XL time.
#define LSM6DS3_QUIET          0b00001100  // Expected quiet time after a tap detection. Default value: 00
                        //   Quiet time is the time after the first detected tap in which there must not be any
                        //   overthreshold event. The default value of these bits is 00b which corresponds to
                        //   2*ODR_XL time. If the QUIET[1:0] bits are set to a different value, 1LSB
                        //   corresponds to 4*ODR_XL time.
#define LSM6DS3_SHOCK          0b00000011  // Maximum duration of overthreshold event. Default value: 00
                        //   Maximum duration is the maximum time of an overthreshold signal detection to be
                        //   recognized as a tap event. The default value of these bits is 00b which corresponds
                        //   to 4*ODR_XL time. If the SHOCK[1:0] bits are set to a different value, 1LSB
                        //   corresponds to 8*ODR_XL time.

/* Single and double-tap function threshold register (r/w). */
#define LSM6DS3_WAKE_UP_THS        0x5B
#define LSM6DS3_SINGLE_DOUBLE_TAP    0b10000000  // Single/double-tap event enable. Default: 0
                        //  (0: only single-tap event enabled;
                        //   1: both single and double-tap events enabled)
#define LSM6DS3_INACTIVITY         0b01000000  // Inactivity event enable. Default value: 0
                        //  (0: sleep disabled; 1: sleep enabled)
#define LSM6DS3_WK_THS           0b00111111  // Threshold for wakeup. Default value: 000000

/* Free-fall, wakeup, time stamp and sleep mode functions duration setting register (r/w). */
#define LSM6DS3_WAKE_UP_DUR        0x5C
#define LSM6DS3_FF_DUR5          0b10000000  // Free fall duration event. Default: 0
                        //   For the complete configuration of the free-fall duration, refer to FF_DUR[4:0] in
                        //   FREE_FALL (5Dh) configuration.
#define LSM6DS3_WAKE_DUR         0b01100000  // Wake up duration event. Default: 00
                        //   1LSB = 1 ODR_time
#define LSM6DS3_TIMER_HR         0b00010000  // Time stamp register resolution setting(1). Default value: 0
                        //  (0: 1LSB = 6.4 ms; 1: 1LSB = 25 ?s)
                        //   1. Configuration of this bit affects TIMESTAMP0_REG (40h), TIMESTAMP1_REG (41h),
                        //      TIMESTAMP2_REG (42h), STEP_TIMESTAMP_L (49h), STEP_TIMESTAMP_H (4Ah), and
                        //      STEP_COUNT_DELTA (15h) registers.
#define LSM6DS3_SLEEP_DUR        0b00001111  // Duration to go in sleep mode. Default value: 0000
                        //    1 LSB = 512 ODR

/* Free-fall function duration setting register (r/w). */
#define LSM6DS3_FREE_FALL        0x5D
// Bits & Masks
#define LSM6DS3_FF_DUR           0b11111000  // Free-fall duration event. Default: 0
                        //   For the complete configuration of the free fall duration, refer to FF_DUR5 in
                        //   WAKE_UP_DUR (5Ch) configuration
#define LSM6DS3_FF_THS          0b00000111  // Free fall threshold setting. Default: 000
                        //   For details refer to Table 188.
#define LSM6DS3_FF_THS_156MG      0b00000000  // 156 mg
#define LSM6DS3_FF_THS_219MG      0b00000001  // 219 mg
#define LSM6DS3_FF_THS_250MG      0b00000010  // 250 mg
#define LSM6DS3_FF_THS_312MG      0b00000011  // 312 mg
#define LSM6DS3_FF_THS_344MG      0b00000100  // 344 mg
#define LSM6DS3_FF_THS_406MG      0b00000101  // 406 mg
#define LSM6DS3_FF_THS_469MG      0b00000110  // 469 mg
#define LSM6DS3_FF_THS_500MG      0b00000111  // 500 mg

/* Functions routing on INT1 register (r/w). */
#define LSM6DS3_MD1_CFG          0x5E
// Bits & Masks
#define LSM6DS3_INT1_INACT_STATE     0b10000000  // Routing on INT1 of inactivity mode. Default: 0
                        //  (0: routing on INT1 of inactivity disabled; 1: routing on INT1 of inactivity enabled)
#define LSM6DS3_INT1_SINGLE_TAP      0b01000000  // Single-tap recognition routing on INT1. Default: 0
                        //  (0: routing of single-tap event on INT1 disabled;
                        //   1: routing of single-tap event on INT1 enabled)
#define LSM6DS3_INT1_WU          0b00100000  // Routing of wakeup event on INT1. Default value: 0
                        //  (0: routing of wakeup event on INT1 disabled;
                        //   1: routing of wakeup event on INT1 enabled)
#define LSM6DS3_INT1_FF         0b00010000  // Routing of free-fall event on INT1. Default value: 0
                        //  (0: routing of free-fall event on INT1 disabled;
                        //   1: routing of free-fall event on INT1 enabled)
#define LSM6DS3_INT1_DOUBLE_TAP     0b00001000  // Routing of tap event on INT1. Default value: 0
                        //  (0: routing of double-tap event on INT1 disabled;
                        //   1: routing of double-tap event on INT1 enabled)
#define LSM6DS3_INT1_6D          0b00000100  // Routing of 6D event on INT1. Default value: 0
                        //  (0: routing of 6D event on INT1 disabled; 1: routing of 6D event on INT1 enabled)
#define LSM6DS3_INT1_TILT        0b00000010  // Routing of tilt event on INT1. Default value: 0
                        //  (0: routing of tilt event on INT1 disabled; 1: routing of tilt event on INT1 enabled)
#define LSM6DS3_INT1_TIMER        0b00000001  // Routing of end counter event of timer on INT1. Default value: 0
                        //  (0: routing of end counter event of timer on INT1 disabled;
                        //   1: routing of end counter event of timer event on INT1 enabled)

/* Functions routing on INT2 register (r/w). */
#define LSM6DS3_MD2_CFG          0x5F
// Bits & Masks
#define LSM6DS3_INT2_INACT_STATE    0b10000000  // Routing on INT2 of inactivity mode. Default: 0
                        //  (0: routing on INT2 of inactivity disabled; 1: routing on INT2 of inactivity enabled)
#define LSM6DS3_INT2_SINGLE_TAP      0b01000000  // Single-tap recognition routing on INT2. Default: 0
                        //  (0: routing of single-tap event on INT2 disabled;
                        //   1: routing of single-tap event on INT2 enabled)
#define LSM6DS3_INT2_WU          0b00100000  // Routing of wakeup event on INT2. Default value: 0
                        //  (0: routing of wakeup event on INT2 disabled;
                        //   1: routing of wake-up event on INT2 enabled)
#define LSM6DS3_INT2_FF         0b00010000  // Routing of free-fall event on INT2. Default value: 0
                        //  (0: routing of free-fall event on INT2 disabled;
                        //   1: routing of free-fall event on INT2 enabled)
#define LSM6DS3_INT2_DOUBLE_TAP      0b00001000  // Routing of tap event on INT2. Default value: 0
                        //  (0: routing of double-tap event on INT2 disabled;
                        //   1: routing of double-tap event on INT2 enabled)
#define LSM6DS3_INT2_6D          0b00000100  // Routing of 6D event on INT2. Default value: 0
                        //  (0: routing of 6D event on INT2 disabled; 1: routing of 6D event on INT2 enabled)
#define LSM6DS3_INT2_TILT        0b00000010  // Routing of tilt event on INT2. Default value: 0
                        //  (0: routing of tilt event on INT2 disabled; 1: routing of tilt event on INT2 enabled)
#define LSM6DS3_INT2_IRON        0b00000001  // Routing of soft-iron/hard-iron algorithm end event on INT2. Default value: 0
                        //  (0: routing of soft-iron/hard-iron algorithm end event on INT2 disabled;
                        //   1: routing of soft-iron/hard-iron algorithm end event on INT2 enabled)
/* External magnetometer raw data (r). */
#define LSM6DS3_OUT_MAG_RAW_X_L      0x66
#define LSM6DS3_OUT_MAG_RAW_X_H      0x67
#define LSM6DS3_OUT_MAG_RAW_Y_L      0x68
#define LSM6DS3_OUT_MAG_RAW_Y_H      0x69
#define LSM6DS3_OUT_MAG_RAW_Z_L      0x6A
#define LSM6DS3_OUT_MAG_RAW_Z_H      0x6B


#endif /* DRV_LSM6DS3_PROTOCOL_H_ */
