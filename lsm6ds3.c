/*
 * lsm6ds3.c
 *
 *  Created on: 18 Jan 2019
 *      Author: stefan jaritz
 */

#include <zephyr.h>
#include "lsm6ds3.h"
#include "lsm6ds3_protocol.h"

#include <errno.h>
#include <device.h>
#include <drivers/spi.h>

#include <logging/log.h>

#define LOG_LEVEL_APP_LSM6DS3 4
LOG_MODULE_REGISTER(LSM6DS3, LOG_LEVEL_APP_LSM6DS3);

//chip select pin PC9
#define LSM6DS3_CS_GPIO_NAME "GPIOC"
#define LSM6DS3_CS_GPIO_NUM 9

#define LSM6DS3_SPI "SPI_3"

typedef enum lsm6ds3_reg_addrs {
	lsm6ds3_reg_addr_reserved_0 = 0x00,
	lsm6ds3_reg_addr_FUNC_CFG_ACCESS = 0x1,
	lsm6ds3_reg_addr_reserved_1 = 0x2,
	lsm6ds3_reg_addr_reserved_2 = 0x3,
	lsm6ds3_reg_addr_SENSOR_SYNC_TIME_FRAME = 0x04,
	lsm6ds3_reg_addr_reserved_3 = 0x05,
	lsm6ds3_reg_addr_FIFO_CTRL1 = 0x06,
	lsm6ds3_reg_addr_FIFO_CTRL2 = 0x07,
	lsm6ds3_reg_addr_FIFO_CTRL3 = 0x08,
	lsm6ds3_reg_addr_FIFO_CTRL4 = 0x09,
	lsm6ds3_reg_addr_FIFO_CTRL5 = 0x0A,
	lsm6ds3_reg_addr_ORIENT_CFG_G = 0x0B,
	lsm6ds3_reg_addr_reserved_4 = 0x0C,
	lsm6ds3_reg_addr_INT1_CTRL = 0x0D,
	lsm6ds3_reg_addr_INT2_CTRL = 0x0E,
	lsm6ds3_reg_addr_WHO_AM_I = 0x0F,
	lsm6ds3_reg_addr_CTRL1_XL = 0x10,
	lsm6ds3_reg_addr_CTRL2_G = 0x11,
	lsm6ds3_reg_addr_CTRL3_C = 0x12,
	lsm6ds3_reg_addr_CTRL4_C = 0x13,
	lsm6ds3_reg_addr_CTRL5_C = 0x14,
	lsm6ds3_reg_addr_CTRL6_C = 0x15,
	lsm6ds3_reg_addr_CTRL7_G = 0x16,
	lsm6ds3_reg_addr_CTRL8_XL = 0x17,
	lsm6ds3_reg_addr_CTRL9_XL = 0x18,
	lsm6ds3_reg_addr_CTRL10_C = 0x19,
	lsm6ds3_reg_addr_MASTER_CONFIG = 0x1A,
	lsm6ds3_reg_addr_WAKE_UP_SRC = 0x1B,
	lsm6ds3_reg_addr_TAP_SRC = 0x1C,
	lsm6ds3_reg_addr_D6D_SRC = 0x1D,
	lsm6ds3_reg_addr_STATUS_REG = 0x1E,
	lsm6ds3_reg_addr_reserved_5 = 0x1F,
	lsm6ds3_reg_addr_OUT_TEMP_L = 0x20,
	lsm6ds3_reg_addr_OUT_TEMP_H = 0x21,
	lsm6ds3_reg_addr_OUTX_L_G = 0x22,
	lsm6ds3_reg_addr_OUTX_H_G = 0x23,
	lsm6ds3_reg_addr_OUTY_L_G = 0x24,
	lsm6ds3_reg_addr_OUTY_H_G = 0x25,
	lsm6ds3_reg_addr_OUTZ_L_G = 0x26,
	lsm6ds3_reg_addr_OUTZ_H_G = 0x27,
	lsm6ds3_reg_addr_OUTX_L_XL = 0x28,
	lsm6ds3_reg_addr_OUTX_H_XL = 0x29,
	lsm6ds3_reg_addr_OUTY_L_XL = 0x2A,
	lsm6ds3_reg_addr_OUTY_H_XL = 0x2B,
	lsm6ds3_reg_addr_OUTZ_L_XL = 0x2C,
	lsm6ds3_reg_addr_OUTZ_H_XL = 0x2D,
	lsm6ds3_reg_addr_SENSORHUB1_REG = 0x2E,
	lsm6ds3_reg_addr_SENSORHUB2_REG = 0x2F,
	lsm6ds3_reg_addr_SENSORHUB3_REG = 0x30,
	lsm6ds3_reg_addr_SENSORHUB4_REG = 0x31,
	lsm6ds3_reg_addr_SENSORHUB5_REG = 0x32,
	lsm6ds3_reg_addr_SENSORHUB6_REG = 0x33,
	lsm6ds3_reg_addr_SENSORHUB7_REG = 0x34,
	lsm6ds3_reg_addr_SENSORHUB8_REG = 0x35,
	lsm6ds3_reg_addr_SENSORHUB9_REG = 0x36,
	lsm6ds3_reg_addr_SENSORHUB10_REG = 0x37,
	lsm6ds3_reg_addr_SENSORHUB11_REG = 0x38,
	lsm6ds3_reg_addr_SENSORHUB12_REG = 0x39,
	lsm6ds3_reg_addr_FIFO_STATUS1 = 0x3A,
	lsm6ds3_reg_addr_FIFO_STATUS2 = 0x3B,
	lsm6ds3_reg_addr_FIFO_STATUS3 = 0x3C,
	lsm6ds3_reg_addr_FIFO_STATUS4 = 0x3D,
	lsm6ds3_reg_addr_FIFO_DATA_OUT_L = 0x3E,
	lsm6ds3_reg_addr_FIFO_DATA_OUT_H = 0x3F,
	lsm6ds3_reg_addr_TIMESTAMP0_REG = 0x40,
	lsm6ds3_reg_addr_TIMESTAMP1_REG = 0x41,
	lsm6ds3_reg_addr_TIMESTAMP2_REG = 0x42,
	lsm6ds3_reg_addr_reserved_6 = 0x43,
	lsm6ds3_reg_addr_reserved_7 = 0x44,
	lsm6ds3_reg_addr_reserved_8 = 0x45,
	lsm6ds3_reg_addr_reserved_9 = 0x46,
	lsm6ds3_reg_addr_reserved_10 = 0x47,
	lsm6ds3_reg_addr_reserved_11 = 0x48,
	lsm6ds3_reg_addr_STEP_TIMESTAMP_L = 0x49,
	lsm6ds3_reg_addr_STEP_TIMESTAMP_H = 0x4A,
	lsm6ds3_reg_addr_STEP_COUNTER_L = 0x4B,
	lsm6ds3_reg_addr_STEP_COUNTER_H = 0x4C,
	lsm6ds3_reg_addr_SENSORHUB13_REG = 0x4D,
	lsm6ds3_reg_addr_SENSORHUB14_REG = 0x4E,
	lsm6ds3_reg_addr_SENSORHUB15_REG = 0x4F,
	lsm6ds3_reg_addr_SENSORHUB16_REG = 0x50,
	lsm6ds3_reg_addr_SENSORHUB17_REG = 0x51,
	lsm6ds3_reg_addr_SENSORHUB18_REG = 0x52,
	lsm6ds3_reg_addr_FUNC_SRC = 0x53,
	lsm6ds3_reg_addr_reserved_12 = 0x54,
	lsm6ds3_reg_addr_reserved_13 = 0x55,
	lsm6ds3_reg_addr_reserved_14 = 0x56,
	lsm6ds3_reg_addr_reserved_15 = 0x57,
	lsm6ds3_reg_addr_TAP_CFG = 0x58,
	lsm6ds3_reg_addr_TAP_THS_6D = 0x59,
	lsm6ds3_reg_addr_INT_DUR2 = 0x5A,
	lsm6ds3_reg_addr_WAKE_UP_THS = 0x5B,
	lsm6ds3_reg_addr_WAKE_UP_DUR = 0x5C,
	lsm6ds3_reg_addr_FREE_FALL = 0x5D,
	lsm6ds3_reg_addr_MD1_CFG = 0x5E,
	lsm6ds3_reg_addr_MD2_CFG = 0x5F,
	lsm6ds3_reg_addr_reserved_16 = 0x60,
	lsm6ds3_reg_addr_reserved_17 = 0x61,
	lsm6ds3_reg_addr_reserved_18 = 0x62,
	lsm6ds3_reg_addr_reserved_19 = 0x63,
	lsm6ds3_reg_addr_reserved_20 = 0x64,
	lsm6ds3_reg_addr_reserved_21 = 0x65,
	lsm6ds3_reg_addr_OUT_MAG_RAW_X_L = 0x66,
	lsm6ds3_reg_addr_OUT_MAG_RAW_X_H = 0x67,
	lsm6ds3_reg_addr_OUT_MAG_RAW_Y_L = 0x68,
	lsm6ds3_reg_addr_OUT_MAG_RAW_Y_H = 0x69,
	lsm6ds3_reg_addr_OUT_MAG_RAW_Z_L = 0x6A,
	lsm6ds3_reg_addr_OUT_MAG_RAW_Z_H = 0x6B,
	lsm6ds3_reg_addr_amount,
} lsm6ds3_reg_addr_t;

