/**********************************************************************
* - Description:		blue-scanner-driver
* - File:				bluetooth_driver.h
* - Compiler:			xtensa-esp32
* - Debugger:			USB2USART
* - Author:				Mohamed El-Sabagh
* - Target:				ESP32
* - Created:			2017-12-24
* - Last changed:		2017-12-24
*
**********************************************************************/
#ifndef BLUETOOTH_DRIVER_H_
#define BLUETOOTH_DRIVER_H_

#include <stdint.h>

#define BLUETOOTH_GATT_SCANNER          0
#define BLUETOOTH_GATT_ADVERTISER       1
#define BLUETOOTH_GATT_DUAL             2

void vBluetoothInit(uint8_t bluetooth_mode);
void vBluetoothDeInit();

#endif
