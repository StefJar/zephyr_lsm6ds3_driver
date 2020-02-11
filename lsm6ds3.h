/*
 * lsm6ds3.h
 *
 *  Created on: 18 Jan 2019
 *      Author: stefan jaritz
 */

#ifndef DRV_LSM6DS3_H_
#define DRV_LSM6DS3_H_

#include <device.h>

#define LSM6DS3_DEV_NAME "LSM6DS3"

typedef enum acc_config_ids {
	acc_cfg_off = 0,
	acc_cfg_26Hz_2g_50Hz = 1,
	acc_cfg_52Hz_2g_50Hz = 2,
	acc_cfg_104Hz_2g_50Hz = 3,
	acc_cfg_208Hz_2g_50Hz = 4,
	acc_cfg_MaxIndex
} acc_config_id_t;

typedef enum gyr_config_ids {
	gyr_cfg_off = 0,
	gyr_cfg_26Hz_245DPS = 1,
	gyr_cfg_52Hz_245DPS = 2,
	gyr_cfg_104Hz_245DPS = 3,
	gyr_cfg_208Hz_245DPS = 4,
	gyr_cfg_MaxIndex
} gyr_config_id_t;

typedef uint16_t movSample_t [3]; // x, y, z sample at 16Bit

typedef union ufifo_status {
	struct {
	// FIFO_STATUS1: DIFF_FIFO_[7:0]
	// FIFO_STATUS2: FTH, FIFO_OVER_RUN, FIFO_FULL, FIFO_EMPTY, DIFF_FIFO [11:8]
	// FIFO_STATUS3: FIFO_PATTERN_[7:0]
	// FIFO_STATUS4: 0, 0, 0, 0, 0, 0, FIFO_PATTERN_[9:8]
	unsigned int diff : 12;
	unsigned int empty : 1;
	unsigned int full : 1;
	unsigned int overrun : 1;
	unsigned int watermarkStatus : 1;
	unsigned int pattern : 10;
	unsigned int unused : 6;
	} bits;
	u32_t raw;
} fifo_status_t;


typedef struct lsm6ds3_api_s {
	void (* init) (void);
	void (* powerDown) (void);
	void (* setup) (acc_config_id_t acc, unsigned int accIntrChannel, gyr_config_id_t gyr, unsigned int gyrIntrChannel);
	int (* readAcc) (movSample_t * pAcc);
	int (* readGyr) (movSample_t * pGyr);
	int (* getFiFoStatus)(fifo_status_t * s);
	int (* readFiFoWords)(u16_t * pB, unsigned int N);
} lsm6ds3_api_t;


#endif /* DRV_LSM6DS3_H_ */