typedef struct lsm6ds3_reg {
	lsm6ds3_reg_addr_t addr;
	u8_t v;
} lsm6ds3_reg_t;

typedef struct acc_config_set {
	unsigned int ctrl1_xl; /* value of the CTRL1 XL register*/
} acc_config_set_t;

typedef struct gyr_config_set {
	unsigned int ctrl2_g; /* value of the CTRL2 G register*/
} gyr_config_set_t;

/*
 * acc_config_t
 *
 * a structure holding all variables need to config
 * the accelerometer data
 */
typedef struct acc_config {
	// accelerometer configs
	const acc_config_set_t * pAccCfgSetL; /* const pointer to the list with the possible accelerometer configs*/
	const unsigned int cfgAccAm; /* amount of cfgs in the accelerometer config set list*/

	// gyroscope configs
	const gyr_config_set_t * pGyrCfgSetL; /* const pointer to the list with the possible gyroscope configs*/
	const unsigned int cfgGyrAm; /* amount of cfgs in the gyroscope config set list*/
} acc_config_t;

static const acc_config_set_t acc_cfgSetL[acc_cfg_MaxIndex] = {
	/* cfg: off*/
	{.ctrl1_xl = LSM6DS3_ODR_XL_POWER_DOWN},
	/* cfg: f_s=26Hz, 2g = full scale, bw_AntiAliasing_filter = 50Hz */
	{.ctrl1_xl = (LSM6DS3_ODR_XL_26HZ | LSM6DS3_FS_XL_2G | LSM6DS3_BW_XL_50HZ)},
	/* cfg: f_s=52Hz, 2g = full scale, bw_AntiAliasing_filter = 50Hz */
	{.ctrl1_xl = (LSM6DS3_ODR_XL_52HZ | LSM6DS3_FS_XL_2G | LSM6DS3_BW_XL_50HZ)},
	/* cfg: f_s=104Hz, 2g = full scale, bw_AntiAliasing_filter = 50Hz */
	{.ctrl1_xl = (LSM6DS3_ODR_XL_104HZ | LSM6DS3_FS_XL_2G | LSM6DS3_BW_XL_50HZ)},
	/* cfg: f_s=208Hz, 2g = full scale, bw_AntiAliasing_filter = 50Hz */
	{.ctrl1_xl = (LSM6DS3_ODR_XL_208HZ | LSM6DS3_FS_XL_2G | LSM6DS3_BW_XL_50HZ)},
}; /* list with possible config sets*/

