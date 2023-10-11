#include <stdio.h>
#include "user_data.h"
#include "common.h"
#include "user_protocol.h"
#include "stm32f0xx_hal.h"
#include "stm32f0xx_hal_flash_ex.h"  
#include "gpio.h"

/**
 * @brief 添加监听指令步骤
 * （1）在user_protocol.h中定义opt
 * （2）在user_data.c中修改getQueryCmdIndex，增加index
 * （3）编写监听解析函数
 * （4）在query_cmd增加对应接口
 */

cmd_query_t query_cmd[] = {
    {OPT_CODE_SINGLE_DEV_QUERY_STATUS,                  onCmdGetAllStatus},
    {OPT_CODE_SINGLE_DEV_SET_SINGLE_LED_STATE,          onCmdSetSingleLedState},
    {OPT_CODE_SINGLE_DEV_SET_MULTI_LED_STATE,           onCmdSingleSetAllLedState},
    {OPT_CODE_SINGLE_DEV_MODIFY_BASE_SETTING,           onCmdModifyBaseSetting},
    {OPT_CODE_MULTI_DEV_SET_AUTO_REPORT_FLAG,           onCmdMultiSetAutoReportFlag},
    {OPT_CODE_MULTI_DEV_SET_SINGLE_LED_STATE,           onCmdMultiSetSingleLedState},
    {OPT_CODE_MULTI_DEV_SET_MULTI_LED_STATE,            onCmdMultiSetAllLedState},
    {OPT_CODE_SINGLE_MODIFY_BAUDRATE,   				onCmdSingleModifyBaudRate},
    {OPT_CODE_MULTI_MODIFY_BAUDRATE,    				onCmdMultiModifyBaudRate},	

};

/**
 * @brief 添加发布指令步骤
 * （1）在user_protocol.h中定义opt
 * （2）修改common.h中结构体cmd_control_t，增加对应的发布指令
 * （3）编写监听解析函数
 * （4）在report_cmd增加对应接口
 */

cmd_report_t report_cmd[] = {
    {&myDevice.cmdControl.singleQueryStatus.sendCmdEnable,          &myDevice.cmdControl.singleQueryStatus.sendCmdDelay,        onReportAllStatus},
    {&myDevice.cmdControl.singleSetLedState.sendCmdEnable,          &myDevice.cmdControl.singleSetLedState.sendCmdDelay,        onReportSetSingleLedState},
    {&myDevice.cmdControl.setAllLedsState.sendCmdEnable,       		&myDevice.cmdControl.setAllLedsState.sendCmdDelay,     onReportSetAllLedState},
    {&myDevice.cmdControl.autoAlarm.sendCmdEnable,          		&myDevice.cmdControl.autoAlarm.sendCmdDelay,          		onReportAlarmType},
    {&myDevice.cmdControl.singleBasicSetting.sendCmdEnable,         &myDevice.cmdControl.singleBasicSetting.sendCmdDelay,       onReportBaseSetting},
    {&myDevice.cmdControl.reportAddrAndUid.sendCmdEnable,           &myDevice.cmdControl.reportAddrAndUid.sendCmdDelay,         onReportAddrAndUid},
    {&myDevice.cmdControl.singleModifyBaudRate.sendCmdEnable,		&myDevice.cmdControl.singleModifyBaudRate.sendCmdDelay,		onReportSingleModifyBaudRate},

};

int getQueryCmdIndex(uint16_t opt)
{
    switch(opt){
        default:                                            return -1;
		case OPT_CODE_SINGLE_DEV_QUERY_STATUS:              return 0;
		case OPT_CODE_SINGLE_DEV_SET_SINGLE_LED_STATE:      return 1;
		case OPT_CODE_SINGLE_DEV_SET_MULTI_LED_STATE:       return 2;
		case OPT_CODE_SINGLE_DEV_MODIFY_BASE_SETTING:       return 3;
		case OPT_CODE_MULTI_DEV_SET_AUTO_REPORT_FLAG:       return 4;   
		case OPT_CODE_MULTI_DEV_SET_SINGLE_LED_STATE:       return 5; 
		case OPT_CODE_MULTI_DEV_SET_MULTI_LED_STATE:        return 6;
		case OPT_CODE_SINGLE_MODIFY_BAUDRATE:               return 7;
		case OPT_CODE_MULTI_MODIFY_BAUDRATE:				return 8;
    }
}

