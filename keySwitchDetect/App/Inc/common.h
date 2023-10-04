#ifndef __COMMON_H__
#define __COMMON_H__
#include <stdint.h>

#define DATABASE_START_ADDR         (0x0800F000)
#define DATABASE_MAGIC              (0xaaaa)


#define DEFAULT_AUTO_REPORT_FLAG    (1)
#define DEFAULT_BAUD_RATE_INDEX     (4)

#define DELAY_BASE                  (10)//100ms*10 = 1s
#define FLASH_FREQ                  (200)//ms
#define AUTO_CHECK                  (100)//100*1ms


#define DEV_NUM						(20)

enum {
    CMD_DISABLE = 0,
    CMD_ENABLE,
};

enum {
	STATE_DISABLE = 0,
	STATE_ENABLE,
};

enum {
    CHARGE_STATUS_ON = 0,
    CHARGE_STATUS_OFF,
    CHARGE_STATUS_BLINK,
};

enum {
    DONE_STATUS_ON = 0,
    DONE_STATUS_OFF,
    DONE_STATUS_BLINK,
};

enum {
    POWER_TYPE_AC_DC = 0,
    POWER_TYPE_BAT,
};

enum {
    BAT_SWITCH_OFF = 0,
    BAT_SWITCH_ON,
};

enum {
	LED_RED_ON = 0,
	LED_GREEN_ON,
};



typedef struct {
    uint8_t sendCmdEnable;
    uint16_t sendCmdDelay;
}cmd_setting_t;

typedef struct {
    cmd_setting_t singleQueryStatus;
    cmd_setting_t singleSetLedState;
	cmd_setting_t setAllLedsState;
	cmd_setting_t autoAlarm;
    cmd_setting_t singleBasicSetting;
	cmd_setting_t reportAddrAndUid;
    cmd_setting_t singleModifyBaudRate;
}cmd_control_t;

typedef struct {
	uint8_t mode;
	uint8_t ledState;
	uint8_t outState;
	uint8_t lastOutState;
	uint8_t outCnt;
	uint8_t outStateInitFlag;
	uint8_t flashStatus;
	uint8_t send;
	uint8_t port;
	uint16_t ledFlashCnt;
}dev_ctrl_t;

typedef struct {
	uint8_t enable;
	uint8_t type;
}report_ctrl_t;


typedef struct {
    uint8_t  autoReportFlag;
    uint8_t  address;
	uint8_t	 voltType;
	uint8_t  chargeStatus;
	uint8_t  doneStatus;
	uint8_t  batSwitchStatus;
	uint16_t checkPeriod;
    uint32_t uid0;
    uint32_t uid1;
    uint32_t uid2;
    uint16_t baudRateIndex;
	uint16_t batVoltage;
	uint16_t dcVoltage;
	uint16_t batOnVoltage;
    cmd_control_t cmdControl;
	dev_ctrl_t devCtrl[DEV_NUM];
	report_ctrl_t repCtrl[DEV_NUM];
}dev_ctx_t;


enum {
	LED_STATE_OFF = 0,
	LED_STATE_RED_ON,
	LED_STATE_GREEN_ON,
	LED_STATE_RED_FLASH,
	LED_STATE_GREEN_FLASH,
	LED_STATE_RED_GREEN_FLASH,
};

enum {
	LED_OFF = 0,
    LED_ON,
};

enum {
    LED_RED = 0,
    LED_GREEN,
};

enum {
	LED_MODE_AUTO = 0,
	LED_MODE_MANUAL,
};

typedef struct {
    uint16_t magic;
    uint16_t address;
    uint16_t autoReportFlag;
    uint16_t baudRateIndex;
}database_t;


extern dev_ctx_t myDevice;

void tim_interrupt_callback(void);
void auto_check_task(void);


#endif