static const gyr_config_set_t gyr_cfgSetL[gyr_cfg_MaxIndex] = {
	/* cfg: off*/
	{.ctrl2_g = LSM6DS3_ODR_G_POWER_DOWN},
	/* cfg: f_s=26Hz 245dps*/
	{.ctrl2_g = (LSM6DS3_ODR_G_26HZ | LSM6DS3_FS_G_245DPS)},
	/* cfg: f_s=52Hz 245dps*/
	{.ctrl2_g = (LSM6DS3_ODR_G_52HZ | LSM6DS3_FS_G_245DPS)},
	/* cfg: f_s=104Hz 245dps*/
	{.ctrl2_g = (LSM6DS3_ODR_G_104HZ | LSM6DS3_FS_G_245DPS)},
	/* cfg: f_s=208Hz 245dps*/
	{.ctrl2_g = (LSM6DS3_ODR_G_208HZ | LSM6DS3_FS_G_245DPS)},
}; /* list with possible config sets*/

static const acc_config_t acc_cfg = {
	.pAccCfgSetL = acc_cfgSetL,
	.cfgAccAm = sizeof(acc_cfgSetL) / sizeof(const acc_config_set_t),

	.pGyrCfgSetL = gyr_cfgSetL,
	.cfgGyrAm = sizeof(gyr_cfgSetL) / sizeof(const gyr_config_set_t),
};