void onCmdGetAllStatus(uint8_t *data, uint16_t length)
{
    uint32_t uid0;
    uint32_t uid1;
    uint32_t uid2;
    uint16_t pos = 0;

    if(length < 12){
        //printf("[%s]length error!\r\n", __FUNCTION__);
        return;
    }

    uid0 = (data[pos++] << 24);
    uid0 += (data[pos++] << 16);
    uid0 += (data[pos++] << 8);
    uid0 += data[pos++];

    uid1 = (data[pos++] << 24);
    uid1 += (data[pos++] << 16);
    uid1 += (data[pos++] << 8);
    uid1 += data[pos++];

    uid2 = (data[pos++] << 24);
    uid2 += (data[pos++] << 16);
    uid2 += (data[pos++] << 8);
    uid2 += data[pos++];

    if(myDevice.uid0 != uid0 || myDevice.uid1 != uid1 || myDevice.uid2 != uid2){
       // printf("[%s]UID is not matched!\r\n", __FUNCTION__);
        return;
    }

    /* send dev status here */
    myDevice.cmdControl.singleQueryStatus.sendCmdEnable = CMD_ENABLE;
    myDevice.cmdControl.singleQueryStatus.sendCmdDelay = 0;
}

void onCmdSingleSetAllLedState(uint8_t *data, uint16_t length)
{
		uint32_t uid0;
		uint32_t uid1;
		uint32_t uid2;
		uint16_t pos = 0;
		uint32_t mode = 0;
		uint8_t ledState[DEV_NUM] = {0};

    if(NULL == data){
       // printf("[%s]data is null!\r\n", __FUNCTION__);
        return;
    }

    /* mode */
	mode  = (data[pos++] << 16);
	mode += (data[pos++] << 8);
	mode += data[pos++];
    /* led state */
	for(int i=DEV_NUM-1;i>0;i-=2){
		ledState[i]   = (data[pos] >> 4) & 0x0f;
		ledState[i-1] = (data[pos++] & 0x0f);
	}
    /* uid */
    uid0 = (data[pos++] << 24);
    uid0 += (data[pos++] << 16);
    uid0 += (data[pos++] << 8);
    uid0 += data[pos++];

    uid1 = (data[pos++] << 24);
    uid1 += (data[pos++] << 16);
    uid1 += (data[pos++] << 8);
    uid1 += data[pos++];

    uid2 = (data[pos++] << 24);
    uid2 += (data[pos++] << 16);
    uid2 += (data[pos++] << 8);
    uid2 += data[pos++];

    if(myDevice.uid0 != uid0 || myDevice.uid1 != uid1 || myDevice.uid2 != uid2){
        //printf("[%s]UID is not matched!\r\n", __FUNCTION__);
        return;
    }
		
		/* set dev state here */
		for(int i=0;i<DEV_NUM;i++){
			myDevice.devCtrl[i].mode = (mode >> i) & 0x01;
			myDevice.devCtrl[i].ledState = ledState[i];
		}
		/* send ack msg here */
		myDevice.cmdControl.setAllLedsState.sendCmdEnable = CMD_ENABLE;
		myDevice.cmdControl.setAllLedsState.sendCmdDelay = 0;	
		data[0] = 0;
}

