#include "main.h"
#include "common.h"
#include "user_data.h"


typedef struct {
    uint8_t cnt;
    uint8_t dir;
}check_status_t;

check_status_t charge_status = {0};

check_status_t charge_done = {0};

uint8_t u8AutoCheckPeriod = 0;
uint8_t u8ManualCheckPeriod = 0;

dev_ctx_t myDevice;
static uint16_t timeBase = 0;

void tim_interrupt_callback(void)
{
    /* 1ms */
    timeBase ++;   
    if(timeBase >= 100){
        /* 100ms */
        timeBase = 0;
			
				user_check_report_delay();
				
    }

	if(u8AutoCheckPeriod)   u8AutoCheckPeriod --;
		
	if(myDevice.checkPeriod > 0)	myDevice.checkPeriod --;
		
	for(int i=0;i<DEV_NUM;i++){
		if(myDevice.devCtrl[i].ledFlashCnt > 0)	myDevice.devCtrl[i].ledFlashCnt --;
		if(myDevice.devCtrl[i].outStateInitTime > 0) myDevice.devCtrl[i].outStateInitTime --;
	}
}

static void check_charge_status(void)
{
    if(HAL_GPIO_ReadPin(ChargeStatus_GPIO_Port, ChargeStatus_Pin)){
        /* uncharging */
        if(charge_status.dir == 0){
            charge_status.dir = 1;
            charge_status.cnt = 0;
            myDevice.chargeStatus = CHARGE_STATUS_BLINK;
        }
        charge_status.cnt ++;
        if(charge_status.cnt >= 30){
            charge_status.cnt = 0;
            myDevice.chargeStatus = CHARGE_STATUS_OFF;
        }
    }else{
        /* charging */
        if(charge_status.dir){
            charge_status.dir = 0;
            charge_status.cnt = 0;
            myDevice.chargeStatus = CHARGE_STATUS_BLINK;
        }
        charge_status.cnt ++;
        if(charge_status.cnt >= 30){
            charge_status.cnt = 0;
            myDevice.chargeStatus = CHARGE_STATUS_ON;
        }
    }

}

static void check_done_status(void)
{
     if(HAL_GPIO_ReadPin(DoneStatus_GPIO_Port, DoneStatus_Pin)){
        /* uncharge done */
        if(charge_done.dir == 0){
            charge_done.dir = 1;
            charge_done.cnt = 0;
            myDevice.doneStatus = DONE_STATUS_BLINK;
        }
        charge_done.cnt ++;
        if(charge_done.cnt >= 30){
            charge_done.cnt = 0;
            myDevice.doneStatus = DONE_STATUS_OFF;
        }
    }else{
        /* charge done */
        if(charge_done.dir){
            charge_done.dir = 0;
            charge_done.cnt = 0;
            myDevice.doneStatus = DONE_STATUS_BLINK;
        }
        charge_done.cnt ++;
        if(charge_done.cnt >= 30){
            charge_done.cnt = 0;
            myDevice.doneStatus = DONE_STATUS_ON;
        }
    } 
}



void auto_check_task(void)
{
    uint8_t batSwitchStatus = 0;
    uint8_t volType = 0;

    if(u8AutoCheckPeriod > 0)   return;

    u8AutoCheckPeriod = AUTO_CHECK;    

    if(myDevice.dcVoltage > 200){
        /* power type is dc*/
        volType = POWER_TYPE_AC_DC;
    }else if(myDevice.batVoltage > 2000){
        /* power type is bat, only bat */
        volType = POWER_TYPE_BAT;
    }else{
        volType = POWER_TYPE_AC_DC;
    }

    /* check bat switch status */
    if(myDevice.batOnVoltage >= 200){
        /* bat switch on */
        batSwitchStatus = BAT_SWITCH_ON;
    }else{
        /* bat switch off */
        batSwitchStatus = BAT_SWITCH_OFF;
    }

    /* check whether needing reporting */
    if(myDevice.voltType == 0xff){
        myDevice.voltType = volType;//power on, init
    }else if(volType != myDevice.voltType){
        myDevice.voltType = volType;
        if(myDevice.autoReportFlag){
           myDevice.cmdControl.reportAddrAndUid.sendCmdEnable = CMD_ENABLE;
           myDevice.cmdControl.reportAddrAndUid.sendCmdDelay = 0;
        }
    }

    /* send msg if neccesary */
    if(myDevice.batSwitchStatus == 0xff){
        myDevice.batSwitchStatus = batSwitchStatus;
    }else if(batSwitchStatus != myDevice.batSwitchStatus){
        myDevice.batSwitchStatus = batSwitchStatus;
        if(myDevice.autoReportFlag){
           myDevice.cmdControl.reportAddrAndUid.sendCmdEnable = CMD_ENABLE;
           myDevice.cmdControl.reportAddrAndUid.sendCmdDelay = 0;
        }
    }

//    /* check bat charge status */
//    check_charge_status();
//
//    /* check bat charge done */
//    check_done_status();
}