typedef struct lsm6ds3_s {
	struct device * spiDev; // spi device
	struct spi_cs_control spi_cs_conf; // spi chip select config
	struct spi_config spi_conf; // spi config
	unsigned int accCfgIndx; // the selected accelerometer configuration
	unsigned int gyrCfgIndx; // the selected gyroscope configuration
} lsm6ds3_t;

static lsm6ds3_t lsm6ds3 = {
	.spiDev = NULL,
	.spi_cs_conf = {
		.gpio_dev = NULL,
		.gpio_pin = LSM6DS3_CS_GPIO_NUM,
		.delay = 1, // 20ns chip select time
	},
	.spi_conf = {
		.frequency = 10000000, // 10MHz clk speed
		.operation = (SPI_OP_MODE_MASTER | SPI_MODE_CPOL | SPI_MODE_CPHA | SPI_WORD_SET(8) | SPI_LINES_SINGLE), // master,
		.slave     = 0, // slave number 0
		.cs        = NULL, // chip select pin
	},
	.accCfgIndx = acc_cfg_off,
	.gyrCfgIndx = gyr_cfg_off,
};

static int lsm6ds3_raw_write(u8_t reg_addr, u8_t * pD, u8_t len) {
	u8_t buffer_tx[] = { LSM6DS3_SPI_WRITE | reg_addr};
	struct spi_buf tx_buf [] = {
		{
		.buf = buffer_tx,
		.len = sizeof(buffer_tx)/sizeof(u8_t)
		},
		{
		.buf = pD,
		.len = len
		}
	};
	const struct spi_buf_set tx = {
		.buffers = tx_buf,
		.count = sizeof(tx_buf)/sizeof(struct spi_buf)
	};

	if (spi_write(lsm6ds3.spiDev, &lsm6ds3.spi_conf, &tx)) {
		return -EIO;
	}
	return 0;
}

static int lsm6ds3_raw_read(u8_t reg_addr, u8_t *v, u8_t len) {
	u8_t buffer_tx[] = {LSM6DS3_SPI_READ | reg_addr};
	struct spi_buf tx_buf [] = {
		{
		.buf = buffer_tx,
		.len = sizeof(buffer_tx)/sizeof(u8_t)
		}
	};
	const struct spi_buf_set tx = {
		.buffers = tx_buf,
		.count = sizeof(tx_buf)/sizeof(struct spi_buf)
	};
	const struct spi_buf rx_buf []= {
		{
		.buf = NULL,
		.len = 1,
		},
		{
		.buf = v,
		.len = len,
		}
	};
	const struct spi_buf_set rx = {
		.buffers = rx_buf,
		.count = sizeof(rx_buf)/sizeof(struct spi_buf)
	};

	if (spi_transceive(lsm6ds3.spiDev, &lsm6ds3.spi_conf, &tx, &rx)) {
		return -EIO;
	}
	return 0;
}

static int lsm6ds3_regs_write(lsm6ds3_reg_t * pRL, size_t N) {
	int r;
	for (size_t i = 0; i < N; i++) {
		r = lsm6ds3_raw_write(pRL->addr, &(pRL->v), 1);
		if (r) return r;
		pRL++;
	}
	return 0;
}

static int lsm6ds3_initialize(struct device *dev) {
	LOG_DBG("init LSM6DS3");

	// get spi3 device
	lsm6ds3.spiDev = device_get_binding(LSM6DS3_SPI);
	if (NULL == lsm6ds3.spiDev) {
		LOG_ERR("can not find device " LSM6DS3_SPI);
		return -1;
	}

	// get chip select pin device
	lsm6ds3.spi_cs_conf.gpio_dev = device_get_binding(LSM6DS3_CS_GPIO_NAME);
	if (NULL == lsm6ds3.spi_cs_conf.gpio_dev) {
		LOG_ERR("can not find device " LSM6DS3_CS_GPIO_NAME);
		return -1;
	}
	// set chip select
	lsm6ds3.spi_conf.cs = &lsm6ds3.spi_cs_conf;
	return 0;
}