void onCmdSetSingleLedState(uint8_t *data, uint16_t length)
{
    uint32_t uid0;
    uint32_t uid1;
    uint32_t uid2;
    uint16_t pos = 0;
    uint8_t status;
    uint8_t port;

    if(NULL == data){
       // printf("[%s]data is null!\r\n", __FUNCTION__);
        return;
    }

    /* port */
    port = data[pos++] - 1;
    /* mode and state */
    status = data[pos++];
    /* uid */
    uid0 = (data[pos++] << 24);
    uid0 += (data[pos++] << 16);
    uid0 += (data[pos++] << 8);
    uid0 += data[pos++];

    uid1 = (data[pos++] << 24);
    uid1 += (data[pos++] << 16);
    uid1 += (data[pos++] << 8);
    uid1 += data[pos++];

    uid2 = (data[pos++] << 24);
    uid2 += (data[pos++] << 16);
    uid2 += (data[pos++] << 8);
    uid2 += data[pos++];

    if(myDevice.uid0 != uid0 || myDevice.uid1 != uid1 || myDevice.uid2 != uid2){
       // printf("[%s]UID is not matched!\r\n", __FUNCTION__);
        return;
    }

	if(port >= DEV_NUM){
		//printf("[%s]invalid port num!!!\r\n", __FUNCTION__);
		return;
	}

    /* set dev state here */
   	myDevice.devCtrl[port].mode = (status >> 4) & 0x0f;
	myDevice.devCtrl[port].ledState = status & 0x0f;
	myDevice.devCtrl[port].send = CMD_ENABLE;
    /* send ack msg here */
    myDevice.cmdControl.singleSetLedState.sendCmdEnable = CMD_ENABLE;
    myDevice.cmdControl.singleSetLedState.sendCmdDelay = 0;
}

void onCmdModifyBaseSetting(uint8_t *data, uint16_t length)
{
    uint32_t uid0;
    uint32_t uid1;
    uint32_t uid2;
    uint16_t pos = 0;
    uint8_t address;
    uint8_t autoReportFlag;

	/* address */
    address = data[pos++];
	/* autoReportFlag */
    autoReportFlag = data[pos++];
	/* uid */
    uid0 = (data[pos++] << 24);
    uid0 += (data[pos++] << 16);
    uid0 += (data[pos++] << 8);
    uid0 += data[pos++];
	
    uid1 = (data[pos++] << 24);
    uid1 += (data[pos++] << 16);
    uid1 += (data[pos++] << 8);
    uid1 += data[pos++];

    uid2 = (data[pos++] << 24);
    uid2 += (data[pos++] << 16);
    uid2 += (data[pos++] << 8);
    uid2 += data[pos++];

    if(myDevice.uid0 != uid0 || myDevice.uid1 != uid1 || myDevice.uid2 != uid2){
        ///printf("[%s]UID is not matched!\r\n", __FUNCTION__);
        return;
    }

    /* set dev status */
    myDevice.address = address;
    myDevice.autoReportFlag = autoReportFlag;
	/* save setting */
	user_database_save();
    /* send dev status here */
    myDevice.cmdControl.singleBasicSetting.sendCmdEnable = CMD_ENABLE;
    myDevice.cmdControl.singleBasicSetting.sendCmdDelay = 0;  
}

void onCmdMultiSetAutoReportFlag(uint8_t *data, uint16_t length)
{
    uint16_t pos = 0;
    uint8_t autoReportFlag;

    if(length < 1){
       // printf("[%s]length error!\r\n", __FUNCTION__);
        return;
    }

    autoReportFlag = data[pos++];

    myDevice.autoReportFlag = autoReportFlag;

    user_database_save();
}

void onCmdMultiSetSingleLedState(uint8_t *data, uint16_t length)
{
    uint16_t pos = 0;
    uint8_t status;
    uint8_t port;

    if(NULL == data){
        //printf("[%s]data is null!\r\n", __FUNCTION__);
        return;
    }

    /* port */
    port = data[pos++] - 1;
    /* mode and state */
    status = data[pos++];
 

	if(port >= DEV_NUM){
		//printf("[%s]invalid port num!!!\r\n", __FUNCTION__);
		return;
	}

    /* set dev state here */
   	myDevice.devCtrl[port].mode = (status >> 4) & 0x0f;
	myDevice.devCtrl[port].ledState = status & 0x0f;
	myDevice.devCtrl[port].send = CMD_DISABLE;
}

void onCmdMultiSetAllLedState(uint8_t *data, uint16_t length)
{
		uint16_t pos = 0;
		uint32_t mode = 0;
		uint8_t ledState[DEV_NUM] = {0};
		uint8_t i;

    if(NULL == data){
      //  printf("[%s]data is null!\r\n", __FUNCTION__);
        return;
    }

    /* mode */
	mode  = (data[pos++] << 16);
	mode += (data[pos++] << 8);
	mode += data[pos++];
    /* led state */
	for(int i=DEV_NUM-1;i>0;i-=2){
		ledState[i]   = (data[pos] >> 4) & 0x0f;
		ledState[i-1] = (data[pos++] & 0x0f);
	}


    /* set dev state here */
	for(i=0;i<DEV_NUM;i++){
		myDevice.devCtrl[i].mode = (mode >> i) & 0x01;
		myDevice.devCtrl[i].ledState = ledState[i];
	}
}

void onCmdSingleModifyBaudRate(uint8_t *data, uint16_t length)
{
    uint32_t uid0;
    uint32_t uid1;
    uint32_t uid2;
    uint16_t pos = 0;
    uint8_t baudRateIndex = 0;

    baudRateIndex = data[pos++];

    uid0 = (data[pos++] << 24);
    uid0 += (data[pos++] << 16);
    uid0 += (data[pos++] << 8);
    uid0 += data[pos++];

    uid1 = (data[pos++] << 24);
    uid1 += (data[pos++] << 16);
    uid1 += (data[pos++] << 8);
    uid1 += data[pos++];

    uid2 = (data[pos++] << 24);
    uid2 += (data[pos++] << 16);
    uid2 += (data[pos++] << 8);
    uid2 += data[pos++]; 

    if(myDevice.uid0 != uid0 || myDevice.uid1 != uid1 || myDevice.uid2 != uid2){
       // printf("[%s]UID is not matched!\r\n", __FUNCTION__);
        return;
    }  
 
    myDevice.baudRateIndex = baudRateIndex;

    user_database_save();

    /* send ack msg */
    myDevice.cmdControl.singleModifyBaudRate.sendCmdEnable = CMD_ENABLE;
    myDevice.cmdControl.singleModifyBaudRate.sendCmdDelay = 0;
}

void onCmdMultiModifyBaudRate(uint8_t *data, uint16_t length)
{
    uint16_t pos = 0;
    uint8_t baudRateIndex = 0;

    baudRateIndex = data[pos++];

    myDevice.baudRateIndex = baudRateIndex;

    user_database_save();
    
    while(1);//wait for watchdog reset  
}