static void lsm6ds3_setup(acc_config_id_t acc, unsigned int accIntrChannel, gyr_config_id_t gyr, unsigned int gyrIntrChannel) {
	enum cfgindxs {
		cfgindx_CTRL9_XL = 0,
		cfgindx_CTRL1_XL = 1,
		cfgindx_CTRL10_C = 2,
		cfgindx_CTRL2_G = 3,
		cfgindx_INT1_CTRL = 4,
		cfgindx_INT2_CTRL = 5,
		cfgindx_FIFO_CTRL5 = 6,
		cfgindx_amount
	};
	lsm6ds3_reg_t cfg[cfgindx_amount] = {
		{
			.addr = lsm6ds3_reg_addr_CTRL9_XL,
			.v = 0
		},
		{
			.addr = lsm6ds3_reg_addr_CTRL1_XL,
			.v = 0
		},
		{
			.addr = lsm6ds3_reg_addr_CTRL10_C,
			.v = 0
		},
		{
			.addr = lsm6ds3_reg_addr_CTRL2_G,
			.v = 0
		},
		{
			.addr = lsm6ds3_reg_addr_INT1_CTRL,
			.v = 0
		},
		{
			.addr = lsm6ds3_reg_addr_INT2_CTRL,
			.v = 0
		},
		{
			.addr = lsm6ds3_reg_addr_FIFO_CTRL5,
			.v = LSM6DS3_ODR_FIFO_DISABLED | LSM6DS3_FIFO_MODE_BYPASS
		}
	};

	// acc cfg
	if (acc_cfg_off != acc) {
		// CTRL9_XL
		cfg[cfgindx_CTRL9_XL].v = (LSM6DS3_ZEN_XL | LSM6DS3_YEN_XL | LSM6DS3_XEN_XL);
		// CTRL1_XL
		cfg[cfgindx_CTRL1_XL].v = acc_cfg.pAccCfgSetL[acc].ctrl1_xl;
	}
	if (gyr_cfg_off != gyr) {
		// CTRL10_C
		cfg[cfgindx_CTRL10_C].v = (LSM6DS3_ZEN_G | LSM6DS3_YEN_G | LSM6DS3_XEN_G);
		// CTRL2_G
		cfg[cfgindx_CTRL2_G].v = acc_cfg.pGyrCfgSetL[gyr].ctrl2_g;
	}

	if (accIntrChannel  == 1) {
		cfg[cfgindx_INT1_CTRL].v = LSM6DS3_INT1_DRDY_XL;
	} else {
		cfg[cfgindx_INT2_CTRL].v = LSM6DS3_INT2_DRDY_XL;
	}

	if (gyrIntrChannel  == 1) {
		cfg[cfgindx_INT1_CTRL].v |= LSM6DS3_INT1_DRDY_G;
	} else {
		cfg[cfgindx_INT2_CTRL].v |= LSM6DS3_INT2_DRDY_G;
	}
/*
	// setup output data rate for fifo
	{
		unsigned indx = (int)acc > (int)gyr ? (int)acc : (int)gyr;
		switch(indx){
			default:
			case 0:
				cfg[cfgindx_FIFO_CTRL5].v = LSM6DS3_ODR_FIFO_DISABLED | LSM6DS3_FIFO_MODE_BYPASS;
				break;
			case 1:
				cfg[cfgindx_FIFO_CTRL5].v = LSM6DS3_ODR_FIFO_26HZ | LSM6DS3_FIFO_MODE_CONT;
				break;
			case 2:
				cfg[cfgindx_FIFO_CTRL5].v = LSM6DS3_ODR_FIFO_52HZ | LSM6DS3_FIFO_MODE_CONT;
				break;
			case 3:
				cfg[cfgindx_FIFO_CTRL5].v = LSM6DS3_ODR_FIFO_104HZ | LSM6DS3_FIFO_MODE_CONT;
				break;
			case 4:
				cfg[cfgindx_FIFO_CTRL5].v = LSM6DS3_ODR_FIFO_208HZ | LSM6DS3_FIFO_MODE_CONT;
				break;
		}
	}
	*/
	lsm6ds3_regs_write(cfg, cfgindx_amount);
}