void onReportAllStatus(void)
{
    uint8_t buffer[100];
    uint8_t pos = 0;
	uint32_t onFlag = 0;
	uint32_t mode = 0;
    
    /* addr */
    buffer[pos++] = myDevice.address;
	/* auto report flag */
	buffer[pos++] = myDevice.autoReportFlag;
 	/* baudRate */
	buffer[pos++] = myDevice.baudRateIndex;
	/* switch onoff flag */
	for(uint8_t i=0;i<DEV_NUM;i++){
		onFlag += (myDevice.devCtrl[i].outState & 0x01) << i;
		mode += (myDevice.devCtrl[i].mode & 0x01) << i;
	}
	buffer[pos++] = (onFlag >> 16) & 0xff;
	buffer[pos++] = (onFlag >> 8) & 0xff;
	buffer[pos++] = onFlag & 0xff;
	/* led control mode */
	buffer[pos++] = (mode >> 16) & 0xff;
	buffer[pos++] = (mode >> 8) & 0xff;
	buffer[pos++] = mode & 0xff;
	/* led state */
	for(int i=DEV_NUM-1;i>0;i-=2){
		buffer[pos++] = ((myDevice.devCtrl[i].ledState << 4) & 0xf0) + (myDevice.devCtrl[i-1].ledState & 0x0f);
	}	
    /* UID */
    buffer[pos++] = (myDevice.uid0 >> 24)& 0xff;
    buffer[pos++] = (myDevice.uid0 >> 16) & 0xff;
    buffer[pos++] = (myDevice.uid0 >> 8) & 0xff;
    buffer[pos++] = myDevice.uid0 & 0xff;
    buffer[pos++] = (myDevice.uid1 >> 24)& 0xff;
    buffer[pos++] = (myDevice.uid1 >> 16) & 0xff;
    buffer[pos++] = (myDevice.uid1 >> 8) & 0xff;
    buffer[pos++] = myDevice.uid1 & 0xff;
    buffer[pos++] = (myDevice.uid2 >> 24)& 0xff;
    buffer[pos++] = (myDevice.uid2 >> 16) & 0xff;
    buffer[pos++] = (myDevice.uid2 >> 8) & 0xff;
    buffer[pos++] = myDevice.uid2 & 0xff;
    
    user_protocol_send_data(CMD_ACK, OPT_CODE_SINGLE_DEV_QUERY_STATUS, buffer, pos);       
}

void onReportSetSingleLedState(void)
{
    uint8_t buffer[50];
    uint8_t pos = 0;
    uint8_t port = 0;
	while(1){
		if(myDevice.devCtrl[port].send == CMD_DISABLE){
			port ++;
			if(port >= DEV_NUM) 
				return;
			else 
				continue;
		}
		/* addr */
    	buffer[pos++] = myDevice.address;
		/* port */
    	buffer[pos++] = port + 1;
		/* mode and state */
		buffer[pos++] = ((myDevice.devCtrl[port].mode << 4) & 0xf0) + (myDevice.devCtrl[port].ledState & 0x0f);
		/* UID */
	    buffer[pos++] = (myDevice.uid0 >> 24)& 0xff;
	    buffer[pos++] = (myDevice.uid0 >> 16) & 0xff;
	    buffer[pos++] = (myDevice.uid0 >> 8) & 0xff;
	    buffer[pos++] = myDevice.uid0 & 0xff;
	    buffer[pos++] = (myDevice.uid1 >> 24)& 0xff;
	    buffer[pos++] = (myDevice.uid1 >> 16) & 0xff;
	    buffer[pos++] = (myDevice.uid1 >> 8) & 0xff;
	    buffer[pos++] = myDevice.uid1 & 0xff;
	    buffer[pos++] = (myDevice.uid2 >> 24)& 0xff;
	    buffer[pos++] = (myDevice.uid2 >> 16) & 0xff;
	    buffer[pos++] = (myDevice.uid2 >> 8) & 0xff;
	    buffer[pos++] = myDevice.uid2 & 0xff;

		user_protocol_send_data(CMD_ACK, OPT_CODE_SINGLE_DEV_SET_SINGLE_LED_STATE, buffer, pos); 

		myDevice.devCtrl[port].send = CMD_DISABLE;

		port ++;
		if(port >= DEV_NUM) return;
	}
}

void onReportSetAllLedState(void)
{
    uint8_t buffer[100];
    uint8_t pos = 0;
	uint32_t mode = 0;
    /* addr */
    buffer[pos++] = myDevice.address;
	/* mode */
	buffer[pos] = 0;
	for(int i;i<DEV_NUM;i++){
		mode += ((myDevice.devCtrl[i].mode & 0x01) << i);
	}
	buffer[pos++] = (mode >> 16) & 0xff;
	buffer[pos++] = (mode >> 8) & 0xff;
	buffer[pos++] = mode & 0xff;
    /* led state */
	for(int i=DEV_NUM-1;i>0;i-=2){
		buffer[pos++] = ((myDevice.devCtrl[i].ledState << 4) & 0xf0) + (myDevice.devCtrl[i-1].ledState & 0x0f);
	}	
    /* UID */
    buffer[pos++] = (myDevice.uid0 >> 24)& 0xff;
    buffer[pos++] = (myDevice.uid0 >> 16) & 0xff;
    buffer[pos++] = (myDevice.uid0 >> 8) & 0xff;
    buffer[pos++] = myDevice.uid0 & 0xff;
    buffer[pos++] = (myDevice.uid1 >> 24)& 0xff;
    buffer[pos++] = (myDevice.uid1 >> 16) & 0xff;
    buffer[pos++] = (myDevice.uid1 >> 8) & 0xff;
    buffer[pos++] = myDevice.uid1 & 0xff;
    buffer[pos++] = (myDevice.uid2 >> 24)& 0xff;
    buffer[pos++] = (myDevice.uid2 >> 16) & 0xff;
    buffer[pos++] = (myDevice.uid2 >> 8) & 0xff;
    buffer[pos++] = myDevice.uid2 & 0xff;

    user_protocol_send_data(CMD_ACK, OPT_CODE_SINGLE_DEV_SET_MULTI_LED_STATE, buffer, pos);     
}

void onReportAlarmType(void)
{
    uint8_t buffer[100];
    uint8_t pos = 0;
	uint8_t port = 0;
	while(1){
		if(myDevice.repCtrl[port].enable){
			/* address */
		    buffer[pos++] = myDevice.address;
			/* port */
		    buffer[pos++] = port + 1;
			/* type */
			buffer[pos++] = myDevice.repCtrl[port].type;
			/* mode and led state */
			buffer[pos++] = (myDevice.devCtrl[port].mode << 4) + (myDevice.devCtrl[port].ledState & 0x0f);
			/* uid */
		    buffer[pos++] = (myDevice.uid0 >> 24)& 0xff;
		    buffer[pos++] = (myDevice.uid0 >> 16) & 0xff;
		    buffer[pos++] = (myDevice.uid0 >> 8) & 0xff;
		    buffer[pos++] = myDevice.uid0 & 0xff;
		    buffer[pos++] = (myDevice.uid1 >> 24)& 0xff;
		    buffer[pos++] = (myDevice.uid1 >> 16) & 0xff;
		    buffer[pos++] = (myDevice.uid1 >> 8) & 0xff;
		    buffer[pos++] = myDevice.uid1 & 0xff;
		    buffer[pos++] = (myDevice.uid2 >> 24)& 0xff;
		    buffer[pos++] = (myDevice.uid2 >> 16) & 0xff;
		    buffer[pos++] = (myDevice.uid2 >> 8) & 0xff;
		    buffer[pos++] = myDevice.uid2 & 0xff;

		    user_protocol_send_data(CMD_QUERY, OPT_CODE_REPORT_DEV_ALARM, buffer, pos);  
		}
		port ++;
		if(port >= DEV_NUM) return;
	}
}

void onReportBaseSetting(void)
{
    uint8_t buffer[100];
    uint8_t pos = 0;
	/* address */
    buffer[pos++] = myDevice.address;
	/* auto report flag */
    buffer[pos++] = myDevice.autoReportFlag;
	/* uid */
    buffer[pos++] = (myDevice.uid0 >> 24)& 0xff;
    buffer[pos++] = (myDevice.uid0 >> 16) & 0xff;
    buffer[pos++] = (myDevice.uid0 >> 8) & 0xff;
    buffer[pos++] = myDevice.uid0 & 0xff;
    buffer[pos++] = (myDevice.uid1 >> 24)& 0xff;
    buffer[pos++] = (myDevice.uid1 >> 16) & 0xff;
    buffer[pos++] = (myDevice.uid1 >> 8) & 0xff;
    buffer[pos++] = myDevice.uid1 & 0xff;
    buffer[pos++] = (myDevice.uid2 >> 24)& 0xff;
    buffer[pos++] = (myDevice.uid2 >> 16) & 0xff;
    buffer[pos++] = (myDevice.uid2 >> 8) & 0xff;
    buffer[pos++] = myDevice.uid2 & 0xff;

    user_protocol_send_data(CMD_ACK, OPT_CODE_SINGLE_DEV_MODIFY_BASE_SETTING, buffer, pos);     
}