static void lsm6ds3_powerDown(void) {
	static const lsm6ds3_reg_t cfg[] = {
		{.addr = lsm6ds3_reg_addr_CTRL1_XL, .v = LSM6DS3_ODR_XL_POWER_DOWN},
		{.addr = lsm6ds3_reg_addr_CTRL2_G, .v = LSM6DS3_ODR_G_POWER_DOWN},
	};
	lsm6ds3_regs_write((lsm6ds3_reg_t *)cfg, sizeof(cfg)/sizeof(const lsm6ds3_reg_t));
}

static void lsm6ds3_init(void) {
	static const lsm6ds3_reg_t cfg[] = {
		{.addr = lsm6ds3_reg_addr_CTRL3_C, .v = LSM6DS3_IF_INC},
		{.addr = lsm6ds3_reg_addr_CTRL1_XL, .v = LSM6DS3_ODR_XL_POWER_DOWN},
		{.addr = lsm6ds3_reg_addr_CTRL2_G, .v = LSM6DS3_ODR_G_POWER_DOWN},
		{.addr = lsm6ds3_reg_addr_CTRL4_C, .v = LSM6DS3_I2C_DISABLE},
		{.addr = lsm6ds3_reg_addr_MASTER_CONFIG, .v = LSM6DS3_DRDY_ON_INT1},
		//LSM6DS3_MASTER_CONFIG, 0
		// fifo config
		/*
		{.addr = lsm6ds3_reg_addr_CTRL3_C, .v = LSM6DS3_BDU},
		{.addr = lsm6ds3_reg_addr_FIFO_CTRL1, .v = 6*5},
		{.addr = lsm6ds3_reg_addr_FIFO_CTRL2, .v = 0},
		//LSM6DS3_FIFO_CTRL3, LSM6DS3_DEC_FIFO_GYRO_X0 | LSM6DS3_DEC_FIFO_XL_X0,
		{.addr = lsm6ds3_reg_addr_FIFO_CTRL3, .v = LSM6DS3_DEC_FIFO_XL_X0},
		{.addr = lsm6ds3_reg_addr_FIFO_CTRL4, .v = 0},
		{.addr = lsm6ds3_reg_addr_FIFO_CTRL5, .v = LSM6DS3_ODR_FIFO_DISABLED | LSM6DS3_FIFO_MODE_BYPASS}, // disabled
		*/
	};

	// start setup
	lsm6ds3_regs_write((lsm6ds3_reg_t *)cfg, sizeof(cfg)/sizeof(const lsm6ds3_reg_t));

	lsm6ds3_setup(acc_cfg_off,1, gyr_cfg_off,2);
}

static int lsm6ds3_readACCsamples(movSample_t * pAcc) {
	if (!lsm6ds3_raw_read(lsm6ds3_reg_addr_OUTX_L_XL,(u8_t *) pAcc, 6)) {
		return 0;
	}
	return -1;
}

static int lsm6ds3_readGYRSamples(movSample_t * pGyr) {
	if (!lsm6ds3_raw_read(lsm6ds3_reg_addr_OUTX_L_G,(u8_t *) pGyr, 6)) {
		return 0;
	} else {
		return -1;
	}
}

static int lsm6ds3_getFiFoStatus(fifo_status_t * s) {
	if (lsm6ds3_raw_read(lsm6ds3_reg_addr_FIFO_STATUS1,(u8_t *) &s->raw, 4)) {
		return -1;
	}
	return 0;
}


static int lsm6ds3_readFiFoWords(u16_t * pB, unsigned int N) {
	unsigned int i;

	for (i = 0; i < N; i++) {
		if (lsm6ds3_raw_read(lsm6ds3_reg_addr_FIFO_DATA_OUT_L,(u8_t *) pB, 2)) {
			return -1;
		}
		pB++;
	}
	return 0;
}

static const lsm6ds3_api_t lsm6ds3_api = {
	.init = lsm6ds3_init,
	.powerDown = lsm6ds3_powerDown,
	.setup = lsm6ds3_setup,
	.readAcc = lsm6ds3_readACCsamples,
	.readGyr = lsm6ds3_readGYRSamples,
	.getFiFoStatus = lsm6ds3_getFiFoStatus,
	.readFiFoWords = lsm6ds3_readFiFoWords
};

DEVICE_AND_API_INIT(lsm6ds3_sensor, LSM6DS3_DEV_NAME, &lsm6ds3_initialize,
	NULL, NULL,
	POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,
	&lsm6ds3_api
	);