void onReportAddrAndUid(void)
{
    uint8_t buffer[100];
    uint8_t pos = 0;
	/* address */
    buffer[pos++] = myDevice.address;
	/* bat switch status */
    buffer[pos++] = myDevice.batSwitchStatus;
	/* uid */
    buffer[pos++] = (myDevice.uid0 >> 24)& 0xff;
    buffer[pos++] = (myDevice.uid0 >> 16) & 0xff;
    buffer[pos++] = (myDevice.uid0 >> 8) & 0xff;
    buffer[pos++] = myDevice.uid0 & 0xff;
    buffer[pos++] = (myDevice.uid1 >> 24)& 0xff;
    buffer[pos++] = (myDevice.uid1 >> 16) & 0xff;
    buffer[pos++] = (myDevice.uid1 >> 8) & 0xff;
    buffer[pos++] = myDevice.uid1 & 0xff;
    buffer[pos++] = (myDevice.uid2 >> 24)& 0xff;
    buffer[pos++] = (myDevice.uid2 >> 16) & 0xff;
    buffer[pos++] = (myDevice.uid2 >> 8) & 0xff;
    buffer[pos++] = myDevice.uid2 & 0xff;

    user_protocol_send_data(CMD_QUERY, OPT_CODE_REPORT_DEV_ADDR_AND_UID, buffer, pos); 

}

void onReportSingleModifyBaudRate(void)
{
    uint8_t buffer[23];
    uint8_t pos = 0;
    /* addr */
    buffer[pos++] = myDevice.address;
    /* lock baudRateIndex */
    buffer[pos++] = myDevice.baudRateIndex;
    /* UID */
    buffer[pos++] = (myDevice.uid0 >> 24)& 0xff;
    buffer[pos++] = (myDevice.uid0 >> 16) & 0xff;
    buffer[pos++] = (myDevice.uid0 >> 8) & 0xff;
    buffer[pos++] = myDevice.uid0 & 0xff;
    buffer[pos++] = (myDevice.uid1 >> 24)& 0xff;
    buffer[pos++] = (myDevice.uid1 >> 16) & 0xff;
    buffer[pos++] = (myDevice.uid1 >> 8) & 0xff;
    buffer[pos++] = myDevice.uid1 & 0xff;
    buffer[pos++] = (myDevice.uid2 >> 24)& 0xff;
    buffer[pos++] = (myDevice.uid2 >> 16) & 0xff;
    buffer[pos++] = (myDevice.uid2 >> 8) & 0xff;
    buffer[pos++] = myDevice.uid2 & 0xff;

    user_protocol_send_data(CMD_ACK, OPT_CODE_SINGLE_MODIFY_BAUDRATE, buffer, pos); 

    while(1);//wait for watchdog reset 
}


uint16_t user_read_flash(uint32_t address)
{
    return *(__IO uint16_t*)address;
}

void user_database_init(void)
{
    uint16_t i;
    uint16_t lenOfDataBase = sizeof(database_t) / sizeof(uint16_t);
    database_t readDataBase;
    uint16_t *pData = (uint16_t *)&readDataBase;

    memset((uint8_t *)&myDevice, 0, sizeof(myDevice));

   // printf("\r\n******************** App Start ********************\r\n");

    myDevice.uid0 = HAL_GetUIDw0();
    myDevice.uid1 = HAL_GetUIDw1();
    myDevice.uid2 = HAL_GetUIDw2();
    //printf("Read data:\r\n");
    for(i=0;i<lenOfDataBase;i++){
        pData[i] = user_read_flash(DATABASE_START_ADDR + 2U*i);
       //printf("%d\t", pData[i]);
    }
    //printf("\r\n");

    if(DATABASE_MAGIC != readDataBase.magic){
       // printf("Init Database!!!\r\n");
        myDevice.autoReportFlag = DEFAULT_AUTO_REPORT_FLAG;
        myDevice.baudRateIndex = DEFAULT_BAUD_RATE_INDEX;
        user_database_save();
    }else{
      //  printf("Read database from flash!!!\r\n");
        myDevice.address = (uint8_t )readDataBase.address;
        myDevice.autoReportFlag = (uint8_t)readDataBase.autoReportFlag;
        myDevice.baudRateIndex = (readDataBase.baudRateIndex == 0xffff) ? DEFAULT_BAUD_RATE_INDEX : readDataBase.baudRateIndex;
    }

	for(i=0;i<DEV_NUM;i++){
		myDevice.devCtrl[i].outStateInitTime = DEFAULT_OUT_INIT_TIME;
	}
}

void user_database_save(void)
{
    uint16_t i;
    uint16_t lenOfDataBase = sizeof(database_t) / sizeof(uint16_t);
    database_t writeDataBase;
    uint16_t *pData = (uint16_t *)&writeDataBase;
    HAL_StatusTypeDef status;
    FLASH_EraseInitTypeDef flashEraseInitType;
    uint32_t PageError;

    writeDataBase.magic = DATABASE_MAGIC;
    writeDataBase.address = myDevice.address;
    writeDataBase.autoReportFlag = myDevice.autoReportFlag;

    writeDataBase.baudRateIndex = myDevice.baudRateIndex;

    HAL_FLASH_Unlock();

    flashEraseInitType.TypeErase = FLASH_TYPEERASE_PAGES;
    flashEraseInitType.PageAddress = DATABASE_START_ADDR;
    flashEraseInitType.NbPages = 1;
    status = HAL_FLASHEx_Erase(&flashEraseInitType, &PageError);
    
    if(HAL_OK != status){
        HAL_FLASH_Lock();
       // printf("Flash erase error: %d\r\n", status);
        return;
    }
    //printf("save data:\r\n");
    for(i=0;i<lenOfDataBase;i++){
        //printf("%d\t", pData[i]);
       if(HAL_OK != HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, DATABASE_START_ADDR + 2U*i, pData[i])){
         //   printf("[%s]write data[%d] fail!\r\n", __FUNCTION__, i);
       } 
    }
    //printf("\r\n");
    HAL_FLASH_Lock();
}

void user_reply_handle(void)
{
    uint16_t funcNum = sizeof(report_cmd) / sizeof(cmd_report_t);
    for(uint16_t i = 0; i < funcNum; i++){
        if(*report_cmd[i].cmdEnable && !(*report_cmd[i].cmdDelay)){
            *report_cmd[i].cmdEnable = CMD_DISABLE;
            report_cmd[i].func();
        }
    }
}

void user_check_report_delay(void)
{
    uint16_t funcNum = sizeof(report_cmd) / sizeof(cmd_report_t);
    for(uint16_t i = 0; i < funcNum; i++){
        if(*report_cmd[i].cmdEnable && (*report_cmd[i].cmdDelay > 0)){
            *report_cmd[i].cmdDelay --;
        }
    }
}

void printSetting(void)
{
    printf("Chip uuid: 0x%04x%04x%04x\r\n", myDevice.uid0, myDevice.uid1, myDevice.uid2);
    printf("address: 0x%02X\r\n", myDevice.address);
    printf("autoReportFlag: %d\r\n", myDevice.autoReportFlag);
    printf("baudRateIndex: %d\r\n", myDevice.baudRateIndex);
}

